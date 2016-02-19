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


#include "darts.h"
#include "getClock.h"

#define INNER 1000
#define OUTER 1000

using namespace darts;

class tpStrictStart : public Codelet
{
public:
  tpStrictStart(uint32_t dep, uint32_t res, ThreadedProcedure * myTP, uint32_t stat):
  Codelet(dep,res,myTP,stat) { }  
  virtual void fire(void);
};

class tpStrictEnd : public Codelet
{
public:
  tpStrictEnd(uint32_t dep, uint32_t res, ThreadedProcedure * myTP, uint32_t stat):
  Codelet(dep,res,myTP,stat) { }  
  virtual void fire(void);
};

class tpStrictLauncher : public ThreadedProcedure
{
public:
    int depth;
    int fannout;
    
    tpStrictStart startCD;
    tpStrictEnd   endCD;
    //This is who to signal when complete
    Codelet * toSignal;
    //Constructor
    tpStrictLauncher(int theDepth, int theFannout, Codelet * toSig):
    ThreadedProcedure(),
    depth(theDepth),
    fannout(theFannout),
    startCD(0,0,this,0),
    endCD(1,1,this,0),
    toSignal(toSig) 
    { 
        add(&startCD);
        //add(&endCD);
    }
};

class cd1Strict : public Codelet
{
public:

    cd1Strict(uint32_t dep, uint32_t res, ThreadedProcedure * myTP, uint32_t stat) :
    Codelet(dep, res, myTP, stat){ }

    virtual void fire(void);
};

class cd2Strict : public Codelet
{
public:

    cd2Strict(uint32_t dep, uint32_t res, ThreadedProcedure * myTP, uint32_t stat) :
    Codelet(dep, res, myTP, stat){ }

    virtual void fire(void);
};

class tpStrict : public ThreadedProcedure
{
public:
    //These are the frame variables
    int depth;
    int fanout;
    cd1Strict CD1;
    cd2Strict CD2;
    Codelet * toSignal;
    //Constructor

    tpStrict(int theDepth, int theFanout, Codelet * toSig) :
    ThreadedProcedure(),
    depth(theDepth),
    fanout(theFanout),
    CD1(0, 0, this, SHORTWAIT),
    CD2(theFanout, theFanout, this, LONGWAIT),
    toSignal(toSig)
    {
        add(&CD1);
        //add(&CD2);
    }
};

void
cd1Strict::fire(void)
{
    tpStrict * myStrict = static_cast<tpStrict*> (myTP_);
    if (!myStrict->depth)
    {
        myStrict->toSignal->decDep();
    } else
    {
        for (int i = 0; i < myStrict->fanout; i++)
        {
            invoke<tpStrict > (myStrict, myStrict->depth - 1, myStrict->fanout, &myStrict->CD2);
        }
    }
}

void
cd2Strict::fire(void)
{
    tpStrict * myStrict = static_cast<tpStrict*> (myTP_);
    myStrict->toSignal->decDep();
}

void
tpStrictStart::fire(void)
{
    tpStrictLauncher * myLauncher = static_cast<tpStrictLauncher*> (myTP_);
    invoke<tpStrict>(myLauncher,myLauncher->depth,myLauncher->fannout,&myLauncher->endCD);
}

void
tpStrictEnd::fire(void)
{
    tpStrictLauncher * myLauncher = static_cast<tpStrictLauncher*> (myTP_);
    myLauncher->toSignal->decDep();
}

int main(int argc, char *argv[])
{
    if (argc != 7)
    {
        std::cout << "enter number of TP CD TPM CDM Fanout depth" << std::endl;
        return 0;
    }
    int tps = atoi(argv[1]);
    int cds = atoi(argv[2]);
    int tpm = atoi(argv[3]);
    int cdm = atoi(argv[4]);
    int fanout = atoi(argv[5]);
    int depth = atoi(argv[6]);
    
    uint64_t innerTime = 0;
    uint64_t outerTime = 0;
    
    ThreadAffinity affin(cds, tps, SPREAD, tpm, cdm);
    if (affin.generateMask())
    {
        Runtime * rt = new Runtime(&affin);
        
        for (int i = 0; i < OUTER; i++) 
        {
            rt->run(launch<tpStrictLauncher>(depth, fanout, &Runtime::finalSignal));
            for (int j = 0; j < INNER; j++) 
            {
                uint64_t startTime = getTime();
                rt->run(launch<tpStrictLauncher>(depth, fanout, &Runtime::finalSignal));
                uint64_t endTime = getTime();
                innerTime += endTime - startTime;
            }
            outerTime += innerTime / INNER;
            innerTime = 0;
        }
        std::cout << outerTime/OUTER << std::endl;
        delete rt;
    }
    return 0;
}