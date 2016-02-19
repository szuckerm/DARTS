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


#include "Affinity.h"
#include "AbstractMachine.h"
#include <iostream>
using namespace darts;

bool
ThreadAffinity::generateMask(void)
{
    hwloc::AbstractMachine AbsMac(llc);
    hwloc::Cluster * clusterMap = AbsMac.getClusterMap();
    unsigned int totalUnits = AbsMac.getTotalNbUnits();
    unsigned int maxCluster = AbsMac.getNbClusters();
    unsigned int maxUnit = clusterMap[0].getNbUnits();
    unsigned int totalRequestedUnits = numTPS + numMCS;
    unsigned int RequestedUnits = mcPerTp + 1;
    
    if(numTPS==0)
        return false;
    
    if (totalRequestedUnits > totalUnits)
    {
        std::cout << "Requested " << totalRequestedUnits << " only " << totalUnits << " available." << std::endl;
        return false;
    }
    
    unsigned int check = RequestedUnits/maxUnit;
    if(RequestedUnits%maxUnit)
        check++;
    
    unsigned int count;
    
    switch (mode)
    {
        case SPREAD:
            if(check*maxUnit*numTPS > totalUnits)
            {
                std::cout << "Size will not fit in SPREAD mode" << std::endl;
                return false;
            }
            //else if(numTPS > maxCluster)
            //{
            //    std::cout << "Size will not fit in SPREAD mode" << std::endl;
            //    return false;
            //}
            if (RequestedUnits < maxUnit)
            {
                unsigned int * clusterCount = new unsigned int[maxCluster];
                for (unsigned int i = 0; i < maxCluster; i++)
                    clusterCount[i] = 0;
                for (unsigned int i = 0; i < numTPS; i++)
                {
                    TPMask.clusterID[i] = i % maxCluster;
                    TPMask.unitID[i] = clusterCount[i];
                    clusterCount[i]=clusterCount[i]+1;
                    for (unsigned int j = 0; j < mcPerTp; j++)
                    {
                        MCMask.clusterID[ i * mcPerTp + j ] = i % maxCluster;
                        MCMask.unitID [ i * mcPerTp + j ] = clusterCount[i];
                        clusterCount[i]=clusterCount[i]+1;
                    }
                }
                delete [] clusterCount;
            } 
            else
            {
                count = 0;
                for (unsigned int i = 0; i < numTPS; i++)
                {
                    TPMask.clusterID[i] = count / maxUnit;
                    TPMask.unitID[i] = count % maxUnit;
                    count++;
                    //std::cout << "TP: " << TPMask.clusterID[i] << ", " << TPMask.unitID[i] << std::endl;
                    for (unsigned int j = 0; j < mcPerTp; j++)
                    {
                        MCMask.clusterID[i * mcPerTp + j] = count / maxUnit;
                        MCMask.unitID[i * mcPerTp + j] = count % maxUnit;
                        count++;
                        //std::cout << "MC: " << MCMask.clusterID[i * mcPerTp + j] << ", " << MCMask.unitID[i * mcPerTp + j] << std::endl;
                    }
                    if(count%maxUnit)
                    {
                        unsigned int temp = count / maxUnit;
                        count = (temp+1)*maxUnit;
                    }
                }
            }
            
            break;
        
        case COMPACT:
            
            count = 0;
            for (unsigned int i = 0; i < numTPS; i++)
            {
                TPMask.clusterID[i] = count / maxUnit;
                TPMask.unitID[i] = count % maxUnit;
                count++;
                //std::cout << "TP: " << TPMask.clusterID[i] << ", " << TPMask.unitID[i] << std::endl;
                for (unsigned int j = 0; j < mcPerTp; j++)
                {
                    MCMask.clusterID[i * mcPerTp + j] = count / maxUnit;
                    MCMask.unitID[i * mcPerTp + j] = count % maxUnit;
                    count++;
                    //std::cout << "MC: " << MCMask.clusterID[i * mcPerTp + j] << ", " << MCMask.unitID[i * mcPerTp + j] << std::endl;
                }
            }

            break;
        
        default:
            return false;
    }
    return true;
}

void
ThreadAffinity::printMask(void)
{
    for(unsigned int i=0;i<TPMask.size;i++)
    {
        std::cout << "TPSched " << TPMask.clusterID[i] << " " << TPMask.unitID[i] << " Policy " << TPpolicy << std::endl;
    }
    
    for(unsigned int i=0;i<MCMask.size;i++)
    {
        std::cout << "MCSched " << MCMask.clusterID[i] << " " << MCMask.unitID[i] << std::endl;
    }
}


