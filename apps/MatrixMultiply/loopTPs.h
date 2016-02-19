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


#pragma once
#include "darts.h"
#include "loopCodelets.h"
#include "matrix.h"
using namespace darts;

class mmTile : public ThreadedProcedure
{
public:

    class iloop : public loop
    {
    public:

        class jloop : public loop
        {
        public:

            tileMult mul;

            jloop(unsigned int it, Codelet * toSig, mmArgs * ARGS, matrix * tempA, int I) :
            loop(it, toSig),
            mul(0, 0, this, it, ARGS, tempA, I, it, this)
            {
                add(&mul);
            }
        };

        matrix tempA;

        codeletFor<jloop> jl;

        iloop(unsigned int it, Codelet * toSig, int JC, mmArgs * ARGS) :
        loop(it, toSig),
        tempA(ARGS->a, it*(ARGS->iTile), 0,
        ((int)it + 1 == ARGS->iCut) ? (ARGS->iMod + ARGS->iTile) : (ARGS->iTile),
        ARGS->msk),

        jl(0, 1, this, SHORTWAIT, toSig, JC, ARGS, &tempA, it)
        {
            add(&jl);
        }
    };

    mmArgs args;
    paraFor<iloop> il;

    mmTile(matrix * A, matrix * B, matrix * C, int MSI, int MSJ, int MSK, int IC, int JC, Codelet * toSig) :
    args(A, B, C,
    MSI, MSJ, MSK,
    IC, JC),
    il(0, 1, this, SHORTWAIT, toSig, IC, JC, &args)
    {
        add(&il);
    }
};
