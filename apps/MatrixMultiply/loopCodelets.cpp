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


#include "loopCodelets.h"
#include "loopTPs.h"
#include "matrix.h"
#include <assert.h>

#define MYTP(X) X * my##X = static_cast<X*>(myTP_)
#ifndef MIN
	#define MIN(X,Y) (X < Y) ? (X) : (Y)
#endif
#define SCRATCH 524288

using namespace darts;
void
tileMult::fire(void)
{
    INT tempISize = (i + 1 == args->iCut) ? (args->iTile + args->iMod) : (args->iTile);
    INT tempJSize = (j + 1 == args->jCut) ? (args->jTile + args->jMod) : (args->jTile);
#ifdef MKL
    matrix C(tempISize, tempJSize);
#else
    matrix C(tempJSize, tempISize);
#endif
    DGEMM(tempISize,
          tempJSize,
          args->msk,
          1,
          A->getPtr(),
          A->getN(),
          &args->b->getPtr()[j * args->jTile],
          args->b->getN(),
          0,
          C.getPtr(),
          C.getN());
#ifdef MKL
    copyMatrix(args->c, &C, i * args->iTile, j * args->jTile);
#else
    copyMatrix(args->c, &C, j * args->jTile, i * args->iTile);
#endif
    
    myLoop->toSignal->decDep();
}
