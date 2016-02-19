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


#ifndef AFFINITY_H
#define	AFFINITY_H
#include <string.h>
#include <iostream>
#ifdef COUNT
#include <papi.h>
#endif
#define NUMEVENTS 5

namespace darts
{

    struct AffinityMask
    {
        unsigned int size;
        unsigned int * clusterID;
        unsigned int * unitID;
        AffinityMask(unsigned int num):
        size(num)
        {
            clusterID = new unsigned int[size];
            unitID = new unsigned int[size];
        }
        ~AffinityMask(void)
        {
            delete [] clusterID;
            delete [] unitID;
        }
    };
    
    enum AffinityMode { SPREAD = 0, COMPACT= 1 };
    
    class ThreadAffinity
    {
    private:
      
	bool papi;
	bool L1;
	bool L2;
	bool FpIdle;
	bool Vector;
	bool Stall;
	
	bool llc;
        unsigned int mcPerTp;
        unsigned int numTPS;
        unsigned int numMCS;
        unsigned int TPpolicy;
        unsigned int MCpolicy;
	int * eventSet;
	long long * eventCounter;
        AffinityMode mode;
        AffinityMask TPMask;
        AffinityMask MCMask;
    public:
        ThreadAffinity(unsigned int mcpertp, unsigned int numbase, AffinityMode choice, unsigned int tpSched = 0, unsigned int mcSched = 0, bool LLC = false):
        papi(false),
        L1(false),
        L2(false),
        FpIdle(false),
        Vector(false),
        Stall(false),        
        llc(LLC),
        mcPerTp(mcpertp),
        numTPS(numbase), numMCS(numbase*(mcpertp)),
        TPpolicy(tpSched), MCpolicy(mcSched),
        eventSet(new int[numTPS+numMCS]),
        eventCounter(new long long[(numTPS+numMCS)*NUMEVENTS]),
        mode(choice),
        TPMask(numTPS), MCMask(numMCS) 
	{
#ifdef COUNT
	  for(unsigned int i=0;i<numTPS+numMCS;i++)
	  {
	    eventSet[i] = PAPI_NULL;
	  }
#endif
	}
        
        ~ThreadAffinity(void)
	{
	  delete [] eventCounter;
	  delete [] eventSet;
	}
        
        bool 		getLLC(void)    { return llc; }
        unsigned int   getNumTPS(void) { return numTPS;  }
        unsigned int   getNumMCS(void) { return numMCS; }
        unsigned int   getNumMcPerTp(void) { return mcPerTp; }
        AffinityMask * getTPMask(void) { return &TPMask; }
        AffinityMask * getMCMask(void) { return &MCMask; }
        unsigned int getTPpolicy(void) { return TPpolicy; }
        unsigned int getMCpolicy(void) { return MCpolicy; }
        bool generateMask(void);
        void printMask(void);
	bool usePapi(void) { return papi; }
	void initPapi(bool l1, bool l2, bool fpidle, bool vector, bool stall);
	bool threadInitPapi(int threadId);
	void startCounters(int threadId);
	void writeCounters(int threadId);
	long long readCounter(int threadId, int offset);
	void incrementCounters(int threadId);
    };

}

#endif	/* AFFINITY_H */

