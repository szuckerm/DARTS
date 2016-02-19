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


#ifndef MERGETP_H
#define	MERGETP_H

#include <iostream>
#include <sstream>
#include "darts.h"

using namespace darts;

class mergeSort : public ThreadedProcedure
{
public:

    class Check : public Codelet
    {
    public:
        Check(uint32_t dep, uint32_t res, ThreadedProcedure * myTP, uint32_t stat) :
        Codelet(dep, res, myTP, stat)
        {
        }

        virtual void fire(void);
    };
    
    class Merge : public Codelet
    {
    public:
        Merge(uint32_t dep, uint32_t res, ThreadedProcedure * myTP, uint32_t stat) :
        Codelet(dep, res, myTP, stat)
        {
        }

        virtual void fire(void);
    };
    
    int size;
    int base;
    int * in;
    int * out;
    
    Check check;
    Merge merge;
    Codelet * toSignal;
    
    mergeSort(int * IN, int * OUT, int SIZE, int BASE, Codelet * toSig):
    ThreadedProcedure(),
    size(SIZE),
    base(BASE),
    in(IN),
    out(OUT),
    check(0,0,this,0),
    merge(2,2,this,0),
    toSignal(toSig) 
    {
        add(&check);
    }
};

class mergeBase : public ThreadedProcedure
{
public:

    class quick : public Codelet
    {
    private:
        int * in;
        int left;
        int right;
        Codelet * toSignal;
    public:
        quick(uint32_t dep, uint32_t res, ThreadedProcedure * myTP, uint32_t stat,
                int * IN, int LEFT, int RIGHT, Codelet * toSig) :
        Codelet(dep, res, myTP, stat),
        in(IN),
        left(LEFT),
        right(RIGHT),
        toSignal(toSig)
        {
        }

        virtual void fire(void);
    };
    
    class merge : public Codelet
    {
    private:
        int * in;
        int * out;
        int size;
        Codelet * toSignal;
    public:
        merge(uint32_t dep, uint32_t res, ThreadedProcedure * myTP, uint32_t stat,
                int * IN, int * OUT, int SIZE, Codelet * toSig) :
        Codelet(dep, res, myTP, stat),
        in(IN),
        out(OUT),
        size(SIZE),
        toSignal(toSig)
        {
        }
        
        virtual void fire(void);
    };
    
    int size;
    int div;
    int last;
    int * in;
    int * out;
    
    quick quick0;
    quick quick1;
    quick quick2;
    quick quick3;
    quick quick4;
    quick quick5;
    quick quick6;
    quick quick7;
    
    merge merge01;
    merge merge23;
    merge merge45;
    merge merge67;
    
    merge merge03;
    merge merge47;
    
    merge merge07;
    
    mergeBase(int * IN, int * OUT, int SIZE, Codelet * toSig) :
    size(SIZE),
    div(SIZE/8),
    last(SIZE%8),
    in(IN),
    out(OUT),
    quick0(0,0,this,0, IN,     0,   div-1, &merge01),
    quick1(0,0,this,1, IN,   div, 2*div-1, &merge01),
    quick2(0,0,this,2, IN, 2*div, 3*div-1, &merge23),
    quick3(0,0,this,3, IN, 3*div, 4*div-1, &merge23),
    quick4(0,0,this,4, IN, 4*div, 5*div-1, &merge45),
    quick5(0,0,this,5, IN, 5*div, 6*div-1, &merge45),
    quick6(0,0,this,6, IN, 6*div, 7*div-1, &merge67),
    quick7(0,0,this,7, IN, 7*div, 8*div-1+last, &merge67),
    
    merge01(2,2,this,0, IN,           OUT,          div*2, &merge03),
    merge23(2,2,this,2, IN+   div*2,  OUT+   div*2, div*2, &merge03),
    merge45(2,2,this,4, IN+ 2*div*2,  OUT+ 2*div*2, div*2, &merge47),
    merge67(2,2,this,6, IN+ 3*div*2,  OUT+ 3*div*2, div*2+last, &merge47),
    
    merge03(2,2,this,0, OUT,          IN,           div*4, &merge07),
    merge47(2,2,this,4, OUT+   div*4, IN+   div*4,  div*4+last, &merge07),
    
    merge07(2,2,this,0, IN,             OUT,            SIZE, toSig)
    {
        add(&quick0);
        add(&quick1);
        add(&quick2);
        add(&quick3);
        add(&quick4);
        add(&quick5);
        add(&quick6);
        add(&quick7);
    }
};

class quickSort : public ThreadedProcedure
{
public:

    class quick : public Codelet
    {
    private:
        int * in;
        int left;
        int right;
        Codelet * toSignal;
    public:
        quick(uint32_t dep, uint32_t res, ThreadedProcedure * myTP, uint32_t stat,
                int * IN, int LEFT, int RIGHT, Codelet * toSig) :
        Codelet(dep, res, myTP, stat),
        in(IN),
        left(LEFT),
        right(RIGHT),
        toSignal(toSig)
        {
        }

        virtual void fire(void);
    };
    
    quick quick0;
    quick quick1; 
    
    quickSort(int * OUT, int SIZE, Codelet * toSig) :

    quick0(0,0,this,0, OUT, 0, (SIZE/2)-1, toSig),
    quick1(0,0,this,1, OUT, (SIZE/2), SIZE-1, toSig)
    {
        add(&quick0);
        add(&quick1);
    }
};
#endif	/* MERGETP_H */

