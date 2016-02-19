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


#ifndef LOOPCLOSURE_H
#define	LOOPCLOSURE_H

namespace darts
{
    class ThreadedProcedure;
    class ABCScheduler;
    struct lpClosure;

    typedef ThreadedProcedure * (*lpfactory) (void*, lpClosure*);

    struct lpClosure
    {
        lpfactory factory;
        unsigned int iter;
        Codelet * toSignal;
        
        lpClosure(void)
        {
        }

        lpClosure(lpfactory tpf,  unsigned int it, Codelet * toSig) :
        factory(tpf), iter(it), toSignal(toSig)
        {
        }
        
        virtual lpClosure * clone(void) { return new lpClosure( *this ); }
	virtual ~lpClosure(void) {}
    };

    template< class arg1 >
    struct lpClosure1 : lpClosure
    {
        arg1 a1;
        
        lpClosure1(void)
        {
        }

        lpClosure1(lpfactory tpf,  unsigned int it, Codelet * toSig,
                arg1 A1) :
        lpClosure(tpf,it,toSig),
        a1(A1)
        {
        }
        
        virtual lpClosure1 * clone(void) { return new lpClosure1( *this ); }
	virtual ~lpClosure1(void) {}
    };

    template< class arg1, class arg2 >
    struct lpClosure2 : lpClosure
    {
        arg1 a1;
        arg2 a2;

        lpClosure2(void)
        {
        }

        lpClosure2(lpfactory tpf,  unsigned int it, Codelet * toSig,
                arg1 A1, arg2 A2) :
        lpClosure(tpf,it,toSig),
        a1(A1), a2(A2)
        {
        }
        
        virtual lpClosure2 * clone(void) { return new lpClosure2( *this ); }
	virtual ~lpClosure2(void) {}
    };

    template< class arg1, class arg2, class arg3 >
    struct lpClosure3 : lpClosure
    {
        arg1 a1;
        arg2 a2;
        arg3 a3;

        lpClosure3(void)
        {
        }

        lpClosure3(lpfactory tpf,  unsigned int it, Codelet * toSig,
                arg1 A1, arg2 A2, arg3 A3) :
        lpClosure(tpf,it,toSig),
        a1(A1), a2(A2), a3(A3)
        {
        }
        
        virtual lpClosure3 * clone(void) { return new lpClosure3( *this ); }
	virtual ~lpClosure3(void) {}
    };

    template< class arg1, class arg2, class arg3, class arg4 >
    struct lpClosure4 : lpClosure
    {
        arg1 a1;
        arg2 a2;
        arg3 a3;
        arg4 a4;

        lpClosure4(void)
        {
        }

        lpClosure4(lpfactory tpf,  unsigned int it, Codelet * toSig,
                arg1 A1, arg2 A2, arg3 A3, arg4 A4) :
        lpClosure(tpf,it,toSig),
        a1(A1), a2(A2), a3(A3), a4(A4)
        {
        }
        
        virtual lpClosure4 * clone(void) { return new lpClosure4( *this ); }
	virtual ~lpClosure4(void) {}
    };

    template< class arg1, class arg2, class arg3, class arg4, class arg5 >
    struct lpClosure5 : lpClosure
    {
        arg1 a1;
        arg2 a2;
        arg3 a3;
        arg4 a4;
        arg5 a5;

        lpClosure5(void)
        {
        }

        lpClosure5(lpfactory tpf,  unsigned int it, Codelet * toSig,
                arg1 A1, arg2 A2, arg3 A3, arg4 A4, arg5 A5) :
        lpClosure(tpf,it,toSig),
        a1(A1), a2(A2), a3(A3), a4(A4), a5(A5)
        {
        }
        
        virtual lpClosure5 * clone(void) { return new lpClosure5( *this ); }
	virtual ~lpClosure5(void) {}
    };

    template< class arg1, class arg2, class arg3, class arg4, class arg5,
    class arg6 >
    struct lpClosure6 : lpClosure
    {
        arg1 a1;
        arg2 a2;
        arg3 a3;
        arg4 a4;
        arg5 a5;
        arg6 a6;

        lpClosure6(void)
        {
        }

        lpClosure6(lpfactory tpf,  unsigned int it, Codelet * toSig,
                arg1 A1, arg2 A2, arg3 A3, arg4 A4, arg5 A5,
                arg6 A6) :
        lpClosure(tpf,it,toSig),
        a1(A1), a2(A2), a3(A3), a4(A4), a5(A5),
        a6(A6)
        {
        }
        
        virtual lpClosure6 * clone(void) { return new lpClosure6( *this ); }
	virtual ~lpClosure6(void) {}
    };

    template< class arg1, class arg2, class arg3, class arg4, class arg5,
    class arg6, class arg7 >
    struct lpClosure7 : lpClosure
    {
        arg1 a1;
        arg2 a2;
        arg3 a3;
        arg4 a4;
        arg5 a5;
        arg6 a6;
        arg7 a7;

        lpClosure7(void)
        {
        }

        lpClosure7(lpfactory tpf,  unsigned int it, Codelet * toSig,
                arg1 A1, arg2 A2, arg3 A3, arg4 A4, arg5 A5,
                arg6 A6, arg7 A7) :
        lpClosure(tpf,it,toSig),
        a1(A1), a2(A2), a3(A3), a4(A4), a5(A5),
        a6(A6), a7(A7)
        {
        }
        
        virtual lpClosure7 * clone(void) { return new lpClosure7( *this ); }
	virtual ~lpClosure7(void) {}
    };

    template< class arg1, class arg2, class arg3, class arg4, class arg5,
    class arg6, class arg7, class arg8 >
    struct lpClosure8 : lpClosure
    {
        arg1 a1;
        arg2 a2;
        arg3 a3;
        arg4 a4;
        arg5 a5;
        arg6 a6;
        arg7 a7;
        arg8 a8;

        lpClosure8(void)
        {
        }

        lpClosure8(lpfactory tpf,  unsigned int it, Codelet * toSig,
                arg1 A1, arg2 A2, arg3 A3, arg4 A4, arg5 A5,
                arg6 A6, arg7 A7, arg8 A8) :
        lpClosure(tpf,it,toSig),
        a1(A1), a2(A2), a3(A3), a4(A4), a5(A5),
        a6(A6), a7(A7), a8(A8)
        {
        }
        
