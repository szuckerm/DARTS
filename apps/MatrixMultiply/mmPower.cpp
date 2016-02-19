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
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include "darts.h"
#include "getClock.h"
#include "loopTPs.h"
#include "matrix.h"

using namespace darts;

uint64_t mmTest(int innerloop, int outerloop, Runtime * rt, int size, int IC, int JC)
{
    int tempI = (IC!=0) ? IC : 1;
    int tempJ = (JC!=0) ? JC : 1;

    matrix A(size,size);
    matrix B(size,size);
    matrix C(size,size);

    initRandomMatrix(&A);
    initRandomMatrix(&B);
    uint64_t innerTime = 0;
    uint64_t outerTime = 0;
    
    for(int i=0;i<outerloop;i++)
    {
        C.resetMatrix();
        rt->run(launch<mmTile>(&A,&B,&C,size,size,size,tempI,tempJ,&Runtime::finalSignal));

        for(int j=0;j<innerloop;j++)
        {
            C.resetMatrix();
            uint64_t startTime = getTime();
            rt->run(launch<mmTile>(&A,&B,&C,size,size,size,tempI,tempJ,&Runtime::finalSignal));
            uint64_t endTime = getTime();
            innerTime+=endTime-startTime;
        }
        outerTime+=innerTime/innerloop;
        innerTime = 0;
    }
    return outerTime/outerloop;
}

int main(int argc, char * argv[])
{
    if (argc != 8)
    {
        std::cout << "enter number of TP CD TPM CDM size iCut jCut" << std::endl;
        return 0;
    }
    int tps = atoi(argv[1]);
    int cds = atoi(argv[2]);
    int tpm = atoi(argv[3]);
    int cdm = atoi(argv[4]);
    int size = atoi(argv[5]);
    int iCut = atoi(argv[6]);
    int jCut = atoi(argv[7]);
    
    ThreadAffinity affin(cds, tps, SPREAD, tpm, cdm);
    if (affin.generateMask())
    {
        Runtime * rt = new Runtime(&affin);
        
        matrix A(size,size);
        matrix B(size,size);
        matrix C(size,size);

        initRandomMatrix(&A);
        initRandomMatrix(&B);
        uint64_t startTime = getTime();
        rt->run(launch<mmTile>(&A,&B,&C,size,size,size,iCut,jCut,&Runtime::finalSignal));
        uint64_t endTime = getTime();
        std::cout << endTime-startTime << std::endl;
    }
    return 0;
}