void 
ThreadAffinity::initPapi(bool l1, bool l2, bool fpidle, bool vector, bool stall)
{
#ifdef COUNT
  int tempNum = ( (l1) ? 2 : 1 ) + ( (l2) ? 2 : 1 ) + ( (fpidle) ? 1 : 0 ) + ( (vector) ? 1 : 0 ) + ( (stall) ? 1 : 0 );
  if(tempNum>NUMEVENTS)
  {
    papi = false;
    return;
  }
  
  L1 = l1;
  L2 = l2;
  FpIdle = fpidle;
  Vector = vector;
  Stall = stall;
  
  //Set addresses for required hardware counters
  unsigned int l1DCM = 0x40000006;
  unsigned int l1DCA = 0x40000007;
  unsigned int l2DCM = 0x4000000b;
  unsigned int l2DCA = 0x4000000a;
  unsigned int fpIDLE = 0x40000019;
  unsigned int vecINS = 0x4000001a;
  unsigned int stlRES = 0x40000017;
  
    //Initialize PAPI library
  int retval = PAPI_library_init(PAPI_VER_CURRENT);
  if(retval != PAPI_VER_CURRENT && retval > 0)
  {
    papi = false;
    return;
  }

  //Initialize thread handling
  if(PAPI_thread_init(pthread_self) != PAPI_OK)
  {
    papi = false;
    return;
  }
  
  if(l1)
  {
    if (PAPI_query_event(l1DCM) != PAPI_OK)
    {
      papi = false;
      return;
    }
    if (PAPI_query_event(l1DCA) != PAPI_OK)
    {
      papi = false;
      return;
    }
  }
  
  if(l2)
  {
    if (PAPI_query_event(l2DCM) != PAPI_OK)
    {
      papi = false;
      return;
    }
    if (PAPI_query_event(l2DCA) != PAPI_OK)
    {
      papi = false;
      return;
    }    
  }
  
  if(fpidle)
  {
    if (PAPI_query_event(fpIDLE) != PAPI_OK)
    {
      papi = false;
      return;
    }
  }

  if(vector)
  {
    if (PAPI_query_event(vecINS) != PAPI_OK)
    {
      papi = false;
      return;
    }
  }

  if(stall)
  {
    if (PAPI_query_event(stlRES) != PAPI_OK)
    {
      papi = false;
      return;
    }
  }
  papi = true;
#else
  (void) l1;
  (void) l2;
  (void) fpidle;
  (void) vector;
  (void) stall;
#endif
}

bool 
ThreadAffinity::threadInitPapi(int threadId)
{
  memset(&eventCounter[threadId*NUMEVENTS], 0, NUMEVENTS*sizeof(long long));
  
#ifdef COUNT
  //Set addresses for required hardware counters
  unsigned int l1DCM = 0x40000006;
  unsigned int l1DCA = 0x40000007;
  unsigned int l2DCM = 0x4000000b;
  unsigned int l2DCA = 0x4000000a;
  unsigned int fpIDLE = 0x40000019;
  unsigned int vecINS = 0x4000001a;
  unsigned int stlRES = 0x40000017;
  
  //Create eventSet
  if (PAPI_create_eventset(&eventSet[threadId]) != PAPI_OK)
  {
    std::cout << "Thread " << threadId << " PAPI_create_eventset - FAILED\n";
    return false;
  }
  
  if(L1)
  {
    if(PAPI_add_event(eventSet[threadId], l1DCM) != PAPI_OK)
      return false;
    
    if(PAPI_add_event(eventSet[threadId], l1DCA) != PAPI_OK)
      return false;
  }
  
  if(L2)
  {
    if(PAPI_add_event(eventSet[threadId], l2DCM) != PAPI_OK)
      return false;
    
    if(PAPI_add_event(eventSet[threadId], l2DCA) != PAPI_OK)
      return false;
  }	
    
  if(FpIdle)
  {
    if(PAPI_add_event(eventSet[threadId], fpIDLE) != PAPI_OK)
      return false;
  }

  if(Vector)
  {
    if(PAPI_add_event(eventSet[threadId], vecINS) != PAPI_OK)
      return false;
  }

  if(Stall)
  {
    if(PAPI_add_event(eventSet[threadId], stlRES) != PAPI_OK)
      return false;
  }
  return true;
#else
  (void) threadId;
  return false;
#endif
}

void 
ThreadAffinity::startCounters(int threadId)
{
#ifdef COUNT
  if (PAPI_start(eventSet[threadId]) != PAPI_OK) 
  {
    std::cout << "Thread " << threadId << " PAPI_start_counters - FAILED\n";
  }
#else
  (void) threadId;
#endif
}

void 
ThreadAffinity::writeCounters(int threadId)
{
#ifdef COUNT
  if (PAPI_stop(eventSet[threadId], &eventCounter[threadId*NUMEVENTS]) != PAPI_OK) 
  {
    std::cout <<"Thread " << threadId << " PAPI_stopped_counters - FAILED\n";
  }
#else
  (void) threadId;
#endif
}

void 
ThreadAffinity::incrementCounters(int threadId)
{
#ifdef COUNT
  long long temp[NUMEVENTS];
  memset(temp, 0, NUMEVENTS*sizeof(long long));
  if (PAPI_stop(eventSet[threadId], temp) != PAPI_OK) 
  {
    std::cout <<"Thread " << threadId << " PAPI_stopped_counters - FAILED\n";
  }
  for(int i=0;i<NUMEVENTS;i++)
  {
    eventCounter[threadId*NUMEVENTS + i]+=temp[i];
  }
#else
  (void) threadId;
#endif
}

long long 
ThreadAffinity::readCounter(int threadId, int offset)
{
#ifdef COUNT
  long long temp = eventCounter[threadId*NUMEVENTS + offset];
  eventCounter[threadId*NUMEVENTS + offset] = 0;
  return temp;
#else
  (void) threadId;
  (void) offset;
  return 0;
#endif
}