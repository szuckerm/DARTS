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
#include <stdlib.h>
#include <stdint.h>

#include <math.h>
#include <stdlib.h>
#include <string.h>

#include "fft.h"
#include "fftTP.h"
#include "getClock.h"
#include "darts.h"

#define INNER 10
#define OUTER 10

using namespace darts;

void initFFT(COMPLEX * in, int size)
{
    for(int i=0; i<size; i++)
    {
        c_re(in[i]) = 1.0;
        c_im(in[i]) = 1.0;
    }
}

int main(int argc, char * argv[])
{
    if (argc != 6)
    {
        std::cout << "enter number of TP CD TPM CDM Size (Power of two)" << std::endl;
        return 0;
    }
    int tps = atoi(argv[1]);
    int cds = atoi(argv[2]);
    int tpm = atoi(argv[3]);
    int cdm = atoi(argv[4]);
    int size = atoi(argv[5]);
    
    ThreadAffinity affin(cds, tps, SPREAD, tpm, cdm);
    if (affin.generateMask())
    {
        Runtime * rt = new Runtime(&affin);
        
        int cluster = tps;
        int worker = cds + 1;
        COMPLEX * in = new COMPLEX[size];
        COMPLEX * out = new COMPLEX[size];

        uint64_t innerTime = 0;
        uint64_t outerTime = 0;

        for(int i=0;i<OUTER;i++)
        {
            initFFT(in, size);
            rt->run(launch<fftTP >(size, in, out, cluster, worker, &Runtime::finalSignal));

            for(int i=0;i<INNER;i++)
            {
               initFFT(in, size);
                uint64_t startTime = getTime();
                rt->run(launch<fftTP >(size, in, out, cluster, worker, &Runtime::finalSignal));
                uint64_t endTime = getTime();
                innerTime+=endTime-startTime;
            }
            outerTime+=innerTime/INNER;
            innerTime = 0;
        }
        delete [] in;
        delete [] out;
        
        std::cout << outerTime/OUTER << std::endl;
    }
    
    return 0;
}