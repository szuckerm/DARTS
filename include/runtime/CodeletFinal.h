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


#ifndef CODELETFINAL_H
#define	CODELETFINAL_H
#include "Codelet.h"
namespace darts
{
    class CodeletFinal : public Codelet
    {
    private:
        Scheduler ** aliveSig;
        unsigned int numThreads;
        bool terminate;
    public:
        CodeletFinal() :
        Codelet(1, 1),
        numThreads(0),
        terminate(true){ }
        
        void setTerminate(bool cond){ terminate = cond; }
        
        bool getTerminate(void){ return terminate; }
        
        unsigned int getNumThreads(void){ return numThreads; }
        
        void addAliveSignal(size_t index, Scheduler * toAdd)
        {
            assert(index < numThreads);

            aliveSig[index] = toAdd;
        }

        void setNumThreads(size_t num)
        {
            numThreads = num;
            aliveSig = new Scheduler * [num];
            for (unsigned int i = 0; i < numThreads; i++)
                aliveSig[i] = 0;
        }

        virtual void decDep(void)
        {
            if (terminate)
            {
                for (unsigned int i = 0; i < numThreads; i++)
                {
                    aliveSig[i]->kill();
                }
                delete [] aliveSig;
            } else
                aliveSig[0]->kill();
        }

        virtual void fire(void){ };
    };

}
#endif	/* CODELETFINAL_H */