        virtual lpClosure8 * clone(void) { return new lpClosure8( *this ); }
	virtual ~lpClosure8(void) {}
    };

    template< class arg1, class arg2, class arg3, class arg4, class arg5,
    class arg6, class arg7, class arg8, class arg9 >
    struct lpClosure9 : lpClosure
    {
        arg1 a1;
        arg2 a2;
        arg3 a3;
        arg4 a4;
        arg5 a5;
        arg6 a6;
        arg7 a7;
        arg8 a8;
        arg9 a9;

        lpClosure9(void)
        {
        }

        lpClosure9(lpfactory tpf,  unsigned int it, Codelet * toSig,
                arg1 A1, arg2 A2, arg3 A3, arg4 A4, arg5 A5,
                arg6 A6, arg7 A7, arg8 A8, arg9 A9) :
        lpClosure(tpf,it,toSig),
        a1(A1), a2(A2), a3(A3), a4(A4), a5(A5),
        a6(A6), a7(A7), a8(A8), a9(A9)
        {
        }
        
        virtual lpClosure9 * clone(void) { return new lpClosure9( *this ); }
	virtual ~lpClosure9(void) {}
    };

    template< class arg1, class arg2, class arg3, class arg4, class arg5,
    class arg6, class arg7, class arg8, class arg9, class arg10 >
    struct lpClosure10 : lpClosure
    {
        arg1 a1;
        arg2 a2;
        arg3 a3;
        arg4 a4;
        arg5 a5;
        arg6 a6;
        arg7 a7;
        arg8 a8;
        arg9 a9;
        arg10 a10;

        lpClosure10(void)
        {
        }

        lpClosure10(lpfactory tpf,  unsigned int it, Codelet * toSig,
                arg1 A1, arg2 A2, arg3 A3, arg4 A4, arg5 A5,
                arg6 A6, arg7 A7, arg8 A8, arg9 A9, arg10 A10) :
        lpClosure(tpf,it,toSig),
        a1(A1), a2(A2), a3(A3), a4(A4), a5(A5),
        a6(A6), a7(A7), a8(A8), a9(A9), a10(A10)
        {
        }
        
        virtual lpClosure10 * clone(void) { return new lpClosure10( *this ); }
	virtual ~lpClosure10(void) {}
    };

    template< class arg1, class arg2, class arg3, class arg4, class arg5,
    class arg6, class arg7, class arg8, class arg9, class arg10,
    class arg11 >
    struct lpClosure11 : lpClosure
    {
        arg1 a1;
        arg2 a2;
        arg3 a3;
        arg4 a4;
        arg5 a5;
        arg6 a6;
        arg7 a7;
        arg8 a8;
        arg9 a9;
        arg10 a10;
        arg11 a11;

        lpClosure11(void)
        {
        }

        lpClosure11(lpfactory tpf,  unsigned int it, Codelet * toSig,
                arg1 A1, arg2 A2, arg3 A3, arg4 A4, arg5 A5,
                arg6 A6, arg7 A7, arg8 A8, arg9 A9, arg10 A10,
                arg11 A11) :
        lpClosure(tpf,it,toSig),
        a1(A1), a2(A2), a3(A3), a4(A4), a5(A5),
        a6(A6), a7(A7), a8(A8), a9(A9), a10(A10),
        a11(A11)
        {
        }
        
        virtual lpClosure11 * clone(void) { return new lpClosure11( *this ); }
	virtual ~lpClosure11(void) {}
    };

    template< class arg1, class arg2, class arg3, class arg4, class arg5,
    class arg6, class arg7, class arg8, class arg9, class arg10,
    class arg11, class arg12 >
    struct lpClosure12 : lpClosure
    {
        arg1 a1;
        arg2 a2;
        arg3 a3;
        arg4 a4;
        arg5 a5;
        arg6 a6;
        arg7 a7;
        arg8 a8;
        arg9 a9;
        arg10 a10;
        arg11 a11;
        arg12 a12;

        lpClosure12(void)
        {
        }

        lpClosure12(lpfactory tpf,  unsigned int it, Codelet * toSig,
                arg1 A1, arg2 A2, arg3 A3, arg4 A4, arg5 A5,
                arg6 A6, arg7 A7, arg8 A8, arg9 A9, arg10 A10,
                arg11 A11, arg12 A12) :
        lpClosure(tpf,it,toSig),
        a1(A1), a2(A2), a3(A3), a4(A4), a5(A5),
        a6(A6), a7(A7), a8(A8), a9(A9), a10(A10),
        a11(A11), a12(A12)
        {
        }
        
        virtual lpClosure12 * clone(void) { return new lpClosure12( *this ); }
	virtual ~lpClosure12(void) {}
    };

    template< class arg1, class arg2, class arg3, class arg4, class arg5,
    class arg6, class arg7, class arg8, class arg9, class arg10,
    class arg11, class arg12, class arg13 >
    struct lpClosure13 : lpClosure
    {
        arg1 a1;
        arg2 a2;
        arg3 a3;
        arg4 a4;
        arg5 a5;
        arg6 a6;
        arg7 a7;
        arg8 a8;
        arg9 a9;
        arg10 a10;
        arg11 a11;
        arg12 a12;
        arg13 a13;

        lpClosure13(void)
        {
        }

        lpClosure13(lpfactory tpf,  unsigned int it, Codelet * toSig,
                arg1 A1, arg2 A2, arg3 A3, arg4 A4, arg5 A5,
                arg6 A6, arg7 A7, arg8 A8, arg9 A9, arg10 A10,
                arg11 A11, arg12 A12, arg13 A13) :
        lpClosure(tpf,it,toSig),
        a1(A1), a2(A2), a3(A3), a4(A4), a5(A5),
        a6(A6), a7(A7), a8(A8), a9(A9), a10(A10),
        a11(A11), a12(A12), a13(A13)
        {
        }
        
        virtual lpClosure13 * clone(void) { return new lpClosure13( *this ); }
	virtual ~lpClosure13(void) {}
    };

    template< class arg1, class arg2, class arg3, class arg4, class arg5,
    class arg6, class arg7, class arg8, class arg9, class arg10,
    class arg11, class arg12, class arg13, class arg14 >
    struct lpClosure14 : lpClosure
    {
        arg1 a1;
        arg2 a2;
        arg3 a3;
        arg4 a4;
        arg5 a5;
        arg6 a6;
        arg7 a7;
        arg8 a8;
        arg9 a9;
        arg10 a10;
        arg11 a11;
        arg12 a12;
        arg13 a13;
        arg14 a14;

