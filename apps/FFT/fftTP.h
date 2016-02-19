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


#ifndef FFTTP_H
#define	FFTTP_H

#include "fft.h"

using namespace darts;

class fftTP : public ThreadedProcedure
{
public:

    class Start : public Codelet
    {
    public:

        Start(uint32_t dep, uint32_t res, ThreadedProcedure * myTP, uint32_t stat) :
        Codelet(dep, res, myTP, stat) { }

        virtual void fire(void);
    };

    class End : public Codelet
    {
    public:

        End(uint32_t dep, uint32_t res, ThreadedProcedure * myTP, uint32_t stat) :
        Codelet(dep, res, myTP, stat) { }

        virtual void fire(void);
    };
    
    unsigned int cluster;
    unsigned int worker;
    int * factors;
    int n;
    COMPLEX * W;
    COMPLEX * in;
    COMPLEX * out;
    Start startCD;
    End endCD;
    Codelet * toSignal;
    
    fftTP(int N, COMPLEX * IN, COMPLEX * OUT, unsigned int Cluster, unsigned int Worker, Codelet * toSig):
    cluster(Cluster),
    worker(Worker),
    factors(new int[40]),
    n(N),
    W(new COMPLEX[N+1]),
    in(IN),
    out(OUT),
    startCD(0,0,this,0),
    endCD(1,1,this,0),
    toSignal(toSig)
    {
        add(&startCD);
    }
    
    ~fftTP(void)
    {
        delete [] factors;
        delete [] W;
    }
    
};

class fftauxTP : public ThreadedProcedure
{
public:

    class baseCheck : public Codelet
    {
    public:
        baseCheck(uint32_t dep, uint32_t res, ThreadedProcedure * myTP, uint32_t stat) :
        Codelet(dep, res, myTP, stat) { }
        
        virtual void fire(void);
    };

    class launchAux : public Codelet
    {
    public:
        launchAux(uint32_t dep, uint32_t res, ThreadedProcedure * myTP, uint32_t stat):
        Codelet(dep, res, myTP, stat) 
        { 
        }
        
        virtual void fire(void);
    };
    
    class launchTwiddle : public Codelet
    {
    public:

        launchTwiddle(uint32_t dep, uint32_t res, ThreadedProcedure * myTP, uint32_t stat) :
        Codelet(dep, res, myTP, stat) { }

        virtual void fire(void);
    };
    
    unsigned int cluster;
    unsigned int worker;
    int n;
    int nW;
    int r;
    int m;
    int * factors;
    COMPLEX * in;
    COMPLEX * out;
    COMPLEX * W;
    
    baseCheck checkCD;
    launchAux auxCD;
    launchTwiddle twiddleCD;
    Codelet * toSignal;
    
    fftauxTP(int N, COMPLEX * IN, COMPLEX * OUT, int * Factors, COMPLEX * w, int NW, unsigned int Cluster, unsigned int Worker, Codelet * toSig):
    cluster(Cluster),
    worker(Worker),
    n(N),
    nW(NW),
    r(0),
    m(0),
    factors(Factors),
    in(IN),
    out(OUT),
    W(w),
    checkCD(0,0,this,0),
    auxCD(1,1,this,0),
    twiddleCD(static_cast<unsigned int>(*factors),static_cast<unsigned int>(*factors),this,0),
    toSignal(toSig)
    {
        add(&checkCD);
    }
};


class fftBase128 : public ThreadedProcedure
{
public:

	class empty : public Codelet
	{
	public:
		empty(uint32_t dep, uint32_t res, ThreadedProcedure * myTP, uint32_t stat):
		Codelet(dep,res,myTP,stat){}
		void fire(void);		
	};

    class unshuffle2 : public Codelet
    {
    private:
        unsigned int start;
        unsigned int end;
        unsigned int inStart;
        COMPLEX * in;
        COMPLEX * out;
        Codelet * toSignal1;
        Codelet * toSignal2;
    public:

