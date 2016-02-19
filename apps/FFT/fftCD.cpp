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

using namespace darts;

void fftTP::Start::fire(void)
{
    fftTP * myFFT = static_cast<fftTP*> (myTP_);
    invoke<NestedLoop< computeWCoefficients> > (myFFT, myFFT->n/2, myFFT->cluster, myFFT->worker, THREASHOLD1, THREASHOLD2, myFFT, &myFFT->endCD);
}

void fftTP::End::fire()
{
    fftTP * myFFT = static_cast<fftTP*> (myTP_);
    int *p = myFFT->factors;
#ifdef BASE_128
    int l = myFFT->n/128;
#else
    int l = myFFT->n/256;
#endif
    int r;

    while(l>1)
    {
      r = factor_128(l);
      *p++ = r;
      l /= r;
    }
    
#ifdef BASE_128
    *p++=128;
    if(myFFT->n==128)
    {       
	invoke<fftBase128> (myFFT, myFFT->n, myFFT->in, myFFT->out, myFFT->W, myFFT->n, myFFT->toSignal);
    }
#else
    *p++ = 256;
    if(myFFT->n==256)
        invoke<fftBase256> (myFFT, myFFT->n, myFFT->in, myFFT->out, myFFT->W, myFFT->n, myFFT->toSignal);
#endif  
    else
    {       
	invoke<fftauxTP> (myFFT, myFFT->n, myFFT->in, myFFT->out, myFFT->factors, myFFT->W, myFFT->n, myFFT->cluster, myFFT->worker,myFFT->toSignal);   
    }
}

void fftauxTP::baseCheck::fire()
{
    fftauxTP * myAux = static_cast<fftauxTP*> (myTP_);
    if (myAux->n == 32)
    {
        fft_base_32(myAux->in, myAux->out);
        myAux->toSignal->decDep();
        return;
    }
    if (myAux->n == 16)
    {
        fft_base_16(myAux->in, myAux->out);
        myAux->toSignal->decDep();
        return;
    }
    if (myAux->n == 8)
    {
        fft_base_8(myAux->in, myAux->out);
        myAux->toSignal->decDep();
        return;
    }
    if (myAux->n == 4)
    {
        fft_base_4(myAux->in, myAux->out);
        myAux->toSignal->decDep();
        return;
    }
    if (myAux->n == 2)
    {
        fft_base_2(myAux->in, myAux->out);
        myAux->toSignal->decDep();
        return;
    }

    myAux->r = *myAux->factors;
    myAux->m = myAux->n / myAux->r;
    if (myAux->r < myAux->n)
    {
        invoke<NestedLoop< Unshuffle> > (myAux, myAux->m, myAux->cluster, myAux->worker, THREASHOLD1, THREASHOLD2, myAux, &myAux->auxCD);
    } 
    else
        myAux->twiddleCD.decDep();
}

void fftauxTP::launchAux::fire()
{
    fftauxTP * myAux = static_cast<fftauxTP*> (myTP_);
    for(int k = 0; k < myAux->n; k+=myAux->m)
    {
        if (myAux->m == 128)
        {
            invoke<fftBase128 > (myAux, myAux->m, myAux->out + k, myAux->in + k, myAux->W, myAux->nW, &myAux->twiddleCD);
        } 
        else
        {
            invoke<fftauxTP > (myAux, myAux->m, myAux->out + k, myAux->in + k, myAux->factors + 1, myAux->W, myAux->nW, myAux->cluster, myAux->worker, &myAux->twiddleCD);
        }
    }
}

void fftauxTP::launchTwiddle::fire()
{
    fftauxTP * myAux = static_cast<fftauxTP*> (myTP_);
    invoke<NestedLoop< Twiddle > > (myAux, myAux->m, myAux->cluster, myAux->worker, THREASHOLD1, THREASHOLD2, myAux, myAux->toSignal);
}

void computeWCoefficients::fire(void)
{
    fftTP * myCWC = static_cast<fftTP*>(parentTP);
    register double twoPiOverN;
    register unsigned int k;
    register REAL s, c;
    twoPiOverN = 2.0 * 3.1415926535897932384626434 / myCWC->n;
    
    for (k = start; k <= end; ++k)
    {
        c = cos(twoPiOverN * k);
        c_re(myCWC->W[k]) = c_re(myCWC->W[myCWC->n - k]) = c;
        s = sin(twoPiOverN * k);
        c_im(myCWC->W[k]) = -s;
        c_im(myCWC->W[myCWC->n - k]) = s;
    }
    toSignal->decDep();
}