        lpClosure14(void)
        {
        }

        lpClosure14(lpfactory tpf,  unsigned int it, Codelet * toSig,
                arg1 A1, arg2 A2, arg3 A3, arg4 A4, arg5 A5,
                arg6 A6, arg7 A7, arg8 A8, arg9 A9, arg10 A10,
                arg11 A11, arg12 A12, arg13 A13, arg14 A14) :
        lpClosure(tpf,it,toSig),
        a1(A1), a2(A2), a3(A3), a4(A4), a5(A5),
        a6(A6), a7(A7), a8(A8), a9(A9), a10(A10),
        a11(A11), a12(A12), a13(A13), a14(A14)
        {
        }
        
        virtual lpClosure14 * clone(void) { return new lpClosure14( *this ); }
	virtual ~lpClosure14(void) {}
    };

    template< class arg1, class arg2, class arg3, class arg4, class arg5,
    class arg6, class arg7, class arg8, class arg9, class arg10,
    class arg11, class arg12, class arg13, class arg14, class arg15 >
    struct lpClosure15 : lpClosure
    {
        arg1 a1;
        arg2 a2;
        arg3 a3;
        arg4 a4;
        arg5 a5;
        arg6 a6;
        arg7 a7;
        arg8 a8;
        arg9 a9;
        arg10 a10;
        arg11 a11;
        arg12 a12;
        arg13 a13;
        arg14 a14;
        arg15 a15;

        lpClosure15(void)
        {
        }

        lpClosure15(lpfactory tpf,  unsigned int it, Codelet * toSig,
                arg1 A1, arg2 A2, arg3 A3, arg4 A4, arg5 A5,
                arg6 A6, arg7 A7, arg8 A8, arg9 A9, arg10 A10,
                arg11 A11, arg12 A12, arg13 A13, arg14 A14, arg15 A15) :
        lpClosure(tpf,it,toSig),
        a1(A1), a2(A2), a3(A3), a4(A4), a5(A5),
        a6(A6), a7(A7), a8(A8), a9(A9), a10(A10),
        a11(A11), a12(A12), a13(A13), a14(A14), a15(A15)
        {
        }
        
        virtual lpClosure15 * clone(void) { return new lpClosure15( *this ); }
	virtual ~lpClosure15(void) {}
    };

    template< class arg1, class arg2, class arg3, class arg4, class arg5,
    class arg6, class arg7, class arg8, class arg9, class arg10,
    class arg11, class arg12, class arg13, class arg14, class arg15,
    class arg16 >
    struct lpClosure16 : lpClosure
    {
        arg1 a1;
        arg2 a2;
        arg3 a3;
        arg4 a4;
        arg5 a5;
        arg6 a6;
        arg7 a7;
        arg8 a8;
        arg9 a9;
        arg10 a10;
        arg11 a11;
        arg12 a12;
        arg13 a13;
        arg14 a14;
        arg15 a15;
        arg16 a16;

        lpClosure16(void)
        {
        }

        lpClosure16(lpfactory tpf,  unsigned int it, Codelet * toSig,
                arg1 A1, arg2 A2, arg3 A3, arg4 A4, arg5 A5,
                arg6 A6, arg7 A7, arg8 A8, arg9 A9, arg10 A10,
                arg11 A11, arg12 A12, arg13 A13, arg14 A14, arg15 A15,
                arg16 A16) :
        lpClosure(tpf,it,toSig),
        a1(A1), a2(A2), a3(A3), a4(A4), a5(A5),
        a6(A6), a7(A7), a8(A8), a9(A9), a10(A10),
        a11(A11), a12(A12), a13(A13), a14(A14), a15(A15),
        a16(A16)
        {
        }
        
        virtual lpClosure16 * clone(void) { return new lpClosure16( *this ); }
	virtual ~lpClosure16(void) {}
    };

    template< class arg1, class arg2, class arg3, class arg4, class arg5,
    class arg6, class arg7, class arg8, class arg9, class arg10,
    class arg11, class arg12, class arg13, class arg14, class arg15,
    class arg16, class arg17 >
    struct lpClosure17 : lpClosure
    {
        arg1 a1;
        arg2 a2;
        arg3 a3;
        arg4 a4;
        arg5 a5;
        arg6 a6;
        arg7 a7;
        arg8 a8;
        arg9 a9;
        arg10 a10;
        arg11 a11;
        arg12 a12;
        arg13 a13;
        arg14 a14;
        arg15 a15;
        arg16 a16;
        arg17 a17;

        lpClosure17(void)
        {
        }

        lpClosure17(lpfactory tpf,  unsigned int it, Codelet * toSig,
                arg1 A1, arg2 A2, arg3 A3, arg4 A4, arg5 A5,
                arg6 A6, arg7 A7, arg8 A8, arg9 A9, arg10 A10,
                arg11 A11, arg12 A12, arg13 A13, arg14 A14, arg15 A15,
                arg16 A16, arg17 A17) :
        lpClosure(tpf,it,toSig),
        a1(A1), a2(A2), a3(A3), a4(A4), a5(A5),
        a6(A6), a7(A7), a8(A8), a9(A9), a10(A10),
        a11(A11), a12(A12), a13(A13), a14(A14), a15(A15),
        a16(A16), a17(A17)
        {
        }
        
        virtual lpClosure17 * clone(void) { return new lpClosure17( *this ); }
	virtual ~lpClosure17(void) {}
    };

    template< class arg1, class arg2, class arg3, class arg4, class arg5,
    class arg6, class arg7, class arg8, class arg9, class arg10,
    class arg11, class arg12, class arg13, class arg14, class arg15,
    class arg16, class arg17, class arg18 >
    struct lpClosure18 : lpClosure
    {
        arg1 a1;
        arg2 a2;
        arg3 a3;
        arg4 a4;
        arg5 a5;
        arg6 a6;
        arg7 a7;
        arg8 a8;
        arg9 a9;
        arg10 a10;
        arg11 a11;
        arg12 a12;
        arg13 a13;
        arg14 a14;
        arg15 a15;
        arg16 a16;
        arg17 a17;
        arg18 a18;

        lpClosure18(void)
        {
        }

        lpClosure18(lpfactory tpf,  unsigned int it, Codelet * toSig,
                arg1 A1, arg2 A2, arg3 A3, arg4 A4, arg5 A5,
                arg6 A6, arg7 A7, arg8 A8, arg9 A9, arg10 A10,
                arg11 A11, arg12 A12, arg13 A13, arg14 A14, arg15 A15,
                arg16 A16, arg17 A17, arg18 A18) :
        lpClosure(tpf,it,toSig),
        a1(A1), a2(A2), a3(A3), a4(A4), a5(A5),
        a6(A6), a7(A7), a8(A8), a9(A9), a10(A10),
        a11(A11), a12(A12), a13(A13), a14(A14), a15(A15),
        a16(A16), a17(A17), a18(A18)
        {
        }
        
        virtual lpClosure18 * clone(void) { return new lpClosure18( *this ); }
	virtual ~lpClosure18(void) {}
    };

    template< class arg1, class arg2, class arg3, class arg4, class arg5,
    class arg6, class arg7, class arg8, class arg9, class arg10,
    class arg11, class arg12, class arg13, class arg14, class arg15,
    class arg16, class arg17, class arg18, class arg19 >
    struct lpClosure19 : lpClosure
    {
        arg1 a1;
        arg2 a2;
        arg3 a3;
        arg4 a4;
        arg5 a5;
        arg6 a6;
        arg7 a7;
        arg8 a8;
        arg9 a9;
        arg10 a10;
        arg11 a11;
        arg12 a12;
        arg13 a13;
        arg14 a14;
        arg15 a15;
        arg16 a16;
        arg17 a17;
        arg18 a18;
        arg19 a19;

        lpClosure19(void)
        {
        }

        lpClosure19(lpfactory tpf,  unsigned int it, Codelet * toSig,
                arg1 A1, arg2 A2, arg3 A3, arg4 A4, arg5 A5,
                arg6 A6, arg7 A7, arg8 A8, arg9 A9, arg10 A10,
                arg11 A11, arg12 A12, arg13 A13, arg14 A14, arg15 A15,
                arg16 A16, arg17 A17, arg18 A18, arg19 A19) :
        lpClosure(tpf,it,toSig),
        a1(A1), a2(A2), a3(A3), a4(A4), a5(A5),
        a6(A6), a7(A7), a8(A8), a9(A9), a10(A10),
        a11(A11), a12(A12), a13(A13), a14(A14), a15(A15),
        a16(A16), a17(A17), a18(A18), a19(A19)
        {
        }
        
        virtual lpClosure19 * clone(void) { return new lpClosure19( *this ); }
	virtual ~lpClosure19(void) {}
    };

    template< class arg1, class arg2, class arg3, class arg4, class arg5,
    class arg6, class arg7, class arg8, class arg9, class arg10,
    class arg11, class arg12, class arg13, class arg14, class arg15,
    class arg16, class arg17, class arg18, class arg19, class arg20 >
    struct lpClosure20 : lpClosure
    {
        arg1 a1;
        arg2 a2;
        arg3 a3;
        arg4 a4;
        arg5 a5;
        arg6 a6;
        arg7 a7;
        arg8 a8;
        arg9 a9;
        arg10 a10;
        arg11 a11;
        arg12 a12;
        arg13 a13;
        arg14 a14;
        arg15 a15;
        arg16 a16;
        arg17 a17;
        arg18 a18;
        arg19 a19;
        arg20 a20;

        lpClosure20(void)
        {
        }

        lpClosure20(lpfactory tpf,  unsigned int it, Codelet * toSig,
                arg1 A1, arg2 A2, arg3 A3, arg4 A4, arg5 A5,
                arg6 A6, arg7 A7, arg8 A8, arg9 A9, arg10 A10,
                arg11 A11, arg12 A12, arg13 A13, arg14 A14, arg15 A15,
                arg16 A16, arg17 A17, arg18 A18, arg19 A19, arg20 A20) :
        lpClosure(tpf,it,toSig),
        a1(A1), a2(A2), a3(A3), a4(A4), a5(A5),
        a6(A6), a7(A7), a8(A8), a9(A9), a10(A10),
        a11(A11), a12(A12), a13(A13), a14(A14), a15(A15),
        a16(A16), a17(A17), a18(A18), a19(A19), a20(A20)
        {
        }
        
        virtual lpClosure20 * clone(void) { return new lpClosure20( *this ); }
	virtual ~lpClosure20(void) {}
    };

    template< class arg1, class arg2, class arg3, class arg4, class arg5,
    class arg6, class arg7, class arg8, class arg9, class arg10,
    class arg11, class arg12, class arg13, class arg14, class arg15,
    class arg16, class arg17, class arg18, class arg19, class arg20,
    class arg21 >
    struct lpClosure21 : lpClosure
    {
        arg1 a1;
        arg2 a2;
        arg3 a3;
        arg4 a4;
        arg5 a5;
        arg6 a6;
        arg7 a7;
        arg8 a8;
        arg9 a9;
        arg10 a10;
        arg11 a11;
        arg12 a12;
        arg13 a13;
        arg14 a14;
        arg15 a15;
        arg16 a16;
        arg17 a17;
        arg18 a18;
        arg19 a19;
        arg20 a20;
        arg21 a21;

        lpClosure21(void)
        {
        }

        lpClosure21(lpfactory tpf,  unsigned int it, Codelet * toSig,
                arg1 A1, arg2 A2, arg3 A3, arg4 A4, arg5 A5,
                arg6 A6, arg7 A7, arg8 A8, arg9 A9, arg10 A10,
                arg11 A11, arg12 A12, arg13 A13, arg14 A14, arg15 A15,
                arg16 A16, arg17 A17, arg18 A18, arg19 A19, arg20 A20,
                arg21 A21) :
        lpClosure(tpf,it,toSig),
        a1(A1), a2(A2), a3(A3), a4(A4), a5(A5),
        a6(A6), a7(A7), a8(A8), a9(A9), a10(A10),
        a11(A11), a12(A12), a13(A13), a14(A14), a15(A15),
        a16(A16), a17(A17), a18(A18), a19(A19), a20(A20),
        a21(A21)
        {
        }
        
        virtual lpClosure21 * clone(void) { return new lpClosure21( *this ); }
	virtual ~lpClosure21(void) {}
    };

    template< class arg1, class arg2, class arg3, class arg4, class arg5,
    class arg6, class arg7, class arg8, class arg9, class arg10,
    class arg11, class arg12, class arg13, class arg14, class arg15,
    class arg16, class arg17, class arg18, class arg19, class arg20,
    class arg21, class arg22 >
    struct lpClosure22 : lpClosure
    {
        arg1 a1;
        arg2 a2;
        arg3 a3;
        arg4 a4;
        arg5 a5;
        arg6 a6;
        arg7 a7;
        arg8 a8;
        arg9 a9;
        arg10 a10;
        arg11 a11;
        arg12 a12;
        arg13 a13;
        arg14 a14;
        arg15 a15;
        arg16 a16;
        arg17 a17;
        arg18 a18;
        arg19 a19;
        arg20 a20;
        arg21 a21;
        arg22 a22;

        lpClosure22(void)
        {
        }

        lpClosure22(lpfactory tpf,  unsigned int it, Codelet * toSig,
                arg1 A1, arg2 A2, arg3 A3, arg4 A4, arg5 A5,
                arg6 A6, arg7 A7, arg8 A8, arg9 A9, arg10 A10,
                arg11 A11, arg12 A12, arg13 A13, arg14 A14, arg15 A15,
                arg16 A16, arg17 A17, arg18 A18, arg19 A19, arg20 A20,
                arg21 A21, arg22 A22) :
        lpClosure(tpf,it,toSig),
        a1(A1), a2(A2), a3(A3), a4(A4), a5(A5),
        a6(A6), a7(A7), a8(A8), a9(A9), a10(A10),
        a11(A11), a12(A12), a13(A13), a14(A14), a15(A15),
        a16(A16), a17(A17), a18(A18), a19(A19), a20(A20),
        a21(A21), a22(A22)
        {
        }
        
        virtual lpClosure22 * clone(void) { return new lpClosure22( *this ); }
	virtual ~lpClosure22(void) {}
    };

    template< class arg1, class arg2, class arg3, class arg4, class arg5,
    class arg6, class arg7, class arg8, class arg9, class arg10,
    class arg11, class arg12, class arg13, class arg14, class arg15,
    class arg16, class arg17, class arg18, class arg19, class arg20,
    class arg21, class arg22, class arg23 >
    struct lpClosure23 : lpClosure
    {
        arg1 a1;
        arg2 a2;
        arg3 a3;
        arg4 a4;
        arg5 a5;
        arg6 a6;
        arg7 a7;
        arg8 a8;
        arg9 a9;
        arg10 a10;
        arg11 a11;
        arg12 a12;
        arg13 a13;
        arg14 a14;
        arg15 a15;
        arg16 a16;
        arg17 a17;
        arg18 a18;
        arg19 a19;
        arg20 a20;
        arg21 a21;
        arg22 a22;
        arg23 a23;

        lpClosure23(void)
        {
        }

        lpClosure23(lpfactory tpf,  unsigned int it, Codelet * toSig,
                arg1 A1, arg2 A2, arg3 A3, arg4 A4, arg5 A5,
                arg6 A6, arg7 A7, arg8 A8, arg9 A9, arg10 A10,
                arg11 A11, arg12 A12, arg13 A13, arg14 A14, arg15 A15,
                arg16 A16, arg17 A17, arg18 A18, arg19 A19, arg20 A20,
                arg21 A21, arg22 A22, arg23 A23) :
        lpClosure(tpf,it,toSig),
        a1(A1), a2(A2), a3(A3), a4(A4), a5(A5),
        a6(A6), a7(A7), a8(A8), a9(A9), a10(A10),
        a11(A11), a12(A12), a13(A13), a14(A14), a15(A15),
        a16(A16), a17(A17), a18(A18), a19(A19), a20(A20),
        a21(A21), a22(A22), a23(A23)
        {
        }
        
        virtual lpClosure23 * clone(void) { return new lpClosure23( *this ); }
	virtual ~lpClosure23(void) {}
    };

    template< class arg1, class arg2, class arg3, class arg4, class arg5,
    class arg6, class arg7, class arg8, class arg9, class arg10,
    class arg11, class arg12, class arg13, class arg14, class arg15,
    class arg16, class arg17, class arg18, class arg19, class arg20,
    class arg21, class arg22, class arg23, class arg24 >
    struct lpClosure24 : lpClosure
    {
        arg1 a1;
        arg2 a2;
        arg3 a3;
        arg4 a4;
        arg5 a5;
        arg6 a6;
        arg7 a7;
        arg8 a8;
        arg9 a9;
        arg10 a10;
        arg11 a11;
        arg12 a12;
        arg13 a13;
        arg14 a14;
        arg15 a15;
        arg16 a16;
        arg17 a17;
        arg18 a18;
        arg19 a19;
        arg20 a20;
        arg21 a21;
        arg22 a22;
        arg23 a23;
        arg24 a24;

        lpClosure24(void)
        {
        }

        lpClosure24(lpfactory tpf,  unsigned int it, Codelet * toSig,
                arg1 A1, arg2 A2, arg3 A3, arg4 A4, arg5 A5,
                arg6 A6, arg7 A7, arg8 A8, arg9 A9, arg10 A10,
                arg11 A11, arg12 A12, arg13 A13, arg14 A14, arg15 A15,
                arg16 A16, arg17 A17, arg18 A18, arg19 A19, arg20 A20,
                arg21 A21, arg22 A22, arg23 A23, arg24 A24) :
        lpClosure(tpf,it,toSig),
        a1(A1), a2(A2), a3(A3), a4(A4), a5(A5),
        a6(A6), a7(A7), a8(A8), a9(A9), a10(A10),
        a11(A11), a12(A12), a13(A13), a14(A14), a15(A15),
        a16(A16), a17(A17), a18(A18), a19(A19), a20(A20),
        a21(A21), a22(A22), a23(A23), a24(A24)
        {
        }
        
        virtual lpClosure24 * clone(void) { return new lpClosure24( *this ); }
	virtual ~lpClosure24(void) {}
    };

    template< class arg1, class arg2, class arg3, class arg4, class arg5,
    class arg6, class arg7, class arg8, class arg9, class arg10,
    class arg11, class arg12, class arg13, class arg14, class arg15,
    class arg16, class arg17, class arg18, class arg19, class arg20,
    class arg21, class arg22, class arg23, class arg24, class arg25 >
    struct lpClosure25 : lpClosure
    {
        arg1 a1;
        arg2 a2;
        arg3 a3;
        arg4 a4;
        arg5 a5;
        arg6 a6;
        arg7 a7;
        arg8 a8;
        arg9 a9;
        arg10 a10;
        arg11 a11;
        arg12 a12;
        arg13 a13;
        arg14 a14;
        arg15 a15;
        arg16 a16;
        arg17 a17;
        arg18 a18;
        arg19 a19;
        arg20 a20;
        arg21 a21;
        arg22 a22;
        arg23 a23;
        arg24 a24;
        arg25 a25;

        lpClosure25(void)
        {
        }

        lpClosure25(lpfactory tpf,  unsigned int it, Codelet * toSig,
                arg1 A1, arg2 A2, arg3 A3, arg4 A4, arg5 A5,
                arg6 A6, arg7 A7, arg8 A8, arg9 A9, arg10 A10,
                arg11 A11, arg12 A12, arg13 A13, arg14 A14, arg15 A15,
                arg16 A16, arg17 A17, arg18 A18, arg19 A19, arg20 A20,
                arg21 A21, arg22 A22, arg23 A23, arg24 A24, arg25 A25) :
        lpClosure(tpf,it,toSig),
        a1(A1), a2(A2), a3(A3), a4(A4), a5(A5),
        a6(A6), a7(A7), a8(A8), a9(A9), a10(A10),
        a11(A11), a12(A12), a13(A13), a14(A14), a15(A15),
        a16(A16), a17(A17), a18(A18), a19(A19), a20(A20),
        a21(A21), a22(A22), a23(A23), a24(A24), a25(A25)
        {
        }
        
        virtual lpClosure25 * clone(void) { return new lpClosure25( *this ); }
	virtual ~lpClosure25(void) {}
    };

    template< class arg1, class arg2, class arg3, class arg4, class arg5,
    class arg6, class arg7, class arg8, class arg9, class arg10,
    class arg11, class arg12, class arg13, class arg14, class arg15,
    class arg16, class arg17, class arg18, class arg19, class arg20,
    class arg21, class arg22, class arg23, class arg24, class arg25,
    class arg26 >
    struct lpClosure26 : lpClosure
    {
        arg1 a1;
        arg2 a2;
        arg3 a3;
        arg4 a4;
        arg5 a5;
        arg6 a6;
        arg7 a7;
        arg8 a8;
        arg9 a9;
        arg10 a10;
        arg11 a11;
        arg12 a12;
        arg13 a13;
        arg14 a14;
        arg15 a15;
        arg16 a16;
        arg17 a17;
        arg18 a18;
        arg19 a19;
        arg20 a20;
        arg21 a21;
        arg22 a22;
        arg23 a23;
        arg24 a24;
        arg25 a25;
        arg26 a26;

        lpClosure26(void)
        {
        }

        lpClosure26(lpfactory tpf,  unsigned int it, Codelet * toSig,
                arg1 A1, arg2 A2, arg3 A3, arg4 A4, arg5 A5,
                arg6 A6, arg7 A7, arg8 A8, arg9 A9, arg10 A10,
                arg11 A11, arg12 A12, arg13 A13, arg14 A14, arg15 A15,
                arg16 A16, arg17 A17, arg18 A18, arg19 A19, arg20 A20,
                arg21 A21, arg22 A22, arg23 A23, arg24 A24, arg25 A25,
                arg26 A26) :
        lpClosure(tpf,it,toSig),
        a1(A1), a2(A2), a3(A3), a4(A4), a5(A5),
        a6(A6), a7(A7), a8(A8), a9(A9), a10(A10),
        a11(A11), a12(A12), a13(A13), a14(A14), a15(A15),
        a16(A16), a17(A17), a18(A18), a19(A19), a20(A20),
        a21(A21), a22(A22), a23(A23), a24(A24), a25(A25),
        a26(A26)
        {
        }
        
        virtual lpClosure26 * clone(void) { return new lpClosure26( *this ); }
	virtual ~lpClosure26(void) {}
    };

    template< class arg1, class arg2, class arg3, class arg4, class arg5,
    class arg6, class arg7, class arg8, class arg9, class arg10,
    class arg11, class arg12, class arg13, class arg14, class arg15,
    class arg16, class arg17, class arg18, class arg19, class arg20,
    class arg21, class arg22, class arg23, class arg24, class arg25,
    class arg26, class arg27 >
    struct lpClosure27 : lpClosure
    {
        arg1 a1;
        arg2 a2;
        arg3 a3;
        arg4 a4;
        arg5 a5;
        arg6 a6;
        arg7 a7;
        arg8 a8;
        arg9 a9;
        arg10 a10;
        arg11 a11;
        arg12 a12;
        arg13 a13;
        arg14 a14;
        arg15 a15;
        arg16 a16;
        arg17 a17;
        arg18 a18;
        arg19 a19;
        arg20 a20;
        arg21 a21;
        arg22 a22;
        arg23 a23;
        arg24 a24;
        arg25 a25;
        arg26 a26;
        arg27 a27;

        lpClosure27(void)
        {
        }

        lpClosure27(lpfactory tpf,  unsigned int it, Codelet * toSig,
                arg1 A1, arg2 A2, arg3 A3, arg4 A4, arg5 A5,
                arg6 A6, arg7 A7, arg8 A8, arg9 A9, arg10 A10,
                arg11 A11, arg12 A12, arg13 A13, arg14 A14, arg15 A15,
                arg16 A16, arg17 A17, arg18 A18, arg19 A19, arg20 A20,
                arg21 A21, arg22 A22, arg23 A23, arg24 A24, arg25 A25,
                arg26 A26, arg27 A27) :
        lpClosure(tpf,it,toSig),
        a1(A1), a2(A2), a3(A3), a4(A4), a5(A5),
        a6(A6), a7(A7), a8(A8), a9(A9), a10(A10),
        a11(A11), a12(A12), a13(A13), a14(A14), a15(A15),
        a16(A16), a17(A17), a18(A18), a19(A19), a20(A20),
        a21(A21), a22(A22), a23(A23), a24(A24), a25(A25),
        a26(A26), a27(A27)
        {
        }
        
        virtual lpClosure27 * clone(void) { return new lpClosure27( *this ); }
	virtual ~lpClosure27(void) {}
    };

    template< class arg1, class arg2, class arg3, class arg4, class arg5,
    class arg6, class arg7, class arg8, class arg9, class arg10,
    class arg11, class arg12, class arg13, class arg14, class arg15,
    class arg16, class arg17, class arg18, class arg19, class arg20,
    class arg21, class arg22, class arg23, class arg24, class arg25,
    class arg26, class arg27, class arg28 >
    struct lpClosure28 : lpClosure
    {
        arg1 a1;
        arg2 a2;
        arg3 a3;
        arg4 a4;
        arg5 a5;
        arg6 a6;
        arg7 a7;
        arg8 a8;
        arg9 a9;
        arg10 a10;
        arg11 a11;
        arg12 a12;
        arg13 a13;
        arg14 a14;
        arg15 a15;
        arg16 a16;
        arg17 a17;
        arg18 a18;
        arg19 a19;
        arg20 a20;
        arg21 a21;
        arg22 a22;
        arg23 a23;
        arg24 a24;
        arg25 a25;
        arg26 a26;
        arg27 a27;
        arg28 a28;

        lpClosure28(void)
        {
        }

        lpClosure28(lpfactory tpf,  unsigned int it, Codelet * toSig,
                arg1 A1, arg2 A2, arg3 A3, arg4 A4, arg5 A5,
                arg6 A6, arg7 A7, arg8 A8, arg9 A9, arg10 A10,
                arg11 A11, arg12 A12, arg13 A13, arg14 A14, arg15 A15,
                arg16 A16, arg17 A17, arg18 A18, arg19 A19, arg20 A20,
                arg21 A21, arg22 A22, arg23 A23, arg24 A24, arg25 A25,
                arg26 A26, arg27 A27, arg28 A28) :
        lpClosure(tpf,it,toSig),
        a1(A1), a2(A2), a3(A3), a4(A4), a5(A5),
        a6(A6), a7(A7), a8(A8), a9(A9), a10(A10),
        a11(A11), a12(A12), a13(A13), a14(A14), a15(A15),
        a16(A16), a17(A17), a18(A18), a19(A19), a20(A20),
        a21(A21), a22(A22), a23(A23), a24(A24), a25(A25),
        a26(A26), a27(A27), a28(A28)
        {
        }
        
        virtual lpClosure28 * clone(void) { return new lpClosure28( *this ); }
	virtual ~lpClosure28(void) {}
    };

    template< class arg1, class arg2, class arg3, class arg4, class arg5,
    class arg6, class arg7, class arg8, class arg9, class arg10,
    class arg11, class arg12, class arg13, class arg14, class arg15,
    class arg16, class arg17, class arg18, class arg19, class arg20,
    class arg21, class arg22, class arg23, class arg24, class arg25,
    class arg26, class arg27, class arg28, class arg29 >
    struct lpClosure29 : lpClosure
    {
        arg1 a1;
        arg2 a2;
        arg3 a3;
        arg4 a4;
        arg5 a5;
        arg6 a6;
        arg7 a7;
        arg8 a8;
        arg9 a9;
        arg10 a10;
        arg11 a11;
        arg12 a12;
        arg13 a13;
        arg14 a14;
        arg15 a15;
        arg16 a16;
        arg17 a17;
        arg18 a18;
        arg19 a19;
        arg20 a20;
        arg21 a21;
        arg22 a22;
        arg23 a23;
        arg24 a24;
        arg25 a25;
        arg26 a26;
        arg27 a27;
        arg28 a28;
        arg29 a29;

        lpClosure29(void)
        {
        }

        lpClosure29(lpfactory tpf,  unsigned int it, Codelet * toSig,
                arg1 A1, arg2 A2, arg3 A3, arg4 A4, arg5 A5,
                arg6 A6, arg7 A7, arg8 A8, arg9 A9, arg10 A10,
                arg11 A11, arg12 A12, arg13 A13, arg14 A14, arg15 A15,
                arg16 A16, arg17 A17, arg18 A18, arg19 A19, arg20 A20,
                arg21 A21, arg22 A22, arg23 A23, arg24 A24, arg25 A25,
                arg26 A26, arg27 A27, arg28 A28, arg29 A29) :
        lpClosure(tpf,it,toSig),
        a1(A1), a2(A2), a3(A3), a4(A4), a5(A5),
        a6(A6), a7(A7), a8(A8), a9(A9), a10(A10),
        a11(A11), a12(A12), a13(A13), a14(A14), a15(A15),
        a16(A16), a17(A17), a18(A18), a19(A19), a20(A20),
        a21(A21), a22(A22), a23(A23), a24(A24), a25(A25),
        a26(A26), a27(A27), a28(A28), a29(A29)
        {
        }
        
        virtual lpClosure29 * clone(void) { return new lpClosure29( *this ); }
	virtual ~lpClosure29(void) {}
    };

    template< class arg1, class arg2, class arg3, class arg4, class arg5,
    class arg6, class arg7, class arg8, class arg9, class arg10,
    class arg11, class arg12, class arg13, class arg14, class arg15,
    class arg16, class arg17, class arg18, class arg19, class arg20,
    class arg21, class arg22, class arg23, class arg24, class arg25,
    class arg26, class arg27, class arg28, class arg29, class arg30 >
    struct lpClosure30 : lpClosure
    {
        arg1 a1;
        arg2 a2;
        arg3 a3;
        arg4 a4;
        arg5 a5;
        arg6 a6;
        arg7 a7;
        arg8 a8;
        arg9 a9;
        arg10 a10;
        arg11 a11;
        arg12 a12;
        arg13 a13;
        arg14 a14;
        arg15 a15;
        arg16 a16;
        arg17 a17;
        arg18 a18;
        arg19 a19;
        arg20 a20;
        arg21 a21;
        arg22 a22;
        arg23 a23;
        arg24 a24;
        arg25 a25;
        arg26 a26;
        arg27 a27;
        arg28 a28;
        arg29 a29;
        arg30 a30;

        lpClosure30(void)
        {
        }

        lpClosure30(lpfactory tpf,  unsigned int it, Codelet * toSig,
                arg1 A1, arg2 A2, arg3 A3, arg4 A4, arg5 A5,
                arg6 A6, arg7 A7, arg8 A8, arg9 A9, arg10 A10,
                arg11 A11, arg12 A12, arg13 A13, arg14 A14, arg15 A15,
                arg16 A16, arg17 A17, arg18 A18, arg19 A19, arg20 A20,
                arg21 A21, arg22 A22, arg23 A23, arg24 A24, arg25 A25,
                arg26 A26, arg27 A27, arg28 A28, arg29 A29, arg30 A30) :
        lpClosure(tpf,it,toSig),
        a1(A1), a2(A2), a3(A3), a4(A4), a5(A5),
        a6(A6), a7(A7), a8(A8), a9(A9), a10(A10),
        a11(A11), a12(A12), a13(A13), a14(A14), a15(A15),
        a16(A16), a17(A17), a18(A18), a19(A19), a20(A20),
        a21(A21), a22(A22), a23(A23), a24(A24), a25(A25),
        a26(A26), a27(A27), a28(A28), a29(A29), a30(A30)
        {
        }
        
        virtual lpClosure30 * clone(void) { return new lpClosure30( *this ); }
	virtual ~lpClosure30(void) {}
    };

    template< class arg1, class arg2, class arg3, class arg4, class arg5,
    class arg6, class arg7, class arg8, class arg9, class arg10,
    class arg11, class arg12, class arg13, class arg14, class arg15,
    class arg16, class arg17, class arg18, class arg19, class arg20,
    class arg21, class arg22, class arg23, class arg24, class arg25,
    class arg26, class arg27, class arg28, class arg29, class arg30,
    class arg31 >
    struct lpClosure31 : lpClosure
    {
        arg1 a1;
        arg2 a2;
        arg3 a3;
        arg4 a4;
        arg5 a5;
        arg6 a6;
        arg7 a7;
        arg8 a8;
        arg9 a9;
        arg10 a10;
        arg11 a11;
        arg12 a12;
        arg13 a13;
        arg14 a14;
        arg15 a15;
        arg16 a16;
        arg17 a17;
        arg18 a18;
        arg19 a19;
        arg20 a20;
        arg21 a21;
        arg22 a22;
        arg23 a23;
        arg24 a24;
        arg25 a25;
        arg26 a26;
        arg27 a27;
        arg28 a28;
        arg29 a29;
        arg30 a30;
        arg31 a31;

        lpClosure31(void)
        {
        }

        lpClosure31(lpfactory tpf,  unsigned int it, Codelet * toSig,
                arg1 A1, arg2 A2, arg3 A3, arg4 A4, arg5 A5,
                arg6 A6, arg7 A7, arg8 A8, arg9 A9, arg10 A10,
                arg11 A11, arg12 A12, arg13 A13, arg14 A14, arg15 A15,
                arg16 A16, arg17 A17, arg18 A18, arg19 A19, arg20 A20,
                arg21 A21, arg22 A22, arg23 A23, arg24 A24, arg25 A25,
                arg26 A26, arg27 A27, arg28 A28, arg29 A29, arg30 A30,
                arg31 A31) :
        lpClosure(tpf,it,toSig),
        a1(A1), a2(A2), a3(A3), a4(A4), a5(A5),
        a6(A6), a7(A7), a8(A8), a9(A9), a10(A10),
        a11(A11), a12(A12), a13(A13), a14(A14), a15(A15),
        a16(A16), a17(A17), a18(A18), a19(A19), a20(A20),
        a21(A21), a22(A22), a23(A23), a24(A24), a25(A25),
        a26(A26), a27(A27), a28(A28), a29(A29), a30(A30),
        a31(A31)
        {
        }
        
        virtual lpClosure31 * clone(void) { return new lpClosure31( *this ); }
	virtual ~lpClosure31(void) {}
    };

    template< class arg1, class arg2, class arg3, class arg4, class arg5,
    class arg6, class arg7, class arg8, class arg9, class arg10,
    class arg11, class arg12, class arg13, class arg14, class arg15,
    class arg16, class arg17, class arg18, class arg19, class arg20,
    class arg21, class arg22, class arg23, class arg24, class arg25,
    class arg26, class arg27, class arg28, class arg29, class arg30,
    class arg31, class arg32 >
    struct lpClosure32 : lpClosure
    {
        arg1 a1;
        arg2 a2;
        arg3 a3;
        arg4 a4;
        arg5 a5;
        arg6 a6;
        arg7 a7;
        arg8 a8;
        arg9 a9;
        arg10 a10;
        arg11 a11;
        arg12 a12;
        arg13 a13;
        arg14 a14;
        arg15 a15;
        arg16 a16;
        arg17 a17;
        arg18 a18;
        arg19 a19;
        arg20 a20;
        arg21 a21;
        arg22 a22;
        arg23 a23;
        arg24 a24;
        arg25 a25;
        arg26 a26;
        arg27 a27;
        arg28 a28;
        arg29 a29;
        arg30 a30;
        arg31 a31;
        arg32 a32;

        lpClosure32(void)
        {
        }

        lpClosure32(lpfactory tpf,  unsigned int it, Codelet * toSig,
                arg1 A1, arg2 A2, arg3 A3, arg4 A4, arg5 A5,
                arg6 A6, arg7 A7, arg8 A8, arg9 A9, arg10 A10,
                arg11 A11, arg12 A12, arg13 A13, arg14 A14, arg15 A15,
                arg16 A16, arg17 A17, arg18 A18, arg19 A19, arg20 A20,
                arg21 A21, arg22 A22, arg23 A23, arg24 A24, arg25 A25,
                arg26 A26, arg27 A27, arg28 A28, arg29 A29, arg30 A30,
                arg31 A31, arg32 A32) :
        lpClosure(tpf,it,toSig),
        a1(A1), a2(A2), a3(A3), a4(A4), a5(A5),
        a6(A6), a7(A7), a8(A8), a9(A9), a10(A10),
        a11(A11), a12(A12), a13(A13), a14(A14), a15(A15),
        a16(A16), a17(A17), a18(A18), a19(A19), a20(A20),
        a21(A21), a22(A22), a23(A23), a24(A24), a25(A25),
        a26(A26), a27(A27), a28(A28), a29(A29), a30(A30),
        a31(A31), a32(A32)
        {
        }
        
        virtual lpClosure32 * clone(void) { return new lpClosure32( *this ); }
	virtual ~lpClosure32(void) {}
    };




}

#endif	/* LOOPCLOSURE_H */