        unshuffle2(uint32_t dep, uint32_t res, ThreadedProcedure * myTP, uint32_t stat,
                unsigned int Start, unsigned int End, unsigned InStart, COMPLEX * IN, COMPLEX * OUT, Codelet * toSig1, Codelet * toSig2) :
        Codelet(dep, res, myTP, stat),
        start(Start),
        end(End),
        inStart(InStart),
        in(IN),
        out(OUT),
        toSignal1(toSig1),
        toSignal2(toSig2)
        {
        }
        void fire(void);
    };

    
    class fftBase32 : public Codelet
    {
    private:
        unsigned int start;
        unsigned int end;
        unsigned int inStart;
        COMPLEX * in;
        COMPLEX * out;
        Codelet * toSignal;
    public:
        fftBase32(uint32_t dep, uint32_t res, ThreadedProcedure * myTP, uint32_t stat, 
                unsigned int Start, unsigned int End, unsigned InStart, COMPLEX * IN, COMPLEX * OUT, Codelet * toSig):
        Codelet(dep, res, myTP, stat),
        start(Start),
        end(End),
        inStart(InStart),
        in(IN),
        out(OUT),
        toSignal(toSig)
        {
        }
        void fire(void);
    };
    
    class twiddle2 : public Codelet
    {
    private:
        int m;
        COMPLEX * in;
        COMPLEX * out;
        Codelet * toSignal;
    public:

        twiddle2(uint32_t dep, uint32_t res, ThreadedProcedure * myTP, uint32_t stat, int M, COMPLEX * IN, COMPLEX * OUT, Codelet * toSig) :
        Codelet(dep, res, myTP, stat),
        m(M),
        in(IN),
        out(OUT),
        toSignal(toSig)
        {
        }
        void fire(void);
    };
    
    int n;
    int nW;
    COMPLEX * in;
    COMPLEX tempSpace[3*128];
    COMPLEX * out;
    COMPLEX * W;
    
    //empty starter;

    unshuffle2 ul128;
    unshuffle2 ur128;
    
    fftBase32 ll64;
    fftBase32 lr64;
    
    fftBase32 rl64;
    fftBase32 rr64;
    
    twiddle2 tl64;
    twiddle2 tr64;
    twiddle2 t128;
    
    fftBase128(int N, COMPLEX * IN, COMPLEX * OUT, COMPLEX * w, int NW, Codelet * toSig):
    n(N),
    nW(NW),
    in(IN),
    out(OUT),
    W(w),
    //starter(0,0,this,0),
    ul128(0,0,this,0,0,64,0,in,tempSpace,&ll64,&lr64),    
    ur128(0,0,this,1,64,128,1,in,tempSpace,&rl64,&rr64),
    
    ll64(1,1,this,0,128,160,0,tempSpace,tempSpace,&tl64),
    lr64(1,1,this,2,160,192,1,tempSpace,tempSpace,&tl64),
    
    rl64(1,1,this,1,192,224,64,tempSpace,tempSpace,&tr64),
    rr64(1,1,this,3,224,256,65,tempSpace,tempSpace,&tr64),
    
    tl64(2,2,this,0,32,tempSpace+256,tempSpace+128,&t128),
    tr64(2,2,this,1,32,tempSpace+320,tempSpace+192,&t128),
    
    t128(2,2,this,1,64,tempSpace+128,out,toSig)
    {
        add(&ul128);
        add(&ur128);
	//add(&starter);
    }
};

class fftBase256 : public ThreadedProcedure
{
public:

    class unshuffle2 : public Codelet
    {
    private:
        unsigned int start;
        unsigned int end;
        unsigned int inStart;
        COMPLEX * in;
        COMPLEX * out;
        Codelet * toSignal1;
        Codelet * toSignal2;
    public:

        unshuffle2(uint32_t dep, uint32_t res, ThreadedProcedure * myTP, uint32_t stat,
                unsigned int Start, unsigned int End, unsigned InStart, COMPLEX * IN, COMPLEX * OUT, Codelet * toSig1, Codelet * toSig2) :
        Codelet(dep, res, myTP, stat),
        start(Start),
        end(End),
        inStart(InStart),
        in(IN),
        out(OUT),
        toSignal1(toSig1),
        toSignal2(toSig2)
        {
        }
        void fire(void);
    };

    
    class fftBase32 : public Codelet
    {
    private:
        unsigned int start;
        unsigned int end;
        unsigned int inStart;
        COMPLEX * in;
        COMPLEX * out;
        Codelet * toSignal;
    public:
        fftBase32(uint32_t dep, uint32_t res, ThreadedProcedure * myTP, uint32_t stat, 
                unsigned int Start, unsigned int End, unsigned InStart, COMPLEX * IN, COMPLEX * OUT, Codelet * toSig):
        Codelet(dep, res, myTP, stat),
        start(Start),
        end(End),
        inStart(InStart),
        in(IN),
        out(OUT),
        toSignal(toSig)
        {
        }
        void fire(void);
    };
    
    class twiddle2 : public Codelet
    {
    private:
        int m;
        COMPLEX * in;
        COMPLEX * out;
        Codelet * toSignal;
    public:

        twiddle2(uint32_t dep, uint32_t res, ThreadedProcedure * myTP, uint32_t stat, int M, COMPLEX * IN, COMPLEX * OUT, Codelet * toSig) :
        Codelet(dep, res, myTP, stat),
        m(M),
        in(IN),
        out(OUT),
        toSignal(toSig)
        {
        }
        void fire(void);
    };
    
    int n;
    int nW;
    COMPLEX * in;
    COMPLEX tempSpace[4*256];
    COMPLEX * out;
    COMPLEX * W;
    
    unshuffle2 ul256;
    unshuffle2 ur256;
    
    unshuffle2 ull128;
    unshuffle2 ulr128;
    
    unshuffle2 url128;
    unshuffle2 urr128;
    
    fftBase32 lll64;
    fftBase32 llr64;
    
    fftBase32 lrl64;
    fftBase32 lrr64;
    
    fftBase32 rll64;
    fftBase32 rlr64;
    
    fftBase32 rrl64;
    fftBase32 rrr64;
    
    twiddle2 tll64;
    twiddle2 tlr64;
    twiddle2 trl64;
    twiddle2 trr64;
    twiddle2 tl128;
    twiddle2 tr128;
    twiddle2 t256;
    
    fftBase256(int N, COMPLEX * IN, COMPLEX * OUT, COMPLEX * w, int NW, Codelet * toSig):
    n(N),
    nW(NW),
    in(IN),
    out(OUT),
    W(w),
    
    ul256(0,0,this,0,0,128,0,in,tempSpace,&ull128,&ulr128),
    ur256(0,0,this,1,128,256,1,in,tempSpace,&url128,&urr128),
    
    ull128(1,1,this,0,256,320,0,tempSpace,tempSpace,&lll64,&llr64),
    ulr128(1,1,this,2,320,384,1,tempSpace,tempSpace,&lrl64,&lrr64),
    
    url128(1,1,this,1,384,448,256,tempSpace,tempSpace,&rll64,&rlr64),
    urr128(1,1,this,3,448,512,257,tempSpace,tempSpace,&rrl64,&rrr64),
    
    lll64(1,1,this,0,512,544,384,tempSpace,tempSpace,&tll64),
    llr64(1,1,this,4,544,576,385,tempSpace,tempSpace,&tll64),
    
    lrl64(1,1,this,2,576,608,512,tempSpace,tempSpace,&tlr64),
    lrr64(1,1,this,5,608,640,513,tempSpace,tempSpace,&tlr64),
    
    rll64(1,1,this,1,640,672,576,tempSpace,tempSpace,&trl64),
    rlr64(1,1,this,6,672,704,577,tempSpace,tempSpace,&trl64),
    
    rrl64(1,1,this,3,704,736,640,tempSpace,tempSpace,&trr64),
    rrr64(1,1,this,7,736,768,641,tempSpace,tempSpace,&trr64),
    