void Unshuffle::fire(void)
{
    fftauxTP * myAux = static_cast<fftauxTP*>(parentTP);
    if (myAux->r == 32)
    {
        fft_unshuffle_32(start, end, myAux->in, myAux->out, myAux->m);
    }
    else if (myAux->r == 16)
    {
        fft_unshuffle_16(start, end, myAux->in, myAux->out, myAux->m);
    }
    else if (myAux->r == 8)
    {
        fft_unshuffle_8(start, end, myAux->in, myAux->out, myAux->m);
    }
    else if (myAux->r == 4)
    {
        fft_unshuffle_4(start, end, myAux->in, myAux->out, myAux->m);
    }
    else if (myAux->r == 2)
    {
        fft_unshuffle_2(start, end, myAux->in, myAux->out, myAux->m);
    }
    else
        unshuffle(start, end, myAux->in, myAux->out, myAux->r, myAux->m);
    toSignal->decDep();
}

void Twiddle::fire(void)
{
    fftauxTP * myAux = static_cast<fftauxTP*> (parentTP);
    
    if (myAux->r == 2)
    {
        fft_twiddle_2(start, end, myAux->in, myAux->out, myAux->W, myAux->nW, myAux->nW / myAux->n, myAux->m);
    } 
    else if (myAux->r == 4)
    {
        fft_twiddle_4(start, end, myAux->in, myAux->out, myAux->W, myAux->nW, myAux->nW / myAux->n, myAux->m);
    } 
    else if (myAux->r == 8)
    {
        fft_twiddle_8(start, end, myAux->in, myAux->out, myAux->W, myAux->nW, myAux->nW / myAux->n, myAux->m);
    } 
    else if (myAux->r == 16)
    {
        fft_twiddle_16(start, end, myAux->in, myAux->out, myAux->W, myAux->nW, myAux->nW / myAux->n, myAux->m);
    } 
    else if (myAux->r == 32)
    {
        fft_twiddle_32(start, end, myAux->in, myAux->out, myAux->W, myAux->nW, myAux->nW / myAux->n, myAux->m);
    } 
    else
    {
        fft_twiddle_gen(start, end, myAux->in, myAux->out, myAux->W, myAux->nW, myAux->nW / myAux->n, myAux->r, myAux->m);
    }
    toSignal->decDep();
}

void fftBase128::empty::fire(void)
{
	fftBase128 * my128 = static_cast<fftBase128*> (myTP_);
	my128->ul128.decDep();
	my128->ur128.decDep();
}

void fftBase128::unshuffle2::fire(void)
{
    for(unsigned int i=start; i < end; i++)
    {
        out[i] = in[inStart];
        inStart+=2;
    }
    toSignal1->decDep();
    toSignal2->decDep();
}

void  fftBase128::fftBase32::fire(void)
{
    for(unsigned int i=start; i < end; i++)
    {
        out[i] = in[inStart];
        inStart+=2;
    }
    
    fft_base_32(&in[start], &out[start+128]);
    toSignal->decDep();
}

void fftBase128::twiddle2::fire(void)
{
    fftBase128 * myBase = static_cast<fftBase128*>(myTP_);
    fft_twiddle_2(0, m, in, out, myBase->W, myBase->nW, myBase->nW / myBase->n, m);
    toSignal->decDep();
}

void fftBase256::unshuffle2::fire(void)
{
    for(unsigned int i=start; i < end; i++)
    {
        out[i] = in[inStart];
    }
    toSignal1->decDep();
    toSignal2->decDep();
}

void  fftBase256::fftBase32::fire(void)
{
    for(unsigned int i=start; i < end; i++)
    {
        out[i] = in[inStart];
        inStart+=2;
    }
    
    fft_base_32(&in[start], &out[start+128]);
    toSignal->decDep();
}

void fftBase256::twiddle2::fire(void)
{
    fftBase256 * myBase = static_cast<fftBase256*>(myTP_);
    fft_twiddle_2(0, m, in, out, myBase->W, myBase->nW, myBase->nW / myBase->n, m);
    toSignal->decDep();
}
