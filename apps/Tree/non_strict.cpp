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

int pow(int base, int power)
{
    int temp = 1;
    for(int i=0;i<power;i++)
    {
        temp*=base;
    }
    return temp;
}

class tpNonStrictStart : public Codelet
{
public:
  tpNonStrictStart(uint32_t dep, uint32_t res, ThreadedProcedure * myTP, uint32_t stat):
  Codelet(dep,res,myTP,stat) { }  
  virtual void fire(void);
};

class tpNonStrictEnd : public Codelet
{
public:
  tpNonStrictEnd(uint32_t dep, uint32_t res, ThreadedProcedure * myTP, uint32_t stat):
  Codelet(dep,res,myTP,stat) { }  
  virtual void fire(void);
};

class tpNonStrictLauncher : public ThreadedProcedure
{
public:
    int depth;
    int fannout;
    
    tpNonStrictStart startCD;
    tpNonStrictEnd   endCD;
    //This is who to signal when complete
    Codelet * toSignal;
    //Constructor
    tpNonStrictLauncher(int theDepth, int theFannout, Codelet * toSig):
    ThreadedProcedure(),
    depth(theDepth),
    fannout(theFannout),
    startCD(0,0,this,0),
    endCD(pow(theFannout,theDepth),pow(theFannout,theDepth),this,0),
    toSignal(toSig) 
    { 
        add(&startCD);
        //add(&endCD);
    }
};

class cd1NonStrict : public Codelet
{
public:
  cd1NonStrict(uint32_t dep, uint32_t res, ThreadedProcedure * myTP, uint32_t stat):
  Codelet(dep,res,myTP,stat) { }
  
  virtual void fire(void);
};

class tpNonStrict : public ThreadedProcedure
{
public:
    //These are the frame variables
    int depth;
    int fanout;
    cd1NonStrict CD1;
    //This is who to signal when complete
    Codelet * toSignal;
    //Constructor
    tpNonStrict(int theDepth, int theFanout, Codelet * toSig):
    ThreadedProcedure(),
    depth(theDepth),
    fanout(theFanout),
    CD1(0,0,this,0),
    toSignal(toSig) 
    {
        add(&CD1);
    }
};

void 
cd1NonStrict::fire(void)
{
    tpNonStrict * myNonStrict = static_cast<tpNonStrict*>(myTP_);

    if(myNonStrict->depth)
    {
        for(int i = 0; i < myNonStrict->fanout; i++)
        {
            invoke<tpNonStrict>(myNonStrict, myNonStrict->depth-1, myNonStrict->fanout, myNonStrict->toSignal);
        }
    }
    myNonStrict->toSignal->decDep();
}

void
tpNonStrictStart::fire(void)
{
    tpNonStrictLauncher * myLauncher = static_cast<tpNonStrictLauncher*> (myTP_);
    invoke<tpNonStrict>(myLauncher,myLauncher->depth,myLauncher->fannout,&myLauncher->endCD);
}

void
tpNonStrictEnd::fire(void)
{
    tpNonStrictLauncher * myLauncher = static_cast<tpNonStrictLauncher*> (myTP_);
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
            rt->run(launch<tpNonStrictLauncher>(depth, fanout, &Runtime::finalSignal));
            for (int j = 0; j < INNER; j++) 
            {
                uint64_t startTime = getTime();
                rt->run(launch<tpNonStrictLauncher>(depth, fanout, &Runtime::finalSignal));
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