    tll64(2,2,this,0,32,tempSpace+512,tempSpace+256,&tl128),
    tlr64(2,2,this,2,32,tempSpace+576,tempSpace+320,&tl128),
    trl64(2,2,this,1,32,tempSpace+640,tempSpace+384,&tr128),
    trr64(2,2,this,3,32,tempSpace+704,tempSpace+448,&tr128),
    tl128(2,2,this,0,64,tempSpace+256,tempSpace,&t256),
    tr128(2,2,this,1,64,tempSpace+384,tempSpace+128,&t256),
    t256(2,2,this,1,128,tempSpace,out,toSig)
    {
        add(&ul256);
        add(&ur256);
    }
};

class baseCore : public Codelet
{
protected:
    unsigned start;
    unsigned end;
    ThreadedProcedure * parentTP;
    Codelet * toSignal;
public:

    baseCore(uint32_t dep, uint32_t res, ThreadedProcedure * myTP, uint32_t stat,
            unsigned int Start, unsigned int End, ThreadedProcedure * ParentTP, Codelet * toSig) :
    Codelet(dep, res, myTP, stat),
    start(Start),
    end(End),
    parentTP(ParentTP),
    toSignal(toSig)
    {
    }
};

class computeWCoefficients : public baseCore
{
public:
    computeWCoefficients(uint32_t dep, uint32_t res, ThreadedProcedure * myTP, uint32_t stat,
            unsigned int Start, unsigned int End, ThreadedProcedure * ParentTP, Codelet * toSig) :
    baseCore(dep,res,myTP,stat,Start,End,ParentTP,toSig) { }
    void fire(void);
};

class Unshuffle : public baseCore
{
public:
    Unshuffle(uint32_t dep, uint32_t res, ThreadedProcedure * myTP, uint32_t stat,
            unsigned int Start, unsigned int End, ThreadedProcedure * ParentTP, Codelet * toSig) :
    baseCore(dep, res, myTP, stat, Start, End, ParentTP, toSig) { }
    void fire(void);
};

class Twiddle : public baseCore
{
public:
    Twiddle(uint32_t dep, uint32_t res, ThreadedProcedure * myTP, uint32_t stat,
            unsigned int Start, unsigned int End, ThreadedProcedure * ParentTP, Codelet * toSig) :
    baseCore(dep, res, myTP, stat, Start, End, ParentTP, toSig) { }
    void fire(void);
};

template<class Core>
class NestedLoop : public ThreadedProcedure
{
public:

    class SingleLoop : public loop
    {
    public:
        unsigned int iterationStart;
        unsigned int iterationEnd;
        Core core;

        SingleLoop(unsigned int it, Codelet * toSig, unsigned int Start, unsigned int End, ThreadedProcedure * ParentTP, unsigned int Workers) :
        loop(it, toSig),
        iterationStart(Start + ((End - Start) / Workers) * it),
        iterationEnd(Start + GETEND((End - Start), Workers, it)),
        core(0, 0, this, it,
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

        DoubleLoop(unsigned int it, Codelet * toSig, unsigned int Start, unsigned int End, ThreadedProcedure * ParentTP, unsigned int Clusters, unsigned int Workers) :
        loop(it, toSig),
        iterationStart(Start + ((End - Start) / Clusters) * it),
        iterationEnd(Start + GETEND((End - Start), Clusters, it)),
        innerLoop(0, 1, this, 0, toSig,
        GETREPS((iterationEnd - iterationStart), Workers),
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

    NestedLoop(unsigned int N, unsigned int Clusters, unsigned int Workers, unsigned int threashold1, unsigned int threashold2, ThreadedProcedure * ParentTP, Codelet * toSig) :
    n(N),
    clusters(Clusters),
    workers(Workers),
    core(0, 0, this, 0, 0, N, ParentTP, toSig),
    singleLoop(0, 1, this, 0, toSig, GETREPS(N, Workers), 0, N, ParentTP, Workers),
    doubleLoop(0, 1, this, 0, toSig, GETREPS(N, Clusters), 0, N, ParentTP, Clusters, Workers)
    {
        if (N < threashold1)
        {
            add(&core);
        } else if (N < threashold2)
        {
            add(&singleLoop);
        } else
        {
            add(&doubleLoop);
        }
    }
};

#endif	/* FFTTP_H */

