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


#ifndef NESTED_H
#define	NESTED_H
#include "loop.h"

#define GETREPS(items,div) (items > div) ? ( (items%div) ? (div + 1) : (div) ) : 1
#define GETEND(items,div,iter) (items/div)*(iter) + ((iter==div || items < div) ? (items%div) : (items/div))

namespace darts
{ 
    class nestedLoop : public ThreadedProcedure
    {
    public:

        class Core : public Codelet
        {
        private:
            unsigned start;
            unsigned end;
            ThreadedProcedure * parentTP;
            Codelet * toSignal;
        public:
            Core(uint32_t dep, uint32_t res, ThreadedProcedure * myTP, uint32_t stat, 
                 unsigned int Start, unsigned int End, ThreadedProcedure * ParentTP, Codelet * toSig):
            Codelet(dep,res,myTP,stat),
            start(Start),
            end(End),
            parentTP(ParentTP),
            toSignal(toSig)
            { 
            }

            virtual void fire(void);
        };

        class SingleLoop: public loop
        {
        public:
            unsigned int iterationStart;
            unsigned int iterationEnd;
            Core core;

            SingleLoop(unsigned int it, Codelet * toSig, unsigned int Start, unsigned int End, ThreadedProcedure * ParentTP, unsigned int Workers):
            loop(it,toSig),
            iterationStart(Start + ((End-Start)/Workers)*it),
            iterationEnd(Start + GETEND((End-Start),Workers,it)),
            core(0,0,this,SHORTWAIT, 
                iterationStart,
                iterationEnd,
                ParentTP,
                toSignal)
            {
                add(&core);
            }        
        };


        class DoubleLoop : public loop
        {
        public:
            unsigned int iterationStart;
            unsigned int iterationEnd;
            codeletFor<SingleLoop> innerLoop;

            DoubleLoop(unsigned int it, Codelet * toSig, unsigned int Start, unsigned int End, ThreadedProcedure * ParentTP, unsigned int Clusters, unsigned int Workers):
            loop(it, toSig),
            iterationStart(Start + ((End-Start)/Clusters)*it),
            iterationEnd(Start + GETEND((End-Start),Clusters,it)),
            innerLoop(0, 1, this, SHORTWAIT, toSig, 
                    GETREPS((iterationEnd-iterationStart),Workers),
                    iterationStart,
                    iterationEnd,
                    ParentTP,
                    Workers)
            {
                add(&innerLoop);
            }
        };

        unsigned int n;
        unsigned int clusters;
        unsigned int workers;
        Core core;
        codeletFor<SingleLoop> singleLoop;
        paraFor<DoubleLoop> doubleLoop;

        nestedLoop(unsigned int N, unsigned int Clusters, unsigned int Workers, unsigned int threashold1, unsigned int threashold2, ThreadedProcedure * ParentTP, Codelet * toSig):
        n(N),
        clusters(Clusters),
        workers(Workers),
        core(0,0,this,SHORTWAIT,0,N,ParentTP,toSig),
        singleLoop(0,1,this,SHORTWAIT,toSig, GETREPS(N,Workers), 0, N, ParentTP, Workers),
        doubleLoop(0,1,this,SHORTWAIT,toSig, GETREPS(N,Clusters), 0, N, ParentTP, Clusters, Workers)
        {
            if(N < threashold1)
            {
                add(&core);
            }
            else if(N < threashold2)
            {
                add(&singleLoop);
            }
            else
            {
                add(&doubleLoop);
            }
        }
    };
    
    /*template <class lp>
    class boundedParaLoop : public ThreadedProcedure
    {
        class bounded : public loop
        {
        public:
            paraFor<lp> innerLoop;

            bounded(unsigned int it, Codelet * toSig, unsigned int iter, unsigned int K):
            loop(it, toSig),
            innerLoop(0, 1, this, SHORTWAIT, toSig, 
                    GETREPS((iterationEnd-iterationStart),K),
                    iterationStart,
                    iterationEnd)
            {
                add(&innerLoop);
            }
        };
        
        unsigned int n;
        unsigned int k;
        serialFor<bounded> kLoop;
        
        boundedParaLoop(unsigned int N, unsigned int K, Codelet * toSig):
        n(N),
        k(K),
        kLoop(0, 1, this, SHORTWAIT, toSig, 
                    GETREPS(N,K),
                    0,
                    N)
        {
            add(&kLoop);
        }
    };*/
        
}

#endif	/* NESTED_H */

