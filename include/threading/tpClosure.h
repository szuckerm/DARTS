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


#ifndef TPCLOSURE_H
#define	TPCLOSURE_H
namespace darts
{
    class ThreadedProcedure;
    struct tpClosure;

    typedef ThreadedProcedure * (*tpfactory) (tpClosure*);

    struct tpClosure
    {
        tpfactory factory;
        ThreadedProcedure * parent;

        tpClosure(void)
        {
        }

        tpClosure(tpfactory tpf, ThreadedProcedure * daddy) :
        factory(tpf), parent(daddy)
        {
        }
        
        virtual tpClosure * clone(void) { return new tpClosure( *this ); }
    	virtual ~tpClosure(void){}
    };

    template< class arg1 >
    struct tpClosure1 : tpClosure
    {
        arg1 a1;
        
        tpClosure1(void)
        {
        }

        tpClosure1(tpfactory tpf, ThreadedProcedure * daddy,
                arg1 A1) :
        tpClosure(tpf, daddy),
        a1(A1)
        {
        }
        
        virtual tpClosure1 * clone(void) { return new tpClosure1( *this ); }
    	virtual ~tpClosure1(void){}
    };

    template< class arg1, class arg2 >
    struct tpClosure2 : tpClosure
    {
        arg1 a1;
        arg2 a2;

        tpClosure2(void)
        {
        }

        tpClosure2(tpfactory tpf, ThreadedProcedure * daddy,
                arg1 A1, arg2 A2) :
        tpClosure(tpf, daddy),
        a1(A1), a2(A2)
        {
        }
        
        virtual tpClosure2 * clone(void) { return new tpClosure2( *this ); }
    	virtual ~tpClosure2(void){}
    };

    template< class arg1, class arg2, class arg3 >
    struct tpClosure3 : tpClosure
    {
        arg1 a1;
        arg2 a2;
        arg3 a3;

        tpClosure3(void)
        {
        }

        tpClosure3(tpfactory tpf, ThreadedProcedure * daddy,
                arg1 A1, arg2 A2, arg3 A3) :
        tpClosure(tpf, daddy),
        a1(A1), a2(A2), a3(A3)
        {
        }
        
        virtual tpClosure3 * clone(void) { return new tpClosure3( *this ); }        
    	virtual ~tpClosure3(void){}
    };

    template< class arg1, class arg2, class arg3, class arg4 >
    struct tpClosure4 : tpClosure
    {
        arg1 a1;
        arg2 a2;
        arg3 a3;
        arg4 a4;

        tpClosure4(void)
        {
        }

        tpClosure4(tpfactory tpf, ThreadedProcedure * daddy,
                arg1 A1, arg2 A2, arg3 A3, arg4 A4) :
        tpClosure(tpf, daddy),
        a1(A1), a2(A2), a3(A3), a4(A4)
        {
        }
        
        virtual tpClosure4 * clone(void) { return new tpClosure4( *this ); }
    	virtual ~tpClosure4(void){}
    };

    template< class arg1, class arg2, class arg3, class arg4, class arg5 >
    struct tpClosure5 : tpClosure
    {
        arg1 a1;
        arg2 a2;
        arg3 a3;
        arg4 a4;
        arg5 a5;

        tpClosure5(void)
        {
        }

        tpClosure5(tpfactory tpf, ThreadedProcedure * daddy,
                arg1 A1, arg2 A2, arg3 A3, arg4 A4, arg5 A5) :
        tpClosure(tpf, daddy),
        a1(A1), a2(A2), a3(A3), a4(A4), a5(A5)
        {
        }
        
        virtual tpClosure5 * clone(void) { return new tpClosure5( *this ); }
    	virtual ~tpClosure5(void){}
    };

    template< class arg1, class arg2, class arg3, class arg4, class arg5,
    class arg6 >
    struct tpClosure6 : tpClosure
    {
        arg1 a1;
        arg2 a2;
        arg3 a3;
        arg4 a4;
        arg5 a5;
        arg6 a6;

        tpClosure6(void)
        {
        }

        tpClosure6(tpfactory tpf, ThreadedProcedure * daddy,
                arg1 A1, arg2 A2, arg3 A3, arg4 A4, arg5 A5,
                arg6 A6) :
        tpClosure(tpf, daddy),
        a1(A1), a2(A2), a3(A3), a4(A4), a5(A5),
        a6(A6)
        {
        }
        
        virtual tpClosure6 * clone(void) { return new tpClosure6( *this ); }
    	virtual ~tpClosure6(void){}
    };

    template< class arg1, class arg2, class arg3, class arg4, class arg5,
    class arg6, class arg7 >
    struct tpClosure7 : tpClosure
    {
        arg1 a1;
        arg2 a2;
        arg3 a3;
        arg4 a4;
        arg5 a5;
        arg6 a6;
        arg7 a7;

        tpClosure7(void)
        {
        }

        tpClosure7(tpfactory tpf, ThreadedProcedure * daddy,
                arg1 A1, arg2 A2, arg3 A3, arg4 A4, arg5 A5,
                arg6 A6, arg7 A7) :
        tpClosure(tpf, daddy),
        a1(A1), a2(A2), a3(A3), a4(A4), a5(A5),
        a6(A6), a7(A7)
        {
        }
        
        virtual tpClosure7 * clone(void) { return new tpClosure7( *this ); }
    	virtual ~tpClosure7(void){}
    };

    template< class arg1, class arg2, class arg3, class arg4, class arg5,
    class arg6, class arg7, class arg8 >
    struct tpClosure8 : tpClosure
    {
        arg1 a1;
        arg2 a2;
        arg3 a3;
        arg4 a4;
        arg5 a5;
        arg6 a6;
        arg7 a7;
        arg8 a8;

        tpClosure8(void)
        {
        }

        tpClosure8(tpfactory tpf, ThreadedProcedure * daddy,
                arg1 A1, arg2 A2, arg3 A3, arg4 A4, arg5 A5,
                arg6 A6, arg7 A7, arg8 A8) :
        tpClosure(tpf, daddy),
        a1(A1), a2(A2), a3(A3), a4(A4), a5(A5),
        a6(A6), a7(A7), a8(A8)
        {
        }
        
        virtual tpClosure8 * clone(void) { return new tpClosure8( *this ); }
    	virtual ~tpClosure8(void){}
    };

    template< class arg1, class arg2, class arg3, class arg4, class arg5,
    class arg6, class arg7, class arg8, class arg9 >
    struct tpClosure9 : tpClosure
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

        tpClosure9(void)
        {
        }

        tpClosure9(tpfactory tpf, ThreadedProcedure * daddy,
                arg1 A1, arg2 A2, arg3 A3, arg4 A4, arg5 A5,
                arg6 A6, arg7 A7, arg8 A8, arg9 A9) :
        tpClosure(tpf, daddy),
        a1(A1), a2(A2), a3(A3), a4(A4), a5(A5),
        a6(A6), a7(A7), a8(A8), a9(A9)
        {
        }
        
        virtual tpClosure9 * clone(void) { return new tpClosure9( *this ); }
    	virtual ~tpClosure9(void){}
    };

    template< class arg1, class arg2, class arg3, class arg4, class arg5,
    class arg6, class arg7, class arg8, class arg9, class arg10 >
    struct tpClosure10 : tpClosure
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

        tpClosure10(void)
        {
        }

        tpClosure10(tpfactory tpf, ThreadedProcedure * daddy,
                arg1 A1, arg2 A2, arg3 A3, arg4 A4, arg5 A5,
                arg6 A6, arg7 A7, arg8 A8, arg9 A9, arg10 A10) :
        tpClosure(tpf, daddy),
        a1(A1), a2(A2), a3(A3), a4(A4), a5(A5),
        a6(A6), a7(A7), a8(A8), a9(A9), a10(A10)
        {
        }
        
        virtual tpClosure10 * clone(void) { return new tpClosure10( *this ); }
    	virtual ~tpClosure10(void){}
    };

    template< class arg1, class arg2, class arg3, class arg4, class arg5,
    class arg6, class arg7, class arg8, class arg9, class arg10,
    class arg11 >
    struct tpClosure11 : tpClosure
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

        tpClosure11(void)
        {
        }

        tpClosure11(tpfactory tpf, ThreadedProcedure * daddy,
                arg1 A1, arg2 A2, arg3 A3, arg4 A4, arg5 A5,
                arg6 A6, arg7 A7, arg8 A8, arg9 A9, arg10 A10,
                arg11 A11) :
        tpClosure(tpf, daddy),
        a1(A1), a2(A2), a3(A3), a4(A4), a5(A5),
        a6(A6), a7(A7), a8(A8), a9(A9), a10(A10),
        a11(A11)
        {
        }
        
        virtual tpClosure11 * clone(void) { return new tpClosure11( *this ); }
    	virtual ~tpClosure11(void){}
    };

    template< class arg1, class arg2, class arg3, class arg4, class arg5,
    class arg6, class arg7, class arg8, class arg9, class arg10,
    class arg11, class arg12 >
    struct tpClosure12 : tpClosure
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

        tpClosure12(void)
        {
        }

        tpClosure12(tpfactory tpf, ThreadedProcedure * daddy,
                arg1 A1, arg2 A2, arg3 A3, arg4 A4, arg5 A5,
                arg6 A6, arg7 A7, arg8 A8, arg9 A9, arg10 A10,
                arg11 A11, arg12 A12) :
        tpClosure(tpf, daddy),
        a1(A1), a2(A2), a3(A3), a4(A4), a5(A5),
        a6(A6), a7(A7), a8(A8), a9(A9), a10(A10),
        a11(A11), a12(A12)
        {
        }
        
        virtual tpClosure12 * clone(void) { return new tpClosure12( *this ); }
    	virtual ~tpClosure12(void){}
    };

    template< class arg1, class arg2, class arg3, class arg4, class arg5,
    class arg6, class arg7, class arg8, class arg9, class arg10,
    class arg11, class arg12, class arg13 >
    struct tpClosure13 : tpClosure
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

        tpClosure13(void)
        {
        }

        tpClosure13(tpfactory tpf, ThreadedProcedure * daddy,
                arg1 A1, arg2 A2, arg3 A3, arg4 A4, arg5 A5,
                arg6 A6, arg7 A7, arg8 A8, arg9 A9, arg10 A10,
                arg11 A11, arg12 A12, arg13 A13) :
        tpClosure(tpf, daddy),
        a1(A1), a2(A2), a3(A3), a4(A4), a5(A5),
        a6(A6), a7(A7), a8(A8), a9(A9), a10(A10),
        a11(A11), a12(A12), a13(A13)
        {
        }
        
        virtual tpClosure13 * clone(void) { return new tpClosure13( *this ); }
    	virtual ~tpClosure13(void){}
    };

    template< class arg1, class arg2, class arg3, class arg4, class arg5,
    class arg6, class arg7, class arg8, class arg9, class arg10,
    class arg11, class arg12, class arg13, class arg14 >
    struct tpClosure14 : tpClosure
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

        tpClosure14(void)
        {
        }

        tpClosure14(tpfactory tpf, ThreadedProcedure * daddy,
                arg1 A1, arg2 A2, arg3 A3, arg4 A4, arg5 A5,
                arg6 A6, arg7 A7, arg8 A8, arg9 A9, arg10 A10,
                arg11 A11, arg12 A12, arg13 A13, arg14 A14) :
        tpClosure(tpf, daddy),
        a1(A1), a2(A2), a3(A3), a4(A4), a5(A5),
        a6(A6), a7(A7), a8(A8), a9(A9), a10(A10),
        a11(A11), a12(A12), a13(A13), a14(A14)
        {
        }
        
        virtual tpClosure14 * clone(void) { return new tpClosure14( *this ); }
    	virtual ~tpClosure14(void){}
    };

    template< class arg1, class arg2, class arg3, class arg4, class arg5,
    class arg6, class arg7, class arg8, class arg9, class arg10,
    class arg11, class arg12, class arg13, class arg14, class arg15 >
    struct tpClosure15 : tpClosure
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

        tpClosure15(void)
        {
        }

        tpClosure15(tpfactory tpf, ThreadedProcedure * daddy,
                arg1 A1, arg2 A2, arg3 A3, arg4 A4, arg5 A5,
                arg6 A6, arg7 A7, arg8 A8, arg9 A9, arg10 A10,
                arg11 A11, arg12 A12, arg13 A13, arg14 A14, arg15 A15) :
        tpClosure(tpf, daddy),
        a1(A1), a2(A2), a3(A3), a4(A4), a5(A5),
        a6(A6), a7(A7), a8(A8), a9(A9), a10(A10),
        a11(A11), a12(A12), a13(A13), a14(A14), a15(A15)
        {
        }
        
        virtual tpClosure15 * clone(void) { return new tpClosure15( *this ); }
    	virtual ~tpClosure15(void){}
    };

    template< class arg1, class arg2, class arg3, class arg4, class arg5,
    class arg6, class arg7, class arg8, class arg9, class arg10,
    class arg11, class arg12, class arg13, class arg14, class arg15,
    class arg16 >
    struct tpClosure16 : tpClosure
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

        tpClosure16(void)
        {
        }

        tpClosure16(tpfactory tpf, ThreadedProcedure * daddy,
                arg1 A1, arg2 A2, arg3 A3, arg4 A4, arg5 A5,
                arg6 A6, arg7 A7, arg8 A8, arg9 A9, arg10 A10,
                arg11 A11, arg12 A12, arg13 A13, arg14 A14, arg15 A15,
                arg16 A16) :
        tpClosure(tpf, daddy),
        a1(A1), a2(A2), a3(A3), a4(A4), a5(A5),
        a6(A6), a7(A7), a8(A8), a9(A9), a10(A10),
        a11(A11), a12(A12), a13(A13), a14(A14), a15(A15),
        a16(A16)
        {
        }
        
        virtual tpClosure16 * clone(void) { return new tpClosure16( *this ); }
    	virtual ~tpClosure16(void){}
    };

    template< class arg1, class arg2, class arg3, class arg4, class arg5,
    class arg6, class arg7, class arg8, class arg9, class arg10,
    class arg11, class arg12, class arg13, class arg14, class arg15,
    class arg16, class arg17 >
    struct tpClosure17 : tpClosure
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

        tpClosure17(void)
        {
        }

        tpClosure17(tpfactory tpf, ThreadedProcedure * daddy,
                arg1 A1, arg2 A2, arg3 A3, arg4 A4, arg5 A5,
                arg6 A6, arg7 A7, arg8 A8, arg9 A9, arg10 A10,
                arg11 A11, arg12 A12, arg13 A13, arg14 A14, arg15 A15,
                arg16 A16, arg17 A17) :
        tpClosure(tpf, daddy),
        a1(A1), a2(A2), a3(A3), a4(A4), a5(A5),
        a6(A6), a7(A7), a8(A8), a9(A9), a10(A10),
        a11(A11), a12(A12), a13(A13), a14(A14), a15(A15),
        a16(A16), a17(A17)
        {
        }
        
        virtual tpClosure17 * clone(void) { return new tpClosure17( *this ); }
    	virtual ~tpClosure17(void){}
    };

    template< class arg1, class arg2, class arg3, class arg4, class arg5,
    class arg6, class arg7, class arg8, class arg9, class arg10,
    class arg11, class arg12, class arg13, class arg14, class arg15,
    class arg16, class arg17, class arg18 >
    struct tpClosure18 : tpClosure
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

        tpClosure18(void)
        {
        }

        tpClosure18(tpfactory tpf, ThreadedProcedure * daddy,
                arg1 A1, arg2 A2, arg3 A3, arg4 A4, arg5 A5,
                arg6 A6, arg7 A7, arg8 A8, arg9 A9, arg10 A10,
                arg11 A11, arg12 A12, arg13 A13, arg14 A14, arg15 A15,
                arg16 A16, arg17 A17, arg18 A18) :
        tpClosure(tpf, daddy),
        a1(A1), a2(A2), a3(A3), a4(A4), a5(A5),
        a6(A6), a7(A7), a8(A8), a9(A9), a10(A10),
        a11(A11), a12(A12), a13(A13), a14(A14), a15(A15),
        a16(A16), a17(A17), a18(A18)
        {
        }
        
        virtual tpClosure18 * clone(void) { return new tpClosure18( *this ); }
    	virtual ~tpClosure18(void){}
    };

    template< class arg1, class arg2, class arg3, class arg4, class arg5,
    class arg6, class arg7, class arg8, class arg9, class arg10,
    class arg11, class arg12, class arg13, class arg14, class arg15,
    class arg16, class arg17, class arg18, class arg19 >
    struct tpClosure19 : tpClosure
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

        tpClosure19(void)
        {
        }

        tpClosure19(tpfactory tpf, ThreadedProcedure * daddy,
                arg1 A1, arg2 A2, arg3 A3, arg4 A4, arg5 A5,
                arg6 A6, arg7 A7, arg8 A8, arg9 A9, arg10 A10,
                arg11 A11, arg12 A12, arg13 A13, arg14 A14, arg15 A15,
                arg16 A16, arg17 A17, arg18 A18, arg19 A19) :
        tpClosure(tpf, daddy),
        a1(A1), a2(A2), a3(A3), a4(A4), a5(A5),
        a6(A6), a7(A7), a8(A8), a9(A9), a10(A10),
        a11(A11), a12(A12), a13(A13), a14(A14), a15(A15),
        a16(A16), a17(A17), a18(A18), a19(A19)
        {
        }
        
        virtual tpClosure19 * clone(void) { return new tpClosure19( *this ); }
    	virtual ~tpClosure19(void){}
    };

    template< class arg1, class arg2, class arg3, class arg4, class arg5,
    class arg6, class arg7, class arg8, class arg9, class arg10,
    class arg11, class arg12, class arg13, class arg14, class arg15,
    class arg16, class arg17, class arg18, class arg19, class arg20 >
    struct tpClosure20 : tpClosure
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

        tpClosure20(void)
        {
        }

        tpClosure20(tpfactory tpf, ThreadedProcedure * daddy,
                arg1 A1, arg2 A2, arg3 A3, arg4 A4, arg5 A5,
                arg6 A6, arg7 A7, arg8 A8, arg9 A9, arg10 A10,
                arg11 A11, arg12 A12, arg13 A13, arg14 A14, arg15 A15,
                arg16 A16, arg17 A17, arg18 A18, arg19 A19, arg20 A20) :
        tpClosure(tpf, daddy),
        a1(A1), a2(A2), a3(A3), a4(A4), a5(A5),
        a6(A6), a7(A7), a8(A8), a9(A9), a10(A10),
        a11(A11), a12(A12), a13(A13), a14(A14), a15(A15),
        a16(A16), a17(A17), a18(A18), a19(A19), a20(A20)
        {
        }
        
        virtual tpClosure20 * clone(void) { return new tpClosure20( *this ); }
    	virtual ~tpClosure20(void){}
    };

    template< class arg1, class arg2, class arg3, class arg4, class arg5,
    class arg6, class arg7, class arg8, class arg9, class arg10,
    class arg11, class arg12, class arg13, class arg14, class arg15,
    class arg16, class arg17, class arg18, class arg19, class arg20,
    class arg21 >
    struct tpClosure21 : tpClosure
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

        tpClosure21(void)
        {
        }

        tpClosure21(tpfactory tpf, ThreadedProcedure * daddy,
                arg1 A1, arg2 A2, arg3 A3, arg4 A4, arg5 A5,
                arg6 A6, arg7 A7, arg8 A8, arg9 A9, arg10 A10,
                arg11 A11, arg12 A12, arg13 A13, arg14 A14, arg15 A15,
                arg16 A16, arg17 A17, arg18 A18, arg19 A19, arg20 A20,
                arg21 A21) :
        tpClosure(tpf, daddy),
        a1(A1), a2(A2), a3(A3), a4(A4), a5(A5),
        a6(A6), a7(A7), a8(A8), a9(A9), a10(A10),
        a11(A11), a12(A12), a13(A13), a14(A14), a15(A15),
        a16(A16), a17(A17), a18(A18), a19(A19), a20(A20),
        a21(A21)
        {
        }
        
        virtual tpClosure21 * clone(void) { return new tpClosure21( *this ); }
    	virtual ~tpClosure21(void){}
    };

    template< class arg1, class arg2, class arg3, class arg4, class arg5,
    class arg6, class arg7, class arg8, class arg9, class arg10,
    class arg11, class arg12, class arg13, class arg14, class arg15,
    class arg16, class arg17, class arg18, class arg19, class arg20,
    class arg21, class arg22 >
    struct tpClosure22 : tpClosure
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

        tpClosure22(void)
        {
        }

        tpClosure22(tpfactory tpf, ThreadedProcedure * daddy,
                arg1 A1, arg2 A2, arg3 A3, arg4 A4, arg5 A5,
                arg6 A6, arg7 A7, arg8 A8, arg9 A9, arg10 A10,
                arg11 A11, arg12 A12, arg13 A13, arg14 A14, arg15 A15,
                arg16 A16, arg17 A17, arg18 A18, arg19 A19, arg20 A20,
                arg21 A21, arg22 A22) :
        tpClosure(tpf, daddy),
        a1(A1), a2(A2), a3(A3), a4(A4), a5(A5),
        a6(A6), a7(A7), a8(A8), a9(A9), a10(A10),
        a11(A11), a12(A12), a13(A13), a14(A14), a15(A15),
        a16(A16), a17(A17), a18(A18), a19(A19), a20(A20),
        a21(A21), a22(A22)
        {
        }
        
        virtual tpClosure22 * clone(void) { return new tpClosure22( *this ); }
    	virtual ~tpClosure22(void){}
    };

    template< class arg1, class arg2, class arg3, class arg4, class arg5,
    class arg6, class arg7, class arg8, class arg9, class arg10,
    class arg11, class arg12, class arg13, class arg14, class arg15,
    class arg16, class arg17, class arg18, class arg19, class arg20,
    class arg21, class arg22, class arg23 >
    struct tpClosure23 : tpClosure
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

        tpClosure23(void)
        {
        }

        tpClosure23(tpfactory tpf, ThreadedProcedure * daddy,
                arg1 A1, arg2 A2, arg3 A3, arg4 A4, arg5 A5,
                arg6 A6, arg7 A7, arg8 A8, arg9 A9, arg10 A10,
                arg11 A11, arg12 A12, arg13 A13, arg14 A14, arg15 A15,
                arg16 A16, arg17 A17, arg18 A18, arg19 A19, arg20 A20,
                arg21 A21, arg22 A22, arg23 A23) :
        tpClosure(tpf, daddy),
        a1(A1), a2(A2), a3(A3), a4(A4), a5(A5),
        a6(A6), a7(A7), a8(A8), a9(A9), a10(A10),
        a11(A11), a12(A12), a13(A13), a14(A14), a15(A15),
        a16(A16), a17(A17), a18(A18), a19(A19), a20(A20),
        a21(A21), a22(A22), a23(A23)
        {
        }
        
        virtual tpClosure23 * clone(void) { return new tpClosure23( *this ); }
    	virtual ~tpClosure23(void){}
    };

    template< class arg1, class arg2, class arg3, class arg4, class arg5,
    class arg6, class arg7, class arg8, class arg9, class arg10,
    class arg11, class arg12, class arg13, class arg14, class arg15,
    class arg16, class arg17, class arg18, class arg19, class arg20,
    class arg21, class arg22, class arg23, class arg24 >
    struct tpClosure24 : tpClosure
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

        tpClosure24(void)
        {
        }

        tpClosure24(tpfactory tpf, ThreadedProcedure * daddy,
                arg1 A1, arg2 A2, arg3 A3, arg4 A4, arg5 A5,
                arg6 A6, arg7 A7, arg8 A8, arg9 A9, arg10 A10,
                arg11 A11, arg12 A12, arg13 A13, arg14 A14, arg15 A15,
                arg16 A16, arg17 A17, arg18 A18, arg19 A19, arg20 A20,
                arg21 A21, arg22 A22, arg23 A23, arg24 A24) :
        tpClosure(tpf, daddy),
        a1(A1), a2(A2), a3(A3), a4(A4), a5(A5),
        a6(A6), a7(A7), a8(A8), a9(A9), a10(A10),
        a11(A11), a12(A12), a13(A13), a14(A14), a15(A15),
        a16(A16), a17(A17), a18(A18), a19(A19), a20(A20),
        a21(A21), a22(A22), a23(A23), a24(A24)
        {
        }
        
        virtual tpClosure24 * clone(void) { return new tpClosure24( *this ); }
    	virtual ~tpClosure24(void){}
    };

    template< class arg1, class arg2, class arg3, class arg4, class arg5,
    class arg6, class arg7, class arg8, class arg9, class arg10,
    class arg11, class arg12, class arg13, class arg14, class arg15,
    class arg16, class arg17, class arg18, class arg19, class arg20,
    class arg21, class arg22, class arg23, class arg24, class arg25 >
    struct tpClosure25 : tpClosure
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

        tpClosure25(void)
        {
        }

        tpClosure25(tpfactory tpf, ThreadedProcedure * daddy,
                arg1 A1, arg2 A2, arg3 A3, arg4 A4, arg5 A5,
                arg6 A6, arg7 A7, arg8 A8, arg9 A9, arg10 A10,
                arg11 A11, arg12 A12, arg13 A13, arg14 A14, arg15 A15,
                arg16 A16, arg17 A17, arg18 A18, arg19 A19, arg20 A20,
                arg21 A21, arg22 A22, arg23 A23, arg24 A24, arg25 A25) :
        tpClosure(tpf, daddy),
        a1(A1), a2(A2), a3(A3), a4(A4), a5(A5),
        a6(A6), a7(A7), a8(A8), a9(A9), a10(A10),
        a11(A11), a12(A12), a13(A13), a14(A14), a15(A15),
        a16(A16), a17(A17), a18(A18), a19(A19), a20(A20),
        a21(A21), a22(A22), a23(A23), a24(A24), a25(A25)
        {
        }
        
        virtual tpClosure25 * clone(void) { return new tpClosure25( *this ); }
    	virtual ~tpClosure25(void){}
    };

    template< class arg1, class arg2, class arg3, class arg4, class arg5,
    class arg6, class arg7, class arg8, class arg9, class arg10,
    class arg11, class arg12, class arg13, class arg14, class arg15,
    class arg16, class arg17, class arg18, class arg19, class arg20,
    class arg21, class arg22, class arg23, class arg24, class arg25,
    class arg26 >
    struct tpClosure26 : tpClosure
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

        tpClosure26(void)
        {
        }

        tpClosure26(tpfactory tpf, ThreadedProcedure * daddy,
                arg1 A1, arg2 A2, arg3 A3, arg4 A4, arg5 A5,
                arg6 A6, arg7 A7, arg8 A8, arg9 A9, arg10 A10,
                arg11 A11, arg12 A12, arg13 A13, arg14 A14, arg15 A15,
                arg16 A16, arg17 A17, arg18 A18, arg19 A19, arg20 A20,
                arg21 A21, arg22 A22, arg23 A23, arg24 A24, arg25 A25,
                arg26 A26) :
        tpClosure(tpf, daddy),
        a1(A1), a2(A2), a3(A3), a4(A4), a5(A5),
        a6(A6), a7(A7), a8(A8), a9(A9), a10(A10),
        a11(A11), a12(A12), a13(A13), a14(A14), a15(A15),
        a16(A16), a17(A17), a18(A18), a19(A19), a20(A20),
        a21(A21), a22(A22), a23(A23), a24(A24), a25(A25),
        a26(A26)
        {
        }
        
        virtual tpClosure26 * clone(void) { return new tpClosure26( *this ); }
    	virtual ~tpClosure26(void){}
    };

    template< class arg1, class arg2, class arg3, class arg4, class arg5,
    class arg6, class arg7, class arg8, class arg9, class arg10,
    class arg11, class arg12, class arg13, class arg14, class arg15,
    class arg16, class arg17, class arg18, class arg19, class arg20,
    class arg21, class arg22, class arg23, class arg24, class arg25,
    class arg26, class arg27 >
    struct tpClosure27 : tpClosure
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

        tpClosure27(void)
        {
        }

        tpClosure27(tpfactory tpf, ThreadedProcedure * daddy,
                arg1 A1, arg2 A2, arg3 A3, arg4 A4, arg5 A5,
                arg6 A6, arg7 A7, arg8 A8, arg9 A9, arg10 A10,
                arg11 A11, arg12 A12, arg13 A13, arg14 A14, arg15 A15,
                arg16 A16, arg17 A17, arg18 A18, arg19 A19, arg20 A20,
                arg21 A21, arg22 A22, arg23 A23, arg24 A24, arg25 A25,
                arg26 A26, arg27 A27) :
        tpClosure(tpf, daddy),
        a1(A1), a2(A2), a3(A3), a4(A4), a5(A5),
        a6(A6), a7(A7), a8(A8), a9(A9), a10(A10),
        a11(A11), a12(A12), a13(A13), a14(A14), a15(A15),
        a16(A16), a17(A17), a18(A18), a19(A19), a20(A20),
        a21(A21), a22(A22), a23(A23), a24(A24), a25(A25),
        a26(A26), a27(A27)
        {
        }
        
        virtual tpClosure27 * clone(void) { return new tpClosure27( *this ); }
    	virtual ~tpClosure27(void){}
    };

    template< class arg1, class arg2, class arg3, class arg4, class arg5,
    class arg6, class arg7, class arg8, class arg9, class arg10,
    class arg11, class arg12, class arg13, class arg14, class arg15,
    class arg16, class arg17, class arg18, class arg19, class arg20,
    class arg21, class arg22, class arg23, class arg24, class arg25,
    class arg26, class arg27, class arg28 >
    struct tpClosure28 : tpClosure
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

        tpClosure28(void)
        {
        }

        tpClosure28(tpfactory tpf, ThreadedProcedure * daddy,
                arg1 A1, arg2 A2, arg3 A3, arg4 A4, arg5 A5,
                arg6 A6, arg7 A7, arg8 A8, arg9 A9, arg10 A10,
                arg11 A11, arg12 A12, arg13 A13, arg14 A14, arg15 A15,
                arg16 A16, arg17 A17, arg18 A18, arg19 A19, arg20 A20,
                arg21 A21, arg22 A22, arg23 A23, arg24 A24, arg25 A25,
                arg26 A26, arg27 A27, arg28 A28) :
        tpClosure(tpf, daddy),
        a1(A1), a2(A2), a3(A3), a4(A4), a5(A5),
        a6(A6), a7(A7), a8(A8), a9(A9), a10(A10),
        a11(A11), a12(A12), a13(A13), a14(A14), a15(A15),
        a16(A16), a17(A17), a18(A18), a19(A19), a20(A20),
        a21(A21), a22(A22), a23(A23), a24(A24), a25(A25),
        a26(A26), a27(A27), a28(A28)
        {
        }
        
        virtual tpClosure28 * clone(void) { return new tpClosure28( *this ); }
    	virtual ~tpClosure28(void){}
    };

    template< class arg1, class arg2, class arg3, class arg4, class arg5,
    class arg6, class arg7, class arg8, class arg9, class arg10,
    class arg11, class arg12, class arg13, class arg14, class arg15,
    class arg16, class arg17, class arg18, class arg19, class arg20,
    class arg21, class arg22, class arg23, class arg24, class arg25,
    class arg26, class arg27, class arg28, class arg29 >
    struct tpClosure29 : tpClosure
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

        tpClosure29(void)
        {
        }

        tpClosure29(tpfactory tpf, ThreadedProcedure * daddy,
                arg1 A1, arg2 A2, arg3 A3, arg4 A4, arg5 A5,
                arg6 A6, arg7 A7, arg8 A8, arg9 A9, arg10 A10,
                arg11 A11, arg12 A12, arg13 A13, arg14 A14, arg15 A15,
                arg16 A16, arg17 A17, arg18 A18, arg19 A19, arg20 A20,
                arg21 A21, arg22 A22, arg23 A23, arg24 A24, arg25 A25,
                arg26 A26, arg27 A27, arg28 A28, arg29 A29) :
        tpClosure(tpf, daddy),
        a1(A1), a2(A2), a3(A3), a4(A4), a5(A5),
        a6(A6), a7(A7), a8(A8), a9(A9), a10(A10),
        a11(A11), a12(A12), a13(A13), a14(A14), a15(A15),
        a16(A16), a17(A17), a18(A18), a19(A19), a20(A20),
        a21(A21), a22(A22), a23(A23), a24(A24), a25(A25),
        a26(A26), a27(A27), a28(A28), a29(A29)
        {
        }
        
        virtual tpClosure29 * clone(void) { return new tpClosure29( *this ); }
    	virtual ~tpClosure29(void){}
    };

    template< class arg1, class arg2, class arg3, class arg4, class arg5,
    class arg6, class arg7, class arg8, class arg9, class arg10,
    class arg11, class arg12, class arg13, class arg14, class arg15,
    class arg16, class arg17, class arg18, class arg19, class arg20,
    class arg21, class arg22, class arg23, class arg24, class arg25,
    class arg26, class arg27, class arg28, class arg29, class arg30 >
    struct tpClosure30 : tpClosure
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

        tpClosure30(void)
        {
        }

        tpClosure30(tpfactory tpf, ThreadedProcedure * daddy,
                arg1 A1, arg2 A2, arg3 A3, arg4 A4, arg5 A5,
                arg6 A6, arg7 A7, arg8 A8, arg9 A9, arg10 A10,
                arg11 A11, arg12 A12, arg13 A13, arg14 A14, arg15 A15,
                arg16 A16, arg17 A17, arg18 A18, arg19 A19, arg20 A20,
                arg21 A21, arg22 A22, arg23 A23, arg24 A24, arg25 A25,
                arg26 A26, arg27 A27, arg28 A28, arg29 A29, arg30 A30) :
        tpClosure(tpf, daddy),
        a1(A1), a2(A2), a3(A3), a4(A4), a5(A5),
        a6(A6), a7(A7), a8(A8), a9(A9), a10(A10),
        a11(A11), a12(A12), a13(A13), a14(A14), a15(A15),
        a16(A16), a17(A17), a18(A18), a19(A19), a20(A20),
        a21(A21), a22(A22), a23(A23), a24(A24), a25(A25),
        a26(A26), a27(A27), a28(A28), a29(A29), a30(A30)
        {
        }
        
        virtual tpClosure30 * clone(void) { return new tpClosure30( *this ); }
    	virtual ~tpClosure30(void){}
    };

    template< class arg1, class arg2, class arg3, class arg4, class arg5,
    class arg6, class arg7, class arg8, class arg9, class arg10,
    class arg11, class arg12, class arg13, class arg14, class arg15,
    class arg16, class arg17, class arg18, class arg19, class arg20,
    class arg21, class arg22, class arg23, class arg24, class arg25,
    class arg26, class arg27, class arg28, class arg29, class arg30,
    class arg31 >
    struct tpClosure31 : tpClosure
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

        tpClosure31(void)
        {
        }

        tpClosure31(tpfactory tpf, ThreadedProcedure * daddy,
                arg1 A1, arg2 A2, arg3 A3, arg4 A4, arg5 A5,
                arg6 A6, arg7 A7, arg8 A8, arg9 A9, arg10 A10,
                arg11 A11, arg12 A12, arg13 A13, arg14 A14, arg15 A15,
                arg16 A16, arg17 A17, arg18 A18, arg19 A19, arg20 A20,
                arg21 A21, arg22 A22, arg23 A23, arg24 A24, arg25 A25,
                arg26 A26, arg27 A27, arg28 A28, arg29 A29, arg30 A30,
                arg31 A31) :
        tpClosure(tpf, daddy),
        a1(A1), a2(A2), a3(A3), a4(A4), a5(A5),
        a6(A6), a7(A7), a8(A8), a9(A9), a10(A10),
        a11(A11), a12(A12), a13(A13), a14(A14), a15(A15),
        a16(A16), a17(A17), a18(A18), a19(A19), a20(A20),
        a21(A21), a22(A22), a23(A23), a24(A24), a25(A25),
        a26(A26), a27(A27), a28(A28), a29(A29), a30(A30),
        a31(A31)
        {
        }
        
        virtual tpClosure31 * clone(void) { return new tpClosure31( *this ); }
    	virtual ~tpClosure31(void){}
    };

    template< class arg1, class arg2, class arg3, class arg4, class arg5,
    class arg6, class arg7, class arg8, class arg9, class arg10,
    class arg11, class arg12, class arg13, class arg14, class arg15,
    class arg16, class arg17, class arg18, class arg19, class arg20,
    class arg21, class arg22, class arg23, class arg24, class arg25,
    class arg26, class arg27, class arg28, class arg29, class arg30,
    class arg31, class arg32 >
    struct tpClosure32 : tpClosure
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

        tpClosure32(void)
        {
        }

        tpClosure32(tpfactory tpf, ThreadedProcedure * daddy,
                arg1 A1, arg2 A2, arg3 A3, arg4 A4, arg5 A5,
                arg6 A6, arg7 A7, arg8 A8, arg9 A9, arg10 A10,
                arg11 A11, arg12 A12, arg13 A13, arg14 A14, arg15 A15,
                arg16 A16, arg17 A17, arg18 A18, arg19 A19, arg20 A20,
                arg21 A21, arg22 A22, arg23 A23, arg24 A24, arg25 A25,
                arg26 A26, arg27 A27, arg28 A28, arg29 A29, arg30 A30,
                arg31 A31, arg32 A32) :
        tpClosure(tpf, daddy),
        a1(A1), a2(A2), a3(A3), a4(A4), a5(A5),
        a6(A6), a7(A7), a8(A8), a9(A9), a10(A10),
        a11(A11), a12(A12), a13(A13), a14(A14), a15(A15),
        a16(A16), a17(A17), a18(A18), a19(A19), a20(A20),
        a21(A21), a22(A22), a23(A23), a24(A24), a25(A25),
        a26(A26), a27(A27), a28(A28), a29(A29), a30(A30),
        a31(A31), a32(A32)
        {
        }
        
        virtual tpClosure32 * clone(void) { return new tpClosure32( *this ); }
    	virtual ~tpClosure32(void){}
    };




}

#endif	/* TPCLOSURE_H */

