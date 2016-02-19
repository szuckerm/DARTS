/* 
 * Copyright (c) 2011-2014, University of Delaware
 * All rights reserved.
 * 
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 * 
 * 1. Redistributions of source code must retain the above copyright notice,
 * this list of conditions and the following disclaimer.
 * 
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 * this list of conditions and the following disclaimer in the documentation
 * and/or other materials provided with the distribution.
 * 
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 */


#include <stdlib.h>
#include <cassert>
#include <time.h>
#include "Atomics.h"
#include "Runtime.h"

#ifdef TRACE
#include "getClock.h"
#endif
#ifndef _MSC_VER
#include <unistd.h>
#endif
using namespace darts;

CodeletFinal Runtime::finalSignal;

void * MCThread( void * args)
{
    mcRuntimeArgs * mcargs = static_cast<mcRuntimeArgs*> (args);
    Runtime * rt = mcargs->rt;
    unsigned int numMCS = rt->getNumMCS();
    unsigned int threadId = mcargs->threadId;
    unsigned int clusterId = mcargs->clusterId;
    unsigned int unitId = mcargs->unitId;
    
    MScheduler * myMCSched = rt->newMCSched(clusterId*numMCS+unitId, mcargs->mcSched);
    myMCSched->setID(threadId);
    rt->finalSignal.addAliveSignal(threadId,myMCSched);
    
    if(rt->usePapi())
    {
      rt->getAffinity()->threadInitPapi(threadId);
      myMCSched->setAffinity(rt->getAffinity());
    }
    rt->decMC();
    rt->decFull();
    rt->spin();
    
    myThread.threadTPsched = myMCSched->getParentScheduler();
    myThread.threadMCsched = myMCSched;
    
    myMCSched->policy();
    return 0;
}

void * TPThread( void * args)
{
    tpRuntimeArgs * tpargs = static_cast<tpRuntimeArgs*> (args);
    Runtime * rt = tpargs->rt;
    unsigned int threadId = tpargs->threadId;
    unsigned int clusterId = tpargs->clusterId;
    
    TPScheduler * myTPSched = rt->newTPSched(clusterId, tpargs->tpSched);
    myTPSched->setID(threadId);
    myTPSched->setNumPeers(rt->getNumTPS());
    rt->finalSignal.addAliveSignal(threadId,myTPSched);
    
    if(rt->usePapi())
    {
      rt->getAffinity()->threadInitPapi(threadId);
      myTPSched->setAffinity(rt->getAffinity());
    }
    
    rt->decTP();
    rt->decFull();
    rt->spin();
    
    myThread.threadTPsched = myTPSched;
    myThread.threadMCsched = NULL;
    
    myTPSched->policy();
    return 0;
}

void TPThread0( Runtime * rt, unsigned int tpPolicy)
{   
    TPScheduler * myTPSched = rt->newTPSched(0, tpPolicy);
    myTPSched->setID(0);
    myTPSched->setNumPeers(rt->getNumTPS());
    rt->finalSignal.addAliveSignal(0,myTPSched);
    
    if(rt->usePapi())
    {
      rt->getAffinity()->threadInitPapi(0);
      myTPSched->setAffinity(rt->getAffinity());
    }
    
    rt->decTP();
    while(rt->checkTP());
    rt->linkTPSched();
    
    while(rt->checkMC());
    rt->linkMCSched();
    
    myThread.threadTPsched = myTPSched;
    myThread.threadMCsched = NULL;
    
    rt->decFull();    
}

void Runtime::linkTPSched()
{
    for(unsigned int i=0;i<numTPSched_;i++)
    {
        for(unsigned int j=0;j<numTPSched_;j++)
        {
            TPSched_[i]->addPeer(TPSched_[j], j);
        }
    }
}

void Runtime::linkMCSched()
{
    for(unsigned int i=0;i<numTPSched_;i++)
    {
        for(unsigned int j=0;j<numMCSched_;j++)
        {
              TPSched_[i]->setSubScheduler(MCSched_[i * numMCSched_ + j]);
              MCSched_[i * numMCSched_ + j]->setParentScheduler(TPSched_[i]);
        }
    }
}

void Runtime::run(tpClosure * tpToStart)
{    
    finalSignal.resetCodelet();
    TPSched_[0]->resurrect();    
    TPSched_[0]->pushTP( tpToStart );
    TPSched_[0]->policy();
}

Runtime::Runtime(unsigned int maxCluster, unsigned int maxWorker):
AbsMac       (false),
clusterMap   (AbsMac.getClusterMap()),
numTPSched_  (   (AbsMac.getNbClusters()<maxCluster) ? AbsMac.getNbClusters() : maxCluster ),
numMCSched_  ( ( (clusterMap[0].getNbUnits()-1) < maxWorker) ? (clusterMap[0].getNbUnits()-1) : maxWorker ),
numThreads_  (numTPSched_ + numTPSched_ * numMCSched_),   
TPSched_      (new TPScheduler*[numTPSched_]),
MCSched_      (new MScheduler*[numMCSched_*numTPSched_]),
localThreads_ (new Thread[numThreads_]),
tpargs_       (new tpRuntimeArgs[numTPSched_]),
mcargs_       (new mcRuntimeArgs[numMCSched_*numTPSched_]),
affinity_    (NULL),
papi_	     (false),
tpcount_     (numTPSched_),
mccount_     (numTPSched_ * numMCSched_),
fullcount_   (numTPSched_ + numTPSched_ * numMCSched_),
spin_        (true)
{    
    if(maxCluster > AbsMac.getNbClusters() && maxCluster!=(unsigned int)-1)
      std::cerr << "maxCluster is greater than the number of available cluster" << std::endl;

    if(maxWorker > AbsMac.getNbClusters() && maxWorker!=(unsigned int)-1)
      std::cerr << "maxWorker is greater than the number of available worker" << std::endl;
    
    srand( time( 0 ) );
    
    finalSignal.setNumThreads(numThreads_);
    
    finalSignal.setTerminate(false);
    
    for(unsigned int i=0;i<numTPSched_;i++)
    {
        unsigned tid = i * (1 + numMCSched_);
        tpargs_[i].rt = this;
        tpargs_[i].threadId = tid;
        tpargs_[i].clusterId = i;
        tpargs_[i].tpSched = 0;
        localThreads_[tid].resetArgument( &tpargs_[i] );
        localThreads_[tid].resetFunction( TPThread );
        localThreads_[tid].setAffinity(clusterMap[i].getUnits()[0].getId());
    }
    
    for(unsigned int i=0;i<numTPSched_;i++)
    {
        int idx = i * numMCSched_;
        for(unsigned int j=0;j<numMCSched_;j++)
        {
            unsigned int tid = i * (1 + numMCSched_) + j + 1;
            mcargs_[ idx + j ].rt = this;
            mcargs_[ idx + j ].threadId = tid;
            mcargs_[ idx + j ].clusterId = i;
            mcargs_[ idx + j ].unitId = j;
            mcargs_[ idx + j ].mcSched = 0;
            localThreads_[tid].resetArgument( &mcargs_[ idx + j ] );
            localThreads_[tid].resetFunction( MCThread );
            localThreads_[tid].setAffinity(clusterMap[i].getUnits()[j+1].getId());
        }
    }
    
    for (unsigned int i = 1; i < numThreads_; i++ )
        localThreads_[i].run();

    TPThread0(this, 0);
}

Runtime::Runtime(ThreadAffinity * affinity):
AbsMac       (affinity->getLLC()),
clusterMap   (AbsMac.getClusterMap()),
numTPSched_  ( affinity->getNumTPS() ),
numMCSched_  ( affinity->getNumMcPerTp() ),
numThreads_  (numTPSched_ + numTPSched_ * numMCSched_),   
TPSched_      (new TPScheduler*[numTPSched_]),
MCSched_      (new MScheduler*[numMCSched_*numTPSched_]),
localThreads_ (new Thread[numThreads_]),
tpargs_       (new tpRuntimeArgs[numTPSched_]),
mcargs_       (new mcRuntimeArgs[numMCSched_*numTPSched_]),
affinity_    (affinity),
papi_	     (affinity->usePapi()),
tpcount_     (numTPSched_),
mccount_     (numTPSched_ * numMCSched_),
fullcount_   (numTPSched_ + numTPSched_ * numMCSched_),
spin_        (true)
{     
    srand( time( 0 ) );
    
    finalSignal.setNumThreads(numThreads_);
    
    finalSignal.setTerminate(false);
    
    AffinityMask * TPaffinity = affinity->getTPMask();
    AffinityMask * MCaffinity = affinity->getMCMask();

    for(unsigned int i=0;i<numTPSched_;i++)
    {
        unsigned tid = i * (1 + numMCSched_);
        tpargs_[i].rt = this;
        tpargs_[i].threadId = tid;
        tpargs_[i].clusterId = i;
        tpargs_[i].tpSched = affinity->getTPpolicy();
        localThreads_[tid].resetArgument( &tpargs_[i] );
        localThreads_[tid].resetFunction( TPThread );
        localThreads_[tid].setAffinity(clusterMap[TPaffinity->clusterID[i]].getUnits()[TPaffinity->unitID[i]].getId());
    }
    
    for(unsigned int i=0;i<numTPSched_;i++)
    {
        int idx = i * numMCSched_;
        for(unsigned int j=0;j<numMCSched_;j++)
        {
            unsigned int tid = i * (1 + numMCSched_) + j + 1;
            mcargs_[ idx + j ].rt = this;
            mcargs_[ idx + j ].threadId = tid;
            mcargs_[ idx + j ].clusterId = i;
            mcargs_[ idx + j ].unitId = j;
            mcargs_[ idx + j ].mcSched = affinity->getMCpolicy();
            localThreads_[tid].resetArgument( &mcargs_[ idx + j ] );
            localThreads_[tid].resetFunction( MCThread );
            localThreads_[tid].setAffinity(clusterMap[MCaffinity->clusterID[idx + j]].getUnits()[MCaffinity->unitID[idx + j]].getId());
        }
    }
    for (unsigned int i = 1; i < numThreads_; i++ )
        localThreads_[i].run();

    TPThread0(this, affinity->getTPpolicy());
}

Runtime::~Runtime(void)
{
    if(!finalSignal.getTerminate())
    {
        finalSignal.setTerminate(true);
        finalSignal.resetCodelet();
        finalSignal.decDep();
        for (unsigned int i = 1; i < numThreads_; i++ )
            localThreads_[i].join(); 
    }
    for(unsigned int i = 0;i<numTPSched_;i++)
        delete TPSched_[i];
    for(unsigned int i = 0;i<numTPSched_*numMCSched_;i++)
        delete MCSched_[i];
    delete [] TPSched_;
    delete [] MCSched_;
    delete [] localThreads_;
    delete [] tpargs_;
    delete [] mcargs_;  
}
