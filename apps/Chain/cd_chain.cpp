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


#include <iostream>
#include "darts.h"

#define INNER 1000
#define OUTER 1000

using namespace darts;

class cdSerialEmpty : public Codelet
{
private:
    Codelet * sig;
public:

    cdSerialEmpty(void) :
    Codelet() { }

    void
    initEmpty(Codelet * toSig, uint32_t dep, uint32_t res, ThreadedProcedure * myTP, uint32_t stat)
    {
        sig = toSig;
        initCodelet(dep, res, myTP, stat);
    }
    virtual void fire(void);
};

class cdSerial : public ThreadedProcedure
{
public:
    int depth;
    cdSerialEmpty * empty;

    cdSerial(int theDepth, Codelet * toSig) :
    ThreadedProcedure(),
    depth(theDepth)
    {
        empty = new cdSerialEmpty[depth];
        for (int i = 1; i < depth - 1; i++)
        {
            empty[i].initEmpty(&empty[i + 1], 1, 1, this, SHORTWAIT);
        }
        
        if(depth==1)
            empty[0].initEmpty(toSig, 0, 0, this, SHORTWAIT);
        else
        {
            empty[0].initEmpty(&empty[1], 0, 0, this, SHORTWAIT);
            empty[depth-1].initEmpty(toSig, 1, 1, this, SHORTWAIT);
        }
        add(&empty[0]);
    }
    ~cdSerial(void)
    {
        delete [] empty;
    }
};

void
cdSerialEmpty::fire(void)
{
    sig->decDep();
}

int main(int argc, char *argv[])
{
    if (argc != 6)
    {
        std::cout << "enter number of TP CD TPM CDM depth" << std::endl;
        return 0;
    }
    int tps = atoi(argv[1]);
    int cds = atoi(argv[2]);
    int tpm = atoi(argv[3]);
    int cdm = atoi(argv[4]);
    int depth = atoi(argv[5]);
    uint64_t innerTime = 0;
    uint64_t outerTime = 0;
    
    if(depth>0)
    {
        ThreadAffinity affin(cds, tps, SPREAD, tpm, cdm);
        if (affin.generateMask())
        {
            Runtime * rt = new Runtime(&affin);

            for (int i = 0; i < OUTER; i++) 
            {
                rt->run(launch<cdSerial> (depth, &Runtime::finalSignal));
                for (int j = 0; j < INNER; j++) 
                {
                    uint64_t startTime = getTime();
                    rt->run(launch<cdSerial> (depth, &Runtime::finalSignal));
                    uint64_t endTime = getTime();
                    innerTime += endTime - startTime;
                }
                outerTime += innerTime / INNER;
                innerTime = 0;
            }
            std::cout << outerTime/OUTER << std::endl;
            delete rt;
        }
    }
    return 0;
}