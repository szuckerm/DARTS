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


#ifndef invoke_H
#define	invoke_H
#include "tpClosure.h"
#include "threadlocal.h"
#include <iostream>
#include <sstream> 
namespace darts {

    template<class newTP>
    ThreadedProcedure *
    TPFactory(tpClosure * args) {
        myThread.tempParent = args->parent;
        ThreadedProcedure * temp = new newTP();
        if (temp->decRef()) {
            delete temp;
            return NULL;
        }
        myThread.tempParent = NULL;
        return temp;
    }

    template<class newTP>
    void
    invoke(ThreadedProcedure * parentTP) {
        parentTP->incRef();
        tpfactory funct = &TPFactory<newTP>;
        tpClosure * closure = new tpClosure(funct, parentTP);
        myThread.threadTPsched->pushTP(closure);
    }

    template<class newTP>
    tpClosure *
    launch() {
        tpfactory funct = &TPFactory<newTP>;
        return new tpClosure(funct, NULL);
    }

    /************************************************************/

    template<class newTP, class arg1 >
    ThreadedProcedure *
    TPFactory(tpClosure * closure) {
        tpClosure1< arg1 > * args = static_cast<tpClosure1< arg1 >*> (closure);
        myThread.tempParent = args->parent;
        ThreadedProcedure * temp = new newTP(args->a1);
        if (temp->decRef()) {
            delete temp;
            return NULL;
        }
        myThread.tempParent = NULL;
        return temp;
    }

    template<class newTP, class arg1 >
    void
    invoke(ThreadedProcedure * parentTP, arg1 A1) {
        parentTP->incRef();
        tpfactory funct = &TPFactory< newTP, arg1 >;
        tpClosure * closure = new tpClosure1< arg1 > (funct, parentTP, A1);
        myThread.threadTPsched->pushTP(closure);
    }

    template<class newTP, class arg1 >
    tpClosure *
    launch(arg1 A1) {
        tpfactory funct = &TPFactory< newTP, arg1 >;
        return new tpClosure1< arg1 > (funct, NULL, A1);
    }

    template<class newTP, class arg1, class arg2 >
    ThreadedProcedure *
    TPFactory(tpClosure * closure) {
        tpClosure2< arg1, arg2 > * args = static_cast<tpClosure2< arg1, arg2 >*> (closure);
        myThread.tempParent = args->parent;
        ThreadedProcedure * temp = new newTP(args->a1, args->a2);
        if (temp->decRef()) {
            delete temp;
            return NULL;
        }
        myThread.tempParent = NULL;
        return temp;
    }

    template<class newTP, class arg1, class arg2 >
    void
    invoke(ThreadedProcedure * parentTP, arg1 A1, arg2 A2) {
        parentTP->incRef();
        tpfactory funct = &TPFactory< newTP, arg1, arg2 >;
        tpClosure * closure = new tpClosure2< arg1, arg2 > (funct, parentTP, A1, A2);
        myThread.threadTPsched->pushTP(closure);
    }

    template<class newTP, class arg1, class arg2 >
    tpClosure *
    launch(arg1 A1, arg2 A2) {
        tpfactory funct = &TPFactory< newTP, arg1, arg2 >;
        return new tpClosure2< arg1, arg2 > (funct, NULL, A1, A2);
    }

    template<class newTP, class arg1, class arg2, class arg3 >
    ThreadedProcedure *
    TPFactory(tpClosure * closure) {
        tpClosure3< arg1, arg2, arg3 > * args = static_cast<tpClosure3< arg1, arg2, arg3 >*> (closure);
        myThread.tempParent = args->parent;
        ThreadedProcedure * temp = new newTP(args->a1, args->a2, args->a3);
        if (temp->decRef()) {
            delete temp;
            return NULL;
        }
        myThread.tempParent = NULL;
        return temp;
    }

    template<class newTP, class arg1, class arg2, class arg3 >
    void
    invoke(ThreadedProcedure * parentTP, arg1 A1, arg2 A2, arg3 A3) {
        parentTP->incRef();
        tpfactory funct = &TPFactory< newTP, arg1, arg2, arg3 >;
        tpClosure * closure = new tpClosure3< arg1, arg2, arg3 > (funct, parentTP, A1, A2, A3);
        myThread.threadTPsched->pushTP(closure);
    }

    template<class newTP, class arg1, class arg2, class arg3 >
    tpClosure *
    launch(arg1 A1, arg2 A2, arg3 A3) {
        tpfactory funct = &TPFactory< newTP, arg1, arg2, arg3 >;
        return new tpClosure3< arg1, arg2, arg3 > (funct, NULL, A1, A2, A3);
    }

    template<class newTP, class arg1, class arg2, class arg3, class arg4 >
    ThreadedProcedure *
    TPFactory(tpClosure * closure) {
        tpClosure4< arg1, arg2, arg3, arg4 > * args = static_cast<tpClosure4< arg1, arg2, arg3, arg4 >*> (closure);
        myThread.tempParent = args->parent;
        ThreadedProcedure * temp = new newTP(args->a1, args->a2, args->a3, args->a4);
        if (temp->decRef()) {
            delete temp;
            return NULL;
        }
        myThread.tempParent = NULL;
        return temp;
    }

    template<class newTP, class arg1, class arg2, class arg3, class arg4 >
    void
    invoke(ThreadedProcedure * parentTP, arg1 A1, arg2 A2, arg3 A3, arg4 A4) {
        parentTP->incRef();
        tpfactory funct = &TPFactory< newTP, arg1, arg2, arg3, arg4 >;
        tpClosure * closure = new tpClosure4< arg1, arg2, arg3, arg4 > (funct, parentTP, A1, A2, A3, A4);
        myThread.threadTPsched->pushTP(closure);
    }

    template<class newTP, class arg1, class arg2, class arg3, class arg4 >
    tpClosure *
    launch(arg1 A1, arg2 A2, arg3 A3, arg4 A4) {
        tpfactory funct = &TPFactory< newTP, arg1, arg2, arg3, arg4 >;
        return new tpClosure4< arg1, arg2, arg3, arg4 > (funct, NULL, A1, A2, A3, A4);
    }

    template<class newTP, class arg1, class arg2, class arg3, class arg4, class arg5 >
    ThreadedProcedure *
    TPFactory(tpClosure * closure) {
        tpClosure5< arg1, arg2, arg3, arg4, arg5 > * args = static_cast<tpClosure5< arg1, arg2, arg3, arg4, arg5 >*> (closure);
        myThread.tempParent = args->parent;
        ThreadedProcedure * temp = new newTP(args->a1, args->a2, args->a3, args->a4, args->a5);
        if (temp->decRef()) {
            delete temp;
            return NULL;
        }
        myThread.tempParent = NULL;
        return temp;
    }

    template<class newTP, class arg1, class arg2, class arg3, class arg4, class arg5 >
    void
    invoke(ThreadedProcedure * parentTP, arg1 A1, arg2 A2, arg3 A3, arg4 A4, arg5 A5) {
        parentTP->incRef();
        tpfactory funct = &TPFactory< newTP, arg1, arg2, arg3, arg4, arg5 >;
        tpClosure * closure = new tpClosure5< arg1, arg2, arg3, arg4, arg5 > (funct, parentTP, A1, A2, A3, A4, A5);
        myThread.threadTPsched->pushTP(closure);
    }

    template<class newTP, class arg1, class arg2, class arg3, class arg4, class arg5 >
    tpClosure *
    launch(arg1 A1, arg2 A2, arg3 A3, arg4 A4, arg5 A5) {
        tpfactory funct = &TPFactory< newTP, arg1, arg2, arg3, arg4, arg5 >;
        return new tpClosure5< arg1, arg2, arg3, arg4, arg5 > (funct, NULL, A1, A2, A3, A4, A5);
    }

    template<class newTP, class arg1, class arg2, class arg3, class arg4, class arg5,
    class arg6 >
    ThreadedProcedure *
    TPFactory(tpClosure * closure) {
        tpClosure6< arg1, arg2, arg3, arg4, arg5,
                arg6 > * args = static_cast<tpClosure6< arg1, arg2, arg3, arg4, arg5,
                arg6 >*> (closure);
        myThread.tempParent = args->parent;
        ThreadedProcedure * temp = new newTP(args->a1, args->a2, args->a3, args->a4, args->a5,
                args->a6);
        if (temp->decRef()) {
            delete temp;
            return NULL;
        }
        myThread.tempParent = NULL;
        return temp;
    }

    template<class newTP, class arg1, class arg2, class arg3, class arg4, class arg5,
    class arg6 >
    void
    invoke(ThreadedProcedure * parentTP, arg1 A1, arg2 A2, arg3 A3, arg4 A4, arg5 A5,
            arg6 A6) {
        parentTP->incRef();
        tpfactory funct = &TPFactory< newTP, arg1, arg2, arg3, arg4, arg5,
                arg6 >;
        tpClosure * closure = new tpClosure6< arg1, arg2, arg3, arg4, arg5,
                arg6 > (funct, parentTP, A1, A2, A3, A4, A5,
                A6);
        myThread.threadTPsched->pushTP(closure);
    }

    template<class newTP, class arg1, class arg2, class arg3, class arg4, class arg5,
    class arg6 >
    tpClosure *
    launch(arg1 A1, arg2 A2, arg3 A3, arg4 A4, arg5 A5,
            arg6 A6) {
        tpfactory funct = &TPFactory< newTP, arg1, arg2, arg3, arg4, arg5,
                arg6 >;
        return new tpClosure6< arg1, arg2, arg3, arg4, arg5,
                arg6 > (funct, NULL, A1, A2, A3, A4, A5,
                A6);
    }

    template<class newTP, class arg1, class arg2, class arg3, class arg4, class arg5,
    class arg6, class arg7 >
    ThreadedProcedure *
    TPFactory(tpClosure * closure) {
        tpClosure7< arg1, arg2, arg3, arg4, arg5,
                arg6, arg7 > * args = static_cast<tpClosure7< arg1, arg2, arg3, arg4, arg5,
                arg6, arg7 >*> (closure);
        myThread.tempParent = args->parent;
        ThreadedProcedure * temp = new newTP(args->a1, args->a2, args->a3, args->a4, args->a5,
                args->a6, args->a7);
        if (temp->decRef()) {
            delete temp;
            return NULL;
        }
        myThread.tempParent = NULL;
        return temp;
    }

    template<class newTP, class arg1, class arg2, class arg3, class arg4, class arg5,
    class arg6, class arg7 >
    void
    invoke(ThreadedProcedure * parentTP, arg1 A1, arg2 A2, arg3 A3, arg4 A4, arg5 A5,
            arg6 A6, arg7 A7) {
        parentTP->incRef();
        tpfactory funct = &TPFactory< newTP, arg1, arg2, arg3, arg4, arg5,
                arg6, arg7 >;
        tpClosure * closure = new tpClosure7< arg1, arg2, arg3, arg4, arg5,
                arg6, arg7 > (funct, parentTP, A1, A2, A3, A4, A5,
                A6, A7);
        myThread.threadTPsched->pushTP(closure);
    }

    template<class newTP, class arg1, class arg2, class arg3, class arg4, class arg5,
    class arg6, class arg7 >
    tpClosure *
    launch(arg1 A1, arg2 A2, arg3 A3, arg4 A4, arg5 A5,
            arg6 A6, arg7 A7) {
        tpfactory funct = &TPFactory< newTP, arg1, arg2, arg3, arg4, arg5,
                arg6, arg7 >;
        return new tpClosure7< arg1, arg2, arg3, arg4, arg5,
                arg6, arg7 > (funct, NULL, A1, A2, A3, A4, A5,
                A6, A7);
    }

    template<class newTP, class arg1, class arg2, class arg3, class arg4, class arg5,
    class arg6, class arg7, class arg8 >
    ThreadedProcedure *
    TPFactory(tpClosure * closure) {
        tpClosure8< arg1, arg2, arg3, arg4, arg5,
                arg6, arg7, arg8 > * args = static_cast<tpClosure8< arg1, arg2, arg3, arg4, arg5,
                arg6, arg7, arg8 >*> (closure);
        myThread.tempParent = args->parent;
        ThreadedProcedure * temp = new newTP(args->a1, args->a2, args->a3, args->a4, args->a5,
                args->a6, args->a7, args->a8);
        if (temp->decRef()) {
            delete temp;
            return NULL;
        }
        myThread.tempParent = NULL;
        return temp;
    }

    template<class newTP, class arg1, class arg2, class arg3, class arg4, class arg5,
    class arg6, class arg7, class arg8 >
    void
    invoke(ThreadedProcedure * parentTP, arg1 A1, arg2 A2, arg3 A3, arg4 A4, arg5 A5,
            arg6 A6, arg7 A7, arg8 A8) {
        parentTP->incRef();
        tpfactory funct = &TPFactory< newTP, arg1, arg2, arg3, arg4, arg5,
                arg6, arg7, arg8 >;
        tpClosure * closure = new tpClosure8< arg1, arg2, arg3, arg4, arg5,
                arg6, arg7, arg8 > (funct, parentTP, A1, A2, A3, A4, A5,
                A6, A7, A8);
        myThread.threadTPsched->pushTP(closure);
    }

    template<class newTP, class arg1, class arg2, class arg3, class arg4, class arg5,
    class arg6, class arg7, class arg8 >
    tpClosure *
    launch(arg1 A1, arg2 A2, arg3 A3, arg4 A4, arg5 A5,
            arg6 A6, arg7 A7, arg8 A8) {
        tpfactory funct = &TPFactory< newTP, arg1, arg2, arg3, arg4, arg5,
                arg6, arg7, arg8 >;
        return new tpClosure8< arg1, arg2, arg3, arg4, arg5,
                arg6, arg7, arg8 > (funct, NULL, A1, A2, A3, A4, A5,
                A6, A7, A8);
    }

    template<class newTP, class arg1, class arg2, class arg3, class arg4, class arg5,
    class arg6, class arg7, class arg8, class arg9 >
    ThreadedProcedure *
    TPFactory(tpClosure * closure) {
        tpClosure9< arg1, arg2, arg3, arg4, arg5,
                arg6, arg7, arg8, arg9 > * args = static_cast<tpClosure9< arg1, arg2, arg3, arg4, arg5,
                arg6, arg7, arg8, arg9 >*> (closure);
        myThread.tempParent = args->parent;
        ThreadedProcedure * temp = new newTP(args->a1, args->a2, args->a3, args->a4, args->a5,
                args->a6, args->a7, args->a8, args->a9);
        if (temp->decRef()) {
            delete temp;
            return NULL;
        }
        myThread.tempParent = NULL;
        return temp;
    }

    template<class newTP, class arg1, class arg2, class arg3, class arg4, class arg5,
    class arg6, class arg7, class arg8, class arg9 >
    void
    invoke(ThreadedProcedure * parentTP, arg1 A1, arg2 A2, arg3 A3, arg4 A4, arg5 A5,
            arg6 A6, arg7 A7, arg8 A8, arg9 A9) {
        parentTP->incRef();
        tpfactory funct = &TPFactory< newTP, arg1, arg2, arg3, arg4, arg5,
                arg6, arg7, arg8, arg9 >;
        tpClosure * closure = new tpClosure9< arg1, arg2, arg3, arg4, arg5,
                arg6, arg7, arg8, arg9 > (funct, parentTP, A1, A2, A3, A4, A5,
                A6, A7, A8, A9);
        myThread.threadTPsched->pushTP(closure);
    }

    template<class newTP, class arg1, class arg2, class arg3, class arg4, class arg5,
    class arg6, class arg7, class arg8, class arg9 >
    tpClosure *
    launch(arg1 A1, arg2 A2, arg3 A3, arg4 A4, arg5 A5,
            arg6 A6, arg7 A7, arg8 A8, arg9 A9) {
        tpfactory funct = &TPFactory< newTP, arg1, arg2, arg3, arg4, arg5,
                arg6, arg7, arg8, arg9 >;
        return new tpClosure9< arg1, arg2, arg3, arg4, arg5,
                arg6, arg7, arg8, arg9 > (funct, NULL, A1, A2, A3, A4, A5,
                A6, A7, A8, A9);
    }

    template<class newTP, class arg1, class arg2, class arg3, class arg4, class arg5,
    class arg6, class arg7, class arg8, class arg9, class arg10 >
    ThreadedProcedure *
    TPFactory(tpClosure * closure) {
        tpClosure10< arg1, arg2, arg3, arg4, arg5,
                arg6, arg7, arg8, arg9, arg10 > * args = static_cast<tpClosure10< arg1, arg2, arg3, arg4, arg5,
                arg6, arg7, arg8, arg9, arg10 >*> (closure);
        myThread.tempParent = args->parent;
        ThreadedProcedure * temp = new newTP(args->a1, args->a2, args->a3, args->a4, args->a5,
                args->a6, args->a7, args->a8, args->a9, args->a10);
        if (temp->decRef()) {
            delete temp;
            return NULL;
        }
        myThread.tempParent = NULL;
        return temp;
    }

    template<class newTP, class arg1, class arg2, class arg3, class arg4, class arg5,
    class arg6, class arg7, class arg8, class arg9, class arg10 >
    void
    invoke(ThreadedProcedure * parentTP, arg1 A1, arg2 A2, arg3 A3, arg4 A4, arg5 A5,
            arg6 A6, arg7 A7, arg8 A8, arg9 A9, arg10 A10) {
        parentTP->incRef();
        tpfactory funct = &TPFactory< newTP, arg1, arg2, arg3, arg4, arg5,
                arg6, arg7, arg8, arg9, arg10 >;
        tpClosure * closure = new tpClosure10< arg1, arg2, arg3, arg4, arg5,
                arg6, arg7, arg8, arg9, arg10 > (funct, parentTP, A1, A2, A3, A4, A5,
                A6, A7, A8, A9, A10);
        myThread.threadTPsched->pushTP(closure);
    }

    template<class newTP, class arg1, class arg2, class arg3, class arg4, class arg5,
    class arg6, class arg7, class arg8, class arg9, class arg10 >
    tpClosure *
    launch(arg1 A1, arg2 A2, arg3 A3, arg4 A4, arg5 A5,
            arg6 A6, arg7 A7, arg8 A8, arg9 A9, arg10 A10) {
        tpfactory funct = &TPFactory< newTP, arg1, arg2, arg3, arg4, arg5,
                arg6, arg7, arg8, arg9, arg10 >;
        return new tpClosure10< arg1, arg2, arg3, arg4, arg5,
                arg6, arg7, arg8, arg9, arg10 > (funct, NULL, A1, A2, A3, A4, A5,
                A6, A7, A8, A9, A10);
    }

    template<class newTP, class arg1, class arg2, class arg3, class arg4, class arg5,
    class arg6, class arg7, class arg8, class arg9, class arg10,
    class arg11 >
    ThreadedProcedure *
    TPFactory(tpClosure * closure) {
        tpClosure11< arg1, arg2, arg3, arg4, arg5,
                arg6, arg7, arg8, arg9, arg10,
                arg11 > * args = static_cast<tpClosure11< arg1, arg2, arg3, arg4, arg5,
                arg6, arg7, arg8, arg9, arg10,
                arg11 >*> (closure);
        myThread.tempParent = args->parent;
        ThreadedProcedure * temp = new newTP(args->a1, args->a2, args->a3, args->a4, args->a5,
                args->a6, args->a7, args->a8, args->a9, args->a10,
                args->a11);
        if (temp->decRef()) {
            delete temp;
            return NULL;
        }
        myThread.tempParent = NULL;
        return temp;
    }

    template<class newTP, class arg1, class arg2, class arg3, class arg4, class arg5,
    class arg6, class arg7, class arg8, class arg9, class arg10,
    class arg11 >
    void
    invoke(ThreadedProcedure * parentTP, arg1 A1, arg2 A2, arg3 A3, arg4 A4, arg5 A5,
            arg6 A6, arg7 A7, arg8 A8, arg9 A9, arg10 A10,
            arg11 A11) {
        parentTP->incRef();
        tpfactory funct = &TPFactory< newTP, arg1, arg2, arg3, arg4, arg5,
                arg6, arg7, arg8, arg9, arg10,
                arg11 >;
        tpClosure * closure = new tpClosure11< arg1, arg2, arg3, arg4, arg5,
                arg6, arg7, arg8, arg9, arg10,
                arg11 > (funct, parentTP, A1, A2, A3, A4, A5,
                A6, A7, A8, A9, A10,
                A11);
        myThread.threadTPsched->pushTP(closure);
    }

    template<class newTP, class arg1, class arg2, class arg3, class arg4, class arg5,
    class arg6, class arg7, class arg8, class arg9, class arg10,
    class arg11 >
    tpClosure *
    launch(arg1 A1, arg2 A2, arg3 A3, arg4 A4, arg5 A5,
            arg6 A6, arg7 A7, arg8 A8, arg9 A9, arg10 A10,
            arg11 A11) {
        tpfactory funct = &TPFactory< newTP, arg1, arg2, arg3, arg4, arg5,
                arg6, arg7, arg8, arg9, arg10,
                arg11 >;
        return new tpClosure11< arg1, arg2, arg3, arg4, arg5,
                arg6, arg7, arg8, arg9, arg10,
                arg11 > (funct, NULL, A1, A2, A3, A4, A5,
                A6, A7, A8, A9, A10,
                A11);
    }

    template<class newTP, class arg1, class arg2, class arg3, class arg4, class arg5,
    class arg6, class arg7, class arg8, class arg9, class arg10,
    class arg11, class arg12 >
    ThreadedProcedure *
    TPFactory(tpClosure * closure) {
        tpClosure12< arg1, arg2, arg3, arg4, arg5,
                arg6, arg7, arg8, arg9, arg10,
                arg11, arg12 > * args = static_cast<tpClosure12< arg1, arg2, arg3, arg4, arg5,
                arg6, arg7, arg8, arg9, arg10,
                arg11, arg12 >*> (closure);
        myThread.tempParent = args->parent;
        ThreadedProcedure * temp = new newTP(args->a1, args->a2, args->a3, args->a4, args->a5,
                args->a6, args->a7, args->a8, args->a9, args->a10,
                args->a11, args->a12);
        if (temp->decRef()) {
            delete temp;
            return NULL;
        }
        myThread.tempParent = NULL;
        return temp;
    }

    template<class newTP, class arg1, class arg2, class arg3, class arg4, class arg5,
    class arg6, class arg7, class arg8, class arg9, class arg10,
    class arg11, class arg12 >
    void
    invoke(ThreadedProcedure * parentTP, arg1 A1, arg2 A2, arg3 A3, arg4 A4, arg5 A5,
            arg6 A6, arg7 A7, arg8 A8, arg9 A9, arg10 A10,
            arg11 A11, arg12 A12) {
        parentTP->incRef();
        tpfactory funct = &TPFactory< newTP, arg1, arg2, arg3, arg4, arg5,
                arg6, arg7, arg8, arg9, arg10,
                arg11, arg12 >;
        tpClosure * closure = new tpClosure12< arg1, arg2, arg3, arg4, arg5,
                arg6, arg7, arg8, arg9, arg10,
                arg11, arg12 > (funct, parentTP, A1, A2, A3, A4, A5,
                A6, A7, A8, A9, A10,
                A11, A12);
        myThread.threadTPsched->pushTP(closure);
    }

    template<class newTP, class arg1, class arg2, class arg3, class arg4, class arg5,
    class arg6, class arg7, class arg8, class arg9, class arg10,
    class arg11, class arg12 >
    tpClosure *
    launch(arg1 A1, arg2 A2, arg3 A3, arg4 A4, arg5 A5,
            arg6 A6, arg7 A7, arg8 A8, arg9 A9, arg10 A10,
            arg11 A11, arg12 A12) {
        tpfactory funct = &TPFactory< newTP, arg1, arg2, arg3, arg4, arg5,
                arg6, arg7, arg8, arg9, arg10,
                arg11, arg12 >;
        return new tpClosure12< arg1, arg2, arg3, arg4, arg5,
                arg6, arg7, arg8, arg9, arg10,
                arg11, arg12 > (funct, NULL, A1, A2, A3, A4, A5,
                A6, A7, A8, A9, A10,
                A11, A12);
    }

    template<class newTP, class arg1, class arg2, class arg3, class arg4, class arg5,
    class arg6, class arg7, class arg8, class arg9, class arg10,
    class arg11, class arg12, class arg13 >
    ThreadedProcedure *
    TPFactory(tpClosure * closure) {
        tpClosure13< arg1, arg2, arg3, arg4, arg5,
                arg6, arg7, arg8, arg9, arg10,
                arg11, arg12, arg13 > * args = static_cast<tpClosure13< arg1, arg2, arg3, arg4, arg5,
                arg6, arg7, arg8, arg9, arg10,
                arg11, arg12, arg13 >*> (closure);
        myThread.tempParent = args->parent;
        ThreadedProcedure * temp = new newTP(args->a1, args->a2, args->a3, args->a4, args->a5,
                args->a6, args->a7, args->a8, args->a9, args->a10,
                args->a11, args->a12, args->a13);
        if (temp->decRef()) {
            delete temp;
            return NULL;
        }
        myThread.tempParent = NULL;
        return temp;
    }

    template<class newTP, class arg1, class arg2, class arg3, class arg4, class arg5,
    class arg6, class arg7, class arg8, class arg9, class arg10,
    class arg11, class arg12, class arg13 >
    void
    invoke(ThreadedProcedure * parentTP, arg1 A1, arg2 A2, arg3 A3, arg4 A4, arg5 A5,
            arg6 A6, arg7 A7, arg8 A8, arg9 A9, arg10 A10,
            arg11 A11, arg12 A12, arg13 A13) {
        parentTP->incRef();
        tpfactory funct = &TPFactory< newTP, arg1, arg2, arg3, arg4, arg5,
                arg6, arg7, arg8, arg9, arg10,
                arg11, arg12, arg13 >;
        tpClosure * closure = new tpClosure13< arg1, arg2, arg3, arg4, arg5,
                arg6, arg7, arg8, arg9, arg10,
                arg11, arg12, arg13 > (funct, parentTP, A1, A2, A3, A4, A5,
                A6, A7, A8, A9, A10,
                A11, A12, A13);
        myThread.threadTPsched->pushTP(closure);
    }

    template<class newTP, class arg1, class arg2, class arg3, class arg4, class arg5,
    class arg6, class arg7, class arg8, class arg9, class arg10,
    class arg11, class arg12, class arg13 >
    tpClosure *
    launch(arg1 A1, arg2 A2, arg3 A3, arg4 A4, arg5 A5,
            arg6 A6, arg7 A7, arg8 A8, arg9 A9, arg10 A10,
            arg11 A11, arg12 A12, arg13 A13) {
        tpfactory funct = &TPFactory< newTP, arg1, arg2, arg3, arg4, arg5,
                arg6, arg7, arg8, arg9, arg10,
                arg11, arg12, arg13 >;
        return new tpClosure13< arg1, arg2, arg3, arg4, arg5,
                arg6, arg7, arg8, arg9, arg10,
                arg11, arg12, arg13 > (funct, NULL, A1, A2, A3, A4, A5,
                A6, A7, A8, A9, A10,
                A11, A12, A13);
    }

    template<class newTP, class arg1, class arg2, class arg3, class arg4, class arg5,
    class arg6, class arg7, class arg8, class arg9, class arg10,
    class arg11, class arg12, class arg13, class arg14 >
    ThreadedProcedure *
    TPFactory(tpClosure * closure) {
        tpClosure14< arg1, arg2, arg3, arg4, arg5,
                arg6, arg7, arg8, arg9, arg10,
                arg11, arg12, arg13, arg14 > * args = static_cast<tpClosure14< arg1, arg2, arg3, arg4, arg5,
                arg6, arg7, arg8, arg9, arg10,
                arg11, arg12, arg13, arg14 >*> (closure);
        myThread.tempParent = args->parent;
        ThreadedProcedure * temp = new newTP(args->a1, args->a2, args->a3, args->a4, args->a5,
                args->a6, args->a7, args->a8, args->a9, args->a10,
                args->a11, args->a12, args->a13, args->a14);
        if (temp->decRef()) {
            delete temp;
            return NULL;
        }
        myThread.tempParent = NULL;
        return temp;
    }

    template<class newTP, class arg1, class arg2, class arg3, class arg4, class arg5,
    class arg6, class arg7, class arg8, class arg9, class arg10,
    class arg11, class arg12, class arg13, class arg14 >
    void
    invoke(ThreadedProcedure * parentTP, arg1 A1, arg2 A2, arg3 A3, arg4 A4, arg5 A5,
            arg6 A6, arg7 A7, arg8 A8, arg9 A9, arg10 A10,
            arg11 A11, arg12 A12, arg13 A13, arg14 A14) {
        parentTP->incRef();
        tpfactory funct = &TPFactory< newTP, arg1, arg2, arg3, arg4, arg5,
                arg6, arg7, arg8, arg9, arg10,
                arg11, arg12, arg13, arg14 >;
        tpClosure * closure = new tpClosure14< arg1, arg2, arg3, arg4, arg5,
                arg6, arg7, arg8, arg9, arg10,
                arg11, arg12, arg13, arg14 > (funct, parentTP, A1, A2, A3, A4, A5,
                A6, A7, A8, A9, A10,
                A11, A12, A13, A14);
        myThread.threadTPsched->pushTP(closure);
    }

    template<class newTP, class arg1, class arg2, class arg3, class arg4, class arg5,
    class arg6, class arg7, class arg8, class arg9, class arg10,
    class arg11, class arg12, class arg13, class arg14 >
    tpClosure *
    launch(arg1 A1, arg2 A2, arg3 A3, arg4 A4, arg5 A5,
            arg6 A6, arg7 A7, arg8 A8, arg9 A9, arg10 A10,
            arg11 A11, arg12 A12, arg13 A13, arg14 A14) {
        tpfactory funct = &TPFactory< newTP, arg1, arg2, arg3, arg4, arg5,
                arg6, arg7, arg8, arg9, arg10,
                arg11, arg12, arg13, arg14 >;
        return new tpClosure14< arg1, arg2, arg3, arg4, arg5,
                arg6, arg7, arg8, arg9, arg10,
                arg11, arg12, arg13, arg14 > (funct, NULL, A1, A2, A3, A4, A5,
                A6, A7, A8, A9, A10,
                A11, A12, A13, A14);
    }

    template<class newTP, class arg1, class arg2, class arg3, class arg4, class arg5,
    class arg6, class arg7, class arg8, class arg9, class arg10,
    class arg11, class arg12, class arg13, class arg14, class arg15 >
    ThreadedProcedure *
    TPFactory(tpClosure * closure) {
        tpClosure15< arg1, arg2, arg3, arg4, arg5,
                arg6, arg7, arg8, arg9, arg10,
                arg11, arg12, arg13, arg14, arg15 > * args = static_cast<tpClosure15< arg1, arg2, arg3, arg4, arg5,
                arg6, arg7, arg8, arg9, arg10,
                arg11, arg12, arg13, arg14, arg15 >*> (closure);
        myThread.tempParent = args->parent;
        ThreadedProcedure * temp = new newTP(args->a1, args->a2, args->a3, args->a4, args->a5,
                args->a6, args->a7, args->a8, args->a9, args->a10,
                args->a11, args->a12, args->a13, args->a14, args->a15);
        if (temp->decRef()) {
            delete temp;
            return NULL;
        }
        myThread.tempParent = NULL;
        return temp;
    }

    template<class newTP, class arg1, class arg2, class arg3, class arg4, class arg5,
    class arg6, class arg7, class arg8, class arg9, class arg10,
    class arg11, class arg12, class arg13, class arg14, class arg15 >
    void
    invoke(ThreadedProcedure * parentTP, arg1 A1, arg2 A2, arg3 A3, arg4 A4, arg5 A5,
            arg6 A6, arg7 A7, arg8 A8, arg9 A9, arg10 A10,
            arg11 A11, arg12 A12, arg13 A13, arg14 A14, arg15 A15) {
        parentTP->incRef();
        tpfactory funct = &TPFactory< newTP, arg1, arg2, arg3, arg4, arg5,
                arg6, arg7, arg8, arg9, arg10,
                arg11, arg12, arg13, arg14, arg15 >;
        tpClosure * closure = new tpClosure15< arg1, arg2, arg3, arg4, arg5,
                arg6, arg7, arg8, arg9, arg10,
                arg11, arg12, arg13, arg14, arg15 > (funct, parentTP, A1, A2, A3, A4, A5,
                A6, A7, A8, A9, A10,
                A11, A12, A13, A14, A15);
        myThread.threadTPsched->pushTP(closure);
    }

    template<class newTP, class arg1, class arg2, class arg3, class arg4, class arg5,
    class arg6, class arg7, class arg8, class arg9, class arg10,
    class arg11, class arg12, class arg13, class arg14, class arg15 >
    tpClosure *
    launch(arg1 A1, arg2 A2, arg3 A3, arg4 A4, arg5 A5,
            arg6 A6, arg7 A7, arg8 A8, arg9 A9, arg10 A10,
            arg11 A11, arg12 A12, arg13 A13, arg14 A14, arg15 A15) {
        tpfactory funct = &TPFactory< newTP, arg1, arg2, arg3, arg4, arg5,
                arg6, arg7, arg8, arg9, arg10,
                arg11, arg12, arg13, arg14, arg15 >;
        return new tpClosure15< arg1, arg2, arg3, arg4, arg5,
                arg6, arg7, arg8, arg9, arg10,
                arg11, arg12, arg13, arg14, arg15 > (funct, NULL, A1, A2, A3, A4, A5,
                A6, A7, A8, A9, A10,
                A11, A12, A13, A14, A15);
    }

    template<class newTP, class arg1, class arg2, class arg3, class arg4, class arg5,
    class arg6, class arg7, class arg8, class arg9, class arg10,
    class arg11, class arg12, class arg13, class arg14, class arg15,
    class arg16 >
    ThreadedProcedure *
    TPFactory(tpClosure * closure) {
        tpClosure16< arg1, arg2, arg3, arg4, arg5,
                arg6, arg7, arg8, arg9, arg10,
                arg11, arg12, arg13, arg14, arg15,
                arg16 > * args = static_cast<tpClosure16< arg1, arg2, arg3, arg4, arg5,
                arg6, arg7, arg8, arg9, arg10,
                arg11, arg12, arg13, arg14, arg15,
                arg16 >*> (closure);
        myThread.tempParent = args->parent;
        ThreadedProcedure * temp = new newTP(args->a1, args->a2, args->a3, args->a4, args->a5,
                args->a6, args->a7, args->a8, args->a9, args->a10,
                args->a11, args->a12, args->a13, args->a14, args->a15,
                args->a16);
        if (temp->decRef()) {
            delete temp;
            return NULL;
        }
        myThread.tempParent = NULL;
        return temp;
    }

    template<class newTP, class arg1, class arg2, class arg3, class arg4, class arg5,
    class arg6, class arg7, class arg8, class arg9, class arg10,
    class arg11, class arg12, class arg13, class arg14, class arg15,
    class arg16 >
    void
    invoke(ThreadedProcedure * parentTP, arg1 A1, arg2 A2, arg3 A3, arg4 A4, arg5 A5,
            arg6 A6, arg7 A7, arg8 A8, arg9 A9, arg10 A10,
            arg11 A11, arg12 A12, arg13 A13, arg14 A14, arg15 A15,
            arg16 A16) {
        parentTP->incRef();
        tpfactory funct = &TPFactory< newTP, arg1, arg2, arg3, arg4, arg5,
                arg6, arg7, arg8, arg9, arg10,
                arg11, arg12, arg13, arg14, arg15,
                arg16 >;
        tpClosure * closure = new tpClosure16< arg1, arg2, arg3, arg4, arg5,
                arg6, arg7, arg8, arg9, arg10,
                arg11, arg12, arg13, arg14, arg15,
                arg16 > (funct, parentTP, A1, A2, A3, A4, A5,
                A6, A7, A8, A9, A10,
                A11, A12, A13, A14, A15,
                A16);
        myThread.threadTPsched->pushTP(closure);
    }

    template<class newTP, class arg1, class arg2, class arg3, class arg4, class arg5,
    class arg6, class arg7, class arg8, class arg9, class arg10,
    class arg11, class arg12, class arg13, class arg14, class arg15,
    class arg16 >
    tpClosure *
    launch(arg1 A1, arg2 A2, arg3 A3, arg4 A4, arg5 A5,
            arg6 A6, arg7 A7, arg8 A8, arg9 A9, arg10 A10,
            arg11 A11, arg12 A12, arg13 A13, arg14 A14, arg15 A15,
            arg16 A16) {
        tpfactory funct = &TPFactory< newTP, arg1, arg2, arg3, arg4, arg5,
                arg6, arg7, arg8, arg9, arg10,
                arg11, arg12, arg13, arg14, arg15,
                arg16 >;
        return new tpClosure16< arg1, arg2, arg3, arg4, arg5,
                arg6, arg7, arg8, arg9, arg10,
                arg11, arg12, arg13, arg14, arg15,
                arg16 > (funct, NULL, A1, A2, A3, A4, A5,
                A6, A7, A8, A9, A10,
                A11, A12, A13, A14, A15,
                A16);
    }

    template<class newTP, class arg1, class arg2, class arg3, class arg4, class arg5,
    class arg6, class arg7, class arg8, class arg9, class arg10,
    class arg11, class arg12, class arg13, class arg14, class arg15,
    class arg16, class arg17 >
    ThreadedProcedure *
    TPFactory(tpClosure * closure) {
        tpClosure17< arg1, arg2, arg3, arg4, arg5,
                arg6, arg7, arg8, arg9, arg10,
                arg11, arg12, arg13, arg14, arg15,
                arg16, arg17 > * args = static_cast<tpClosure17< arg1, arg2, arg3, arg4, arg5,
                arg6, arg7, arg8, arg9, arg10,
                arg11, arg12, arg13, arg14, arg15,
                arg16, arg17 >*> (closure);
        myThread.tempParent = args->parent;
        ThreadedProcedure * temp = new newTP(args->a1, args->a2, args->a3, args->a4, args->a5,
                args->a6, args->a7, args->a8, args->a9, args->a10,
                args->a11, args->a12, args->a13, args->a14, args->a15,
                args->a16, args->a17);
        if (temp->decRef()) {
            delete temp;
            return NULL;
        }
        myThread.tempParent = NULL;
        return temp;
    }

    template<class newTP, class arg1, class arg2, class arg3, class arg4, class arg5,
    class arg6, class arg7, class arg8, class arg9, class arg10,
    class arg11, class arg12, class arg13, class arg14, class arg15,
    class arg16, class arg17 >
    void
    invoke(ThreadedProcedure * parentTP, arg1 A1, arg2 A2, arg3 A3, arg4 A4, arg5 A5,
            arg6 A6, arg7 A7, arg8 A8, arg9 A9, arg10 A10,
            arg11 A11, arg12 A12, arg13 A13, arg14 A14, arg15 A15,
            arg16 A16, arg17 A17) {
        parentTP->incRef();
        tpfactory funct = &TPFactory< newTP, arg1, arg2, arg3, arg4, arg5,
                arg6, arg7, arg8, arg9, arg10,
                arg11, arg12, arg13, arg14, arg15,
                arg16, arg17 >;
        tpClosure * closure = new tpClosure17< arg1, arg2, arg3, arg4, arg5,
                arg6, arg7, arg8, arg9, arg10,
                arg11, arg12, arg13, arg14, arg15,
                arg16, arg17 > (funct, parentTP, A1, A2, A3, A4, A5,
                A6, A7, A8, A9, A10,
                A11, A12, A13, A14, A15,
                A16, A17);
        myThread.threadTPsched->pushTP(closure);
    }

    template<class newTP, class arg1, class arg2, class arg3, class arg4, class arg5,
    class arg6, class arg7, class arg8, class arg9, class arg10,
    class arg11, class arg12, class arg13, class arg14, class arg15,
    class arg16, class arg17 >
    tpClosure *
    launch(arg1 A1, arg2 A2, arg3 A3, arg4 A4, arg5 A5,
            arg6 A6, arg7 A7, arg8 A8, arg9 A9, arg10 A10,
            arg11 A11, arg12 A12, arg13 A13, arg14 A14, arg15 A15,
            arg16 A16, arg17 A17) {
        tpfactory funct = &TPFactory< newTP, arg1, arg2, arg3, arg4, arg5,
                arg6, arg7, arg8, arg9, arg10,
                arg11, arg12, arg13, arg14, arg15,
                arg16, arg17 >;
        return new tpClosure17< arg1, arg2, arg3, arg4, arg5,
                arg6, arg7, arg8, arg9, arg10,
                arg11, arg12, arg13, arg14, arg15,
                arg16, arg17 > (funct, NULL, A1, A2, A3, A4, A5,
                A6, A7, A8, A9, A10,
                A11, A12, A13, A14, A15,
                A16, A17);
    }

    template<class newTP, class arg1, class arg2, class arg3, class arg4, class arg5,
    class arg6, class arg7, class arg8, class arg9, class arg10,
    class arg11, class arg12, class arg13, class arg14, class arg15,
    class arg16, class arg17, class arg18 >
    ThreadedProcedure *
    TPFactory(tpClosure * closure) {
        tpClosure18< arg1, arg2, arg3, arg4, arg5,
                arg6, arg7, arg8, arg9, arg10,
                arg11, arg12, arg13, arg14, arg15,
                arg16, arg17, arg18 > * args = static_cast<tpClosure18< arg1, arg2, arg3, arg4, arg5,
                arg6, arg7, arg8, arg9, arg10,
                arg11, arg12, arg13, arg14, arg15,
                arg16, arg17, arg18 >*> (closure);
        myThread.tempParent = args->parent;
        ThreadedProcedure * temp = new newTP(args->a1, args->a2, args->a3, args->a4, args->a5,
                args->a6, args->a7, args->a8, args->a9, args->a10,
                args->a11, args->a12, args->a13, args->a14, args->a15,
                args->a16, args->a17, args->a18);
        if (temp->decRef()) {
            delete temp;
            return NULL;
        }
        myThread.tempParent = NULL;
        return temp;
    }

    template<class newTP, class arg1, class arg2, class arg3, class arg4, class arg5,
    class arg6, class arg7, class arg8, class arg9, class arg10,
    class arg11, class arg12, class arg13, class arg14, class arg15,
    class arg16, class arg17, class arg18 >
    void
    invoke(ThreadedProcedure * parentTP, arg1 A1, arg2 A2, arg3 A3, arg4 A4, arg5 A5,
            arg6 A6, arg7 A7, arg8 A8, arg9 A9, arg10 A10,
            arg11 A11, arg12 A12, arg13 A13, arg14 A14, arg15 A15,
            arg16 A16, arg17 A17, arg18 A18) {
        parentTP->incRef();
        tpfactory funct = &TPFactory< newTP, arg1, arg2, arg3, arg4, arg5,
                arg6, arg7, arg8, arg9, arg10,
                arg11, arg12, arg13, arg14, arg15,
                arg16, arg17, arg18 >;
        tpClosure * closure = new tpClosure18< arg1, arg2, arg3, arg4, arg5,
                arg6, arg7, arg8, arg9, arg10,
                arg11, arg12, arg13, arg14, arg15,
                arg16, arg17, arg18 > (funct, parentTP, A1, A2, A3, A4, A5,
                A6, A7, A8, A9, A10,
                A11, A12, A13, A14, A15,
                A16, A17, A18);
        myThread.threadTPsched->pushTP(closure);
    }

    template<class newTP, class arg1, class arg2, class arg3, class arg4, class arg5,
    class arg6, class arg7, class arg8, class arg9, class arg10,
    class arg11, class arg12, class arg13, class arg14, class arg15,
    class arg16, class arg17, class arg18 >
    tpClosure *
    launch(arg1 A1, arg2 A2, arg3 A3, arg4 A4, arg5 A5,
            arg6 A6, arg7 A7, arg8 A8, arg9 A9, arg10 A10,
            arg11 A11, arg12 A12, arg13 A13, arg14 A14, arg15 A15,
            arg16 A16, arg17 A17, arg18 A18) {
        tpfactory funct = &TPFactory< newTP, arg1, arg2, arg3, arg4, arg5,
                arg6, arg7, arg8, arg9, arg10,
                arg11, arg12, arg13, arg14, arg15,
                arg16, arg17, arg18 >;
        return new tpClosure18< arg1, arg2, arg3, arg4, arg5,
                arg6, arg7, arg8, arg9, arg10,
                arg11, arg12, arg13, arg14, arg15,
                arg16, arg17, arg18 > (funct, NULL, A1, A2, A3, A4, A5,
                A6, A7, A8, A9, A10,
                A11, A12, A13, A14, A15,
                A16, A17, A18);
    }

    template<class newTP, class arg1, class arg2, class arg3, class arg4, class arg5,
    class arg6, class arg7, class arg8, class arg9, class arg10,
    class arg11, class arg12, class arg13, class arg14, class arg15,
    class arg16, class arg17, class arg18, class arg19 >
    ThreadedProcedure *
    TPFactory(tpClosure * closure) {
        tpClosure19< arg1, arg2, arg3, arg4, arg5,
                arg6, arg7, arg8, arg9, arg10,
                arg11, arg12, arg13, arg14, arg15,
                arg16, arg17, arg18, arg19 > * args = static_cast<tpClosure19< arg1, arg2, arg3, arg4, arg5,
                arg6, arg7, arg8, arg9, arg10,
                arg11, arg12, arg13, arg14, arg15,
                arg16, arg17, arg18, arg19 >*> (closure);
        myThread.tempParent = args->parent;
        ThreadedProcedure * temp = new newTP(args->a1, args->a2, args->a3, args->a4, args->a5,
                args->a6, args->a7, args->a8, args->a9, args->a10,
                args->a11, args->a12, args->a13, args->a14, args->a15,
                args->a16, args->a17, args->a18, args->a19);
        if (temp->decRef()) {
            delete temp;
            return NULL;
        }
        myThread.tempParent = NULL;
        return temp;
    }

    template<class newTP, class arg1, class arg2, class arg3, class arg4, class arg5,
    class arg6, class arg7, class arg8, class arg9, class arg10,
    class arg11, class arg12, class arg13, class arg14, class arg15,
    class arg16, class arg17, class arg18, class arg19 >
    void
    invoke(ThreadedProcedure * parentTP, arg1 A1, arg2 A2, arg3 A3, arg4 A4, arg5 A5,
            arg6 A6, arg7 A7, arg8 A8, arg9 A9, arg10 A10,
            arg11 A11, arg12 A12, arg13 A13, arg14 A14, arg15 A15,
            arg16 A16, arg17 A17, arg18 A18, arg19 A19) {
        parentTP->incRef();
        tpfactory funct = &TPFactory< newTP, arg1, arg2, arg3, arg4, arg5,
                arg6, arg7, arg8, arg9, arg10,
                arg11, arg12, arg13, arg14, arg15,
                arg16, arg17, arg18, arg19 >;
        tpClosure * closure = new tpClosure19< arg1, arg2, arg3, arg4, arg5,
                arg6, arg7, arg8, arg9, arg10,
                arg11, arg12, arg13, arg14, arg15,
                arg16, arg17, arg18, arg19 > (funct, parentTP, A1, A2, A3, A4, A5,
                A6, A7, A8, A9, A10,
                A11, A12, A13, A14, A15,
                A16, A17, A18, A19);
        myThread.threadTPsched->pushTP(closure);
    }

    template<class newTP, class arg1, class arg2, class arg3, class arg4, class arg5,
    class arg6, class arg7, class arg8, class arg9, class arg10,
    class arg11, class arg12, class arg13, class arg14, class arg15,
    class arg16, class arg17, class arg18, class arg19 >
    tpClosure *
    launch(arg1 A1, arg2 A2, arg3 A3, arg4 A4, arg5 A5,
            arg6 A6, arg7 A7, arg8 A8, arg9 A9, arg10 A10,
            arg11 A11, arg12 A12, arg13 A13, arg14 A14, arg15 A15,
            arg16 A16, arg17 A17, arg18 A18, arg19 A19) {
        tpfactory funct = &TPFactory< newTP, arg1, arg2, arg3, arg4, arg5,
                arg6, arg7, arg8, arg9, arg10,
                arg11, arg12, arg13, arg14, arg15,
                arg16, arg17, arg18, arg19 >;
        return new tpClosure19< arg1, arg2, arg3, arg4, arg5,
                arg6, arg7, arg8, arg9, arg10,
                arg11, arg12, arg13, arg14, arg15,
                arg16, arg17, arg18, arg19 > (funct, NULL, A1, A2, A3, A4, A5,
                A6, A7, A8, A9, A10,
                A11, A12, A13, A14, A15,
                A16, A17, A18, A19);
    }

    template<class newTP, class arg1, class arg2, class arg3, class arg4, class arg5,
    class arg6, class arg7, class arg8, class arg9, class arg10,
    class arg11, class arg12, class arg13, class arg14, class arg15,
    class arg16, class arg17, class arg18, class arg19, class arg20 >
    ThreadedProcedure *
    TPFactory(tpClosure * closure) {
        tpClosure20< arg1, arg2, arg3, arg4, arg5,
                arg6, arg7, arg8, arg9, arg10,
                arg11, arg12, arg13, arg14, arg15,
                arg16, arg17, arg18, arg19, arg20 > * args = static_cast<tpClosure20< arg1, arg2, arg3, arg4, arg5,
                arg6, arg7, arg8, arg9, arg10,
                arg11, arg12, arg13, arg14, arg15,
                arg16, arg17, arg18, arg19, arg20 >*> (closure);
        myThread.tempParent = args->parent;
        ThreadedProcedure * temp = new newTP(args->a1, args->a2, args->a3, args->a4, args->a5,
                args->a6, args->a7, args->a8, args->a9, args->a10,
                args->a11, args->a12, args->a13, args->a14, args->a15,
                args->a16, args->a17, args->a18, args->a19, args->a20);
        if (temp->decRef()) {
            delete temp;
            return NULL;
        }
        myThread.tempParent = NULL;
        return temp;
    }

    template<class newTP, class arg1, class arg2, class arg3, class arg4, class arg5,
    class arg6, class arg7, class arg8, class arg9, class arg10,
    class arg11, class arg12, class arg13, class arg14, class arg15,
    class arg16, class arg17, class arg18, class arg19, class arg20 >
    void
    invoke(ThreadedProcedure * parentTP, arg1 A1, arg2 A2, arg3 A3, arg4 A4, arg5 A5,
            arg6 A6, arg7 A7, arg8 A8, arg9 A9, arg10 A10,
            arg11 A11, arg12 A12, arg13 A13, arg14 A14, arg15 A15,
            arg16 A16, arg17 A17, arg18 A18, arg19 A19, arg20 A20) {
        parentTP->incRef();
        tpfactory funct = &TPFactory< newTP, arg1, arg2, arg3, arg4, arg5,
                arg6, arg7, arg8, arg9, arg10,
                arg11, arg12, arg13, arg14, arg15,
                arg16, arg17, arg18, arg19, arg20 >;
        tpClosure * closure = new tpClosure20< arg1, arg2, arg3, arg4, arg5,
                arg6, arg7, arg8, arg9, arg10,
                arg11, arg12, arg13, arg14, arg15,
                arg16, arg17, arg18, arg19, arg20 > (funct, parentTP, A1, A2, A3, A4, A5,
                A6, A7, A8, A9, A10,
                A11, A12, A13, A14, A15,
                A16, A17, A18, A19, A20);
        myThread.threadTPsched->pushTP(closure);
    }

    template<class newTP, class arg1, class arg2, class arg3, class arg4, class arg5,
    class arg6, class arg7, class arg8, class arg9, class arg10,
    class arg11, class arg12, class arg13, class arg14, class arg15,
    class arg16, class arg17, class arg18, class arg19, class arg20 >
    tpClosure *
    launch(arg1 A1, arg2 A2, arg3 A3, arg4 A4, arg5 A5,
            arg6 A6, arg7 A7, arg8 A8, arg9 A9, arg10 A10,
            arg11 A11, arg12 A12, arg13 A13, arg14 A14, arg15 A15,
            arg16 A16, arg17 A17, arg18 A18, arg19 A19, arg20 A20) {
        tpfactory funct = &TPFactory< newTP, arg1, arg2, arg3, arg4, arg5,
                arg6, arg7, arg8, arg9, arg10,
                arg11, arg12, arg13, arg14, arg15,
                arg16, arg17, arg18, arg19, arg20 >;
        return new tpClosure20< arg1, arg2, arg3, arg4, arg5,
                arg6, arg7, arg8, arg9, arg10,
                arg11, arg12, arg13, arg14, arg15,
                arg16, arg17, arg18, arg19, arg20 > (funct, NULL, A1, A2, A3, A4, A5,
                A6, A7, A8, A9, A10,
                A11, A12, A13, A14, A15,
                A16, A17, A18, A19, A20);
    }

    template<class newTP, class arg1, class arg2, class arg3, class arg4, class arg5,
    class arg6, class arg7, class arg8, class arg9, class arg10,
    class arg11, class arg12, class arg13, class arg14, class arg15,
    class arg16, class arg17, class arg18, class arg19, class arg20,
    class arg21 >
    ThreadedProcedure *
    TPFactory(tpClosure * closure) {
        tpClosure21< arg1, arg2, arg3, arg4, arg5,
                arg6, arg7, arg8, arg9, arg10,
                arg11, arg12, arg13, arg14, arg15,
                arg16, arg17, arg18, arg19, arg20,
                arg21 > * args = static_cast<tpClosure21< arg1, arg2, arg3, arg4, arg5,
                arg6, arg7, arg8, arg9, arg10,
                arg11, arg12, arg13, arg14, arg15,
                arg16, arg17, arg18, arg19, arg20,
                arg21 >*> (closure);
        myThread.tempParent = args->parent;
        ThreadedProcedure * temp = new newTP(args->a1, args->a2, args->a3, args->a4, args->a5,
                args->a6, args->a7, args->a8, args->a9, args->a10,
                args->a11, args->a12, args->a13, args->a14, args->a15,
                args->a16, args->a17, args->a18, args->a19, args->a20,
                args->a21);
        if (temp->decRef()) {
            delete temp;
            return NULL;
        }
        myThread.tempParent = NULL;
        return temp;
    }

    template<class newTP, class arg1, class arg2, class arg3, class arg4, class arg5,
    class arg6, class arg7, class arg8, class arg9, class arg10,
    class arg11, class arg12, class arg13, class arg14, class arg15,
    class arg16, class arg17, class arg18, class arg19, class arg20,
    class arg21 >
    void
    invoke(ThreadedProcedure * parentTP, arg1 A1, arg2 A2, arg3 A3, arg4 A4, arg5 A5,
            arg6 A6, arg7 A7, arg8 A8, arg9 A9, arg10 A10,
            arg11 A11, arg12 A12, arg13 A13, arg14 A14, arg15 A15,
            arg16 A16, arg17 A17, arg18 A18, arg19 A19, arg20 A20,
            arg21 A21) {
        parentTP->incRef();
        tpfactory funct = &TPFactory< newTP, arg1, arg2, arg3, arg4, arg5,
                arg6, arg7, arg8, arg9, arg10,
                arg11, arg12, arg13, arg14, arg15,
                arg16, arg17, arg18, arg19, arg20,
                arg21 >;
        tpClosure * closure = new tpClosure21< arg1, arg2, arg3, arg4, arg5,
                arg6, arg7, arg8, arg9, arg10,
                arg11, arg12, arg13, arg14, arg15,
                arg16, arg17, arg18, arg19, arg20,
                arg21 > (funct, parentTP, A1, A2, A3, A4, A5,
                A6, A7, A8, A9, A10,
                A11, A12, A13, A14, A15,
                A16, A17, A18, A19, A20,
                A21);
        myThread.threadTPsched->pushTP(closure);
    }

    template<class newTP, class arg1, class arg2, class arg3, class arg4, class arg5,
    class arg6, class arg7, class arg8, class arg9, class arg10,
    class arg11, class arg12, class arg13, class arg14, class arg15,
    class arg16, class arg17, class arg18, class arg19, class arg20,
    class arg21 >
    tpClosure *
    launch(arg1 A1, arg2 A2, arg3 A3, arg4 A4, arg5 A5,
            arg6 A6, arg7 A7, arg8 A8, arg9 A9, arg10 A10,
            arg11 A11, arg12 A12, arg13 A13, arg14 A14, arg15 A15,
            arg16 A16, arg17 A17, arg18 A18, arg19 A19, arg20 A20,
            arg21 A21) {
        tpfactory funct = &TPFactory< newTP, arg1, arg2, arg3, arg4, arg5,
                arg6, arg7, arg8, arg9, arg10,
                arg11, arg12, arg13, arg14, arg15,
                arg16, arg17, arg18, arg19, arg20,
                arg21 >;
        return new tpClosure21< arg1, arg2, arg3, arg4, arg5,
                arg6, arg7, arg8, arg9, arg10,
                arg11, arg12, arg13, arg14, arg15,
                arg16, arg17, arg18, arg19, arg20,
                arg21 > (funct, NULL, A1, A2, A3, A4, A5,
                A6, A7, A8, A9, A10,
                A11, A12, A13, A14, A15,
                A16, A17, A18, A19, A20,
                A21);
    }

    template<class newTP, class arg1, class arg2, class arg3, class arg4, class arg5,
    class arg6, class arg7, class arg8, class arg9, class arg10,
    class arg11, class arg12, class arg13, class arg14, class arg15,
    class arg16, class arg17, class arg18, class arg19, class arg20,
    class arg21, class arg22 >
    ThreadedProcedure *
    TPFactory(tpClosure * closure) {
        tpClosure22< arg1, arg2, arg3, arg4, arg5,
                arg6, arg7, arg8, arg9, arg10,
                arg11, arg12, arg13, arg14, arg15,
                arg16, arg17, arg18, arg19, arg20,
                arg21, arg22 > * args = static_cast<tpClosure22< arg1, arg2, arg3, arg4, arg5,
                arg6, arg7, arg8, arg9, arg10,
                arg11, arg12, arg13, arg14, arg15,
                arg16, arg17, arg18, arg19, arg20,
                arg21, arg22 >*> (closure);
        myThread.tempParent = args->parent;
        ThreadedProcedure * temp = new newTP(args->a1, args->a2, args->a3, args->a4, args->a5,
                args->a6, args->a7, args->a8, args->a9, args->a10,
                args->a11, args->a12, args->a13, args->a14, args->a15,
                args->a16, args->a17, args->a18, args->a19, args->a20,
                args->a21, args->a22);
        if (temp->decRef()) {
            delete temp;
            return NULL;
        }
        myThread.tempParent = NULL;
        return temp;
    }

    template<class newTP, class arg1, class arg2, class arg3, class arg4, class arg5,
    class arg6, class arg7, class arg8, class arg9, class arg10,
    class arg11, class arg12, class arg13, class arg14, class arg15,
    class arg16, class arg17, class arg18, class arg19, class arg20,
    class arg21, class arg22 >
    void
    invoke(ThreadedProcedure * parentTP, arg1 A1, arg2 A2, arg3 A3, arg4 A4, arg5 A5,
            arg6 A6, arg7 A7, arg8 A8, arg9 A9, arg10 A10,
            arg11 A11, arg12 A12, arg13 A13, arg14 A14, arg15 A15,
            arg16 A16, arg17 A17, arg18 A18, arg19 A19, arg20 A20,
            arg21 A21, arg22 A22) {
        parentTP->incRef();
        tpfactory funct = &TPFactory< newTP, arg1, arg2, arg3, arg4, arg5,
                arg6, arg7, arg8, arg9, arg10,
                arg11, arg12, arg13, arg14, arg15,
                arg16, arg17, arg18, arg19, arg20,
                arg21, arg22 >;
        tpClosure * closure = new tpClosure22< arg1, arg2, arg3, arg4, arg5,
                arg6, arg7, arg8, arg9, arg10,
                arg11, arg12, arg13, arg14, arg15,
                arg16, arg17, arg18, arg19, arg20,
                arg21, arg22 > (funct, parentTP, A1, A2, A3, A4, A5,
                A6, A7, A8, A9, A10,
                A11, A12, A13, A14, A15,
                A16, A17, A18, A19, A20,
                A21, A22);
        myThread.threadTPsched->pushTP(closure);
    }

    template<class newTP, class arg1, class arg2, class arg3, class arg4, class arg5,
    class arg6, class arg7, class arg8, class arg9, class arg10,
    class arg11, class arg12, class arg13, class arg14, class arg15,
    class arg16, class arg17, class arg18, class arg19, class arg20,
    class arg21, class arg22 >
    tpClosure *
    launch(arg1 A1, arg2 A2, arg3 A3, arg4 A4, arg5 A5,
            arg6 A6, arg7 A7, arg8 A8, arg9 A9, arg10 A10,
            arg11 A11, arg12 A12, arg13 A13, arg14 A14, arg15 A15,
            arg16 A16, arg17 A17, arg18 A18, arg19 A19, arg20 A20,
            arg21 A21, arg22 A22) {
        tpfactory funct = &TPFactory< newTP, arg1, arg2, arg3, arg4, arg5,
                arg6, arg7, arg8, arg9, arg10,
                arg11, arg12, arg13, arg14, arg15,
                arg16, arg17, arg18, arg19, arg20,
                arg21, arg22 >;
        return new tpClosure22< arg1, arg2, arg3, arg4, arg5,
                arg6, arg7, arg8, arg9, arg10,
                arg11, arg12, arg13, arg14, arg15,
                arg16, arg17, arg18, arg19, arg20,
                arg21, arg22 > (funct, NULL, A1, A2, A3, A4, A5,
                A6, A7, A8, A9, A10,
                A11, A12, A13, A14, A15,
                A16, A17, A18, A19, A20,
                A21, A22);
    }

    template<class newTP, class arg1, class arg2, class arg3, class arg4, class arg5,
    class arg6, class arg7, class arg8, class arg9, class arg10,
    class arg11, class arg12, class arg13, class arg14, class arg15,
    class arg16, class arg17, class arg18, class arg19, class arg20,
    class arg21, class arg22, class arg23 >
    ThreadedProcedure *
    TPFactory(tpClosure * closure) {
        tpClosure23< arg1, arg2, arg3, arg4, arg5,
                arg6, arg7, arg8, arg9, arg10,
                arg11, arg12, arg13, arg14, arg15,
                arg16, arg17, arg18, arg19, arg20,
                arg21, arg22, arg23 > * args = static_cast<tpClosure23< arg1, arg2, arg3, arg4, arg5,
                arg6, arg7, arg8, arg9, arg10,
                arg11, arg12, arg13, arg14, arg15,
                arg16, arg17, arg18, arg19, arg20,
                arg21, arg22, arg23 >*> (closure);
        myThread.tempParent = args->parent;
        ThreadedProcedure * temp = new newTP(args->a1, args->a2, args->a3, args->a4, args->a5,
                args->a6, args->a7, args->a8, args->a9, args->a10,
                args->a11, args->a12, args->a13, args->a14, args->a15,
                args->a16, args->a17, args->a18, args->a19, args->a20,
                args->a21, args->a22, args->a23);
        if (temp->decRef()) {
            delete temp;
            return NULL;
        }
        myThread.tempParent = NULL;
        return temp;
    }

    template<class newTP, class arg1, class arg2, class arg3, class arg4, class arg5,
    class arg6, class arg7, class arg8, class arg9, class arg10,
    class arg11, class arg12, class arg13, class arg14, class arg15,
    class arg16, class arg17, class arg18, class arg19, class arg20,
    class arg21, class arg22, class arg23 >
    void
    invoke(ThreadedProcedure * parentTP, arg1 A1, arg2 A2, arg3 A3, arg4 A4, arg5 A5,
            arg6 A6, arg7 A7, arg8 A8, arg9 A9, arg10 A10,
            arg11 A11, arg12 A12, arg13 A13, arg14 A14, arg15 A15,
            arg16 A16, arg17 A17, arg18 A18, arg19 A19, arg20 A20,
            arg21 A21, arg22 A22, arg23 A23) {
        parentTP->incRef();
        tpfactory funct = &TPFactory< newTP, arg1, arg2, arg3, arg4, arg5,
                arg6, arg7, arg8, arg9, arg10,
                arg11, arg12, arg13, arg14, arg15,
                arg16, arg17, arg18, arg19, arg20,
                arg21, arg22, arg23 >;
        tpClosure * closure = new tpClosure23< arg1, arg2, arg3, arg4, arg5,
                arg6, arg7, arg8, arg9, arg10,
                arg11, arg12, arg13, arg14, arg15,
                arg16, arg17, arg18, arg19, arg20,
                arg21, arg22, arg23 > (funct, parentTP, A1, A2, A3, A4, A5,
                A6, A7, A8, A9, A10,
                A11, A12, A13, A14, A15,
                A16, A17, A18, A19, A20,
                A21, A22, A23);
        myThread.threadTPsched->pushTP(closure);
    }

    template<class newTP, class arg1, class arg2, class arg3, class arg4, class arg5,
    class arg6, class arg7, class arg8, class arg9, class arg10,
    class arg11, class arg12, class arg13, class arg14, class arg15,
    class arg16, class arg17, class arg18, class arg19, class arg20,
    class arg21, class arg22, class arg23 >
    tpClosure *
    launch(arg1 A1, arg2 A2, arg3 A3, arg4 A4, arg5 A5,
            arg6 A6, arg7 A7, arg8 A8, arg9 A9, arg10 A10,
            arg11 A11, arg12 A12, arg13 A13, arg14 A14, arg15 A15,
            arg16 A16, arg17 A17, arg18 A18, arg19 A19, arg20 A20,
            arg21 A21, arg22 A22, arg23 A23) {
        tpfactory funct = &TPFactory< newTP, arg1, arg2, arg3, arg4, arg5,
                arg6, arg7, arg8, arg9, arg10,
                arg11, arg12, arg13, arg14, arg15,
                arg16, arg17, arg18, arg19, arg20,
                arg21, arg22, arg23 >;
        return new tpClosure23< arg1, arg2, arg3, arg4, arg5,
                arg6, arg7, arg8, arg9, arg10,
                arg11, arg12, arg13, arg14, arg15,
                arg16, arg17, arg18, arg19, arg20,
                arg21, arg22, arg23 > (funct, NULL, A1, A2, A3, A4, A5,
                A6, A7, A8, A9, A10,
                A11, A12, A13, A14, A15,
                A16, A17, A18, A19, A20,
                A21, A22, A23);
    }

    template<class newTP, class arg1, class arg2, class arg3, class arg4, class arg5,
    class arg6, class arg7, class arg8, class arg9, class arg10,
    class arg11, class arg12, class arg13, class arg14, class arg15,
    class arg16, class arg17, class arg18, class arg19, class arg20,
    class arg21, class arg22, class arg23, class arg24 >
    ThreadedProcedure *
    TPFactory(tpClosure * closure) {
        tpClosure24< arg1, arg2, arg3, arg4, arg5,
                arg6, arg7, arg8, arg9, arg10,
                arg11, arg12, arg13, arg14, arg15,
                arg16, arg17, arg18, arg19, arg20,
                arg21, arg22, arg23, arg24 > * args = static_cast<tpClosure24< arg1, arg2, arg3, arg4, arg5,
                arg6, arg7, arg8, arg9, arg10,
                arg11, arg12, arg13, arg14, arg15,
                arg16, arg17, arg18, arg19, arg20,
                arg21, arg22, arg23, arg24 >*> (closure);
        myThread.tempParent = args->parent;
        ThreadedProcedure * temp = new newTP(args->a1, args->a2, args->a3, args->a4, args->a5,
                args->a6, args->a7, args->a8, args->a9, args->a10,
                args->a11, args->a12, args->a13, args->a14, args->a15,
                args->a16, args->a17, args->a18, args->a19, args->a20,
                args->a21, args->a22, args->a23, args->a24);
        if (temp->decRef()) {
            delete temp;
            return NULL;
        }
        myThread.tempParent = NULL;
        return temp;
    }

    template<class newTP, class arg1, class arg2, class arg3, class arg4, class arg5,
    class arg6, class arg7, class arg8, class arg9, class arg10,
    class arg11, class arg12, class arg13, class arg14, class arg15,
    class arg16, class arg17, class arg18, class arg19, class arg20,
    class arg21, class arg22, class arg23, class arg24 >
    void
    invoke(ThreadedProcedure * parentTP, arg1 A1, arg2 A2, arg3 A3, arg4 A4, arg5 A5,
            arg6 A6, arg7 A7, arg8 A8, arg9 A9, arg10 A10,
            arg11 A11, arg12 A12, arg13 A13, arg14 A14, arg15 A15,
            arg16 A16, arg17 A17, arg18 A18, arg19 A19, arg20 A20,
            arg21 A21, arg22 A22, arg23 A23, arg24 A24) {
        parentTP->incRef();
        tpfactory funct = &TPFactory< newTP, arg1, arg2, arg3, arg4, arg5,
                arg6, arg7, arg8, arg9, arg10,
                arg11, arg12, arg13, arg14, arg15,
                arg16, arg17, arg18, arg19, arg20,
                arg21, arg22, arg23, arg24 >;
        tpClosure * closure = new tpClosure24< arg1, arg2, arg3, arg4, arg5,
                arg6, arg7, arg8, arg9, arg10,
                arg11, arg12, arg13, arg14, arg15,
                arg16, arg17, arg18, arg19, arg20,
                arg21, arg22, arg23, arg24 > (funct, parentTP, A1, A2, A3, A4, A5,
                A6, A7, A8, A9, A10,
                A11, A12, A13, A14, A15,
                A16, A17, A18, A19, A20,
                A21, A22, A23, A24);
        myThread.threadTPsched->pushTP(closure);
    }

    template<class newTP, class arg1, class arg2, class arg3, class arg4, class arg5,
    class arg6, class arg7, class arg8, class arg9, class arg10,
    class arg11, class arg12, class arg13, class arg14, class arg15,
    class arg16, class arg17, class arg18, class arg19, class arg20,
    class arg21, class arg22, class arg23, class arg24 >
    tpClosure *
    launch(arg1 A1, arg2 A2, arg3 A3, arg4 A4, arg5 A5,
            arg6 A6, arg7 A7, arg8 A8, arg9 A9, arg10 A10,
            arg11 A11, arg12 A12, arg13 A13, arg14 A14, arg15 A15,
            arg16 A16, arg17 A17, arg18 A18, arg19 A19, arg20 A20,
            arg21 A21, arg22 A22, arg23 A23, arg24 A24) {
        tpfactory funct = &TPFactory< newTP, arg1, arg2, arg3, arg4, arg5,
                arg6, arg7, arg8, arg9, arg10,
                arg11, arg12, arg13, arg14, arg15,
                arg16, arg17, arg18, arg19, arg20,
                arg21, arg22, arg23, arg24 >;
        return new tpClosure24< arg1, arg2, arg3, arg4, arg5,
                arg6, arg7, arg8, arg9, arg10,
                arg11, arg12, arg13, arg14, arg15,
                arg16, arg17, arg18, arg19, arg20,
                arg21, arg22, arg23, arg24 > (funct, NULL, A1, A2, A3, A4, A5,
                A6, A7, A8, A9, A10,
                A11, A12, A13, A14, A15,
                A16, A17, A18, A19, A20,
                A21, A22, A23, A24);
    }

    template<class newTP, class arg1, class arg2, class arg3, class arg4, class arg5,
    class arg6, class arg7, class arg8, class arg9, class arg10,
    class arg11, class arg12, class arg13, class arg14, class arg15,
    class arg16, class arg17, class arg18, class arg19, class arg20,
    class arg21, class arg22, class arg23, class arg24, class arg25 >
    ThreadedProcedure *
    TPFactory(tpClosure * closure) {
        tpClosure25< arg1, arg2, arg3, arg4, arg5,
                arg6, arg7, arg8, arg9, arg10,
                arg11, arg12, arg13, arg14, arg15,
                arg16, arg17, arg18, arg19, arg20,
                arg21, arg22, arg23, arg24, arg25 > * args = static_cast<tpClosure25< arg1, arg2, arg3, arg4, arg5,
                arg6, arg7, arg8, arg9, arg10,
                arg11, arg12, arg13, arg14, arg15,
                arg16, arg17, arg18, arg19, arg20,
                arg21, arg22, arg23, arg24, arg25 >*> (closure);
        myThread.tempParent = args->parent;
        ThreadedProcedure * temp = new newTP(args->a1, args->a2, args->a3, args->a4, args->a5,
                args->a6, args->a7, args->a8, args->a9, args->a10,
                args->a11, args->a12, args->a13, args->a14, args->a15,
                args->a16, args->a17, args->a18, args->a19, args->a20,
                args->a21, args->a22, args->a23, args->a24, args->a25);
        if (temp->decRef()) {
            delete temp;
            return NULL;
        }
        myThread.tempParent = NULL;
        return temp;
    }

    template<class newTP, class arg1, class arg2, class arg3, class arg4, class arg5,
    class arg6, class arg7, class arg8, class arg9, class arg10,
    class arg11, class arg12, class arg13, class arg14, class arg15,
    class arg16, class arg17, class arg18, class arg19, class arg20,
    class arg21, class arg22, class arg23, class arg24, class arg25 >
    void
    invoke(ThreadedProcedure * parentTP, arg1 A1, arg2 A2, arg3 A3, arg4 A4, arg5 A5,
            arg6 A6, arg7 A7, arg8 A8, arg9 A9, arg10 A10,
            arg11 A11, arg12 A12, arg13 A13, arg14 A14, arg15 A15,
            arg16 A16, arg17 A17, arg18 A18, arg19 A19, arg20 A20,
            arg21 A21, arg22 A22, arg23 A23, arg24 A24, arg25 A25) {
        parentTP->incRef();
        tpfactory funct = &TPFactory< newTP, arg1, arg2, arg3, arg4, arg5,
                arg6, arg7, arg8, arg9, arg10,
                arg11, arg12, arg13, arg14, arg15,
                arg16, arg17, arg18, arg19, arg20,
                arg21, arg22, arg23, arg24, arg25 >;
        tpClosure * closure = new tpClosure25< arg1, arg2, arg3, arg4, arg5,
                arg6, arg7, arg8, arg9, arg10,
                arg11, arg12, arg13, arg14, arg15,
                arg16, arg17, arg18, arg19, arg20,
                arg21, arg22, arg23, arg24, arg25 > (funct, parentTP, A1, A2, A3, A4, A5,
                A6, A7, A8, A9, A10,
                A11, A12, A13, A14, A15,
                A16, A17, A18, A19, A20,
                A21, A22, A23, A24, A25);
        myThread.threadTPsched->pushTP(closure);
    }

    template<class newTP, class arg1, class arg2, class arg3, class arg4, class arg5,
    class arg6, class arg7, class arg8, class arg9, class arg10,
    class arg11, class arg12, class arg13, class arg14, class arg15,
    class arg16, class arg17, class arg18, class arg19, class arg20,
    class arg21, class arg22, class arg23, class arg24, class arg25 >
    tpClosure *
    launch(arg1 A1, arg2 A2, arg3 A3, arg4 A4, arg5 A5,
            arg6 A6, arg7 A7, arg8 A8, arg9 A9, arg10 A10,
            arg11 A11, arg12 A12, arg13 A13, arg14 A14, arg15 A15,
            arg16 A16, arg17 A17, arg18 A18, arg19 A19, arg20 A20,
            arg21 A21, arg22 A22, arg23 A23, arg24 A24, arg25 A25) {
        tpfactory funct = &TPFactory< newTP, arg1, arg2, arg3, arg4, arg5,
                arg6, arg7, arg8, arg9, arg10,
                arg11, arg12, arg13, arg14, arg15,
                arg16, arg17, arg18, arg19, arg20,
                arg21, arg22, arg23, arg24, arg25 >;
        return new tpClosure25< arg1, arg2, arg3, arg4, arg5,
                arg6, arg7, arg8, arg9, arg10,
                arg11, arg12, arg13, arg14, arg15,
                arg16, arg17, arg18, arg19, arg20,
                arg21, arg22, arg23, arg24, arg25 > (funct, NULL, A1, A2, A3, A4, A5,
                A6, A7, A8, A9, A10,
                A11, A12, A13, A14, A15,
                A16, A17, A18, A19, A20,
                A21, A22, A23, A24, A25);
    }

    template<class newTP, class arg1, class arg2, class arg3, class arg4, class arg5,
    class arg6, class arg7, class arg8, class arg9, class arg10,
    class arg11, class arg12, class arg13, class arg14, class arg15,
    class arg16, class arg17, class arg18, class arg19, class arg20,
    class arg21, class arg22, class arg23, class arg24, class arg25,
    class arg26 >
    ThreadedProcedure *
    TPFactory(tpClosure * closure) {
        tpClosure26< arg1, arg2, arg3, arg4, arg5,
                arg6, arg7, arg8, arg9, arg10,
                arg11, arg12, arg13, arg14, arg15,
                arg16, arg17, arg18, arg19, arg20,
                arg21, arg22, arg23, arg24, arg25,
                arg26 > * args = static_cast<tpClosure26< arg1, arg2, arg3, arg4, arg5,
                arg6, arg7, arg8, arg9, arg10,
                arg11, arg12, arg13, arg14, arg15,
                arg16, arg17, arg18, arg19, arg20,
                arg21, arg22, arg23, arg24, arg25,
                arg26 >*> (closure);
        myThread.tempParent = args->parent;
        ThreadedProcedure * temp = new newTP(args->a1, args->a2, args->a3, args->a4, args->a5,
                args->a6, args->a7, args->a8, args->a9, args->a10,
                args->a11, args->a12, args->a13, args->a14, args->a15,
                args->a16, args->a17, args->a18, args->a19, args->a20,
                args->a21, args->a22, args->a23, args->a24, args->a25,
                args->a26);
        if (temp->decRef()) {
            delete temp;
            return NULL;
        }
        myThread.tempParent = NULL;
        return temp;
    }

    template<class newTP, class arg1, class arg2, class arg3, class arg4, class arg5,
    class arg6, class arg7, class arg8, class arg9, class arg10,
    class arg11, class arg12, class arg13, class arg14, class arg15,
    class arg16, class arg17, class arg18, class arg19, class arg20,
    class arg21, class arg22, class arg23, class arg24, class arg25,
    class arg26 >
    void
    invoke(ThreadedProcedure * parentTP, arg1 A1, arg2 A2, arg3 A3, arg4 A4, arg5 A5,
            arg6 A6, arg7 A7, arg8 A8, arg9 A9, arg10 A10,
            arg11 A11, arg12 A12, arg13 A13, arg14 A14, arg15 A15,
            arg16 A16, arg17 A17, arg18 A18, arg19 A19, arg20 A20,
            arg21 A21, arg22 A22, arg23 A23, arg24 A24, arg25 A25,
            arg26 A26) {
        parentTP->incRef();
        tpfactory funct = &TPFactory< newTP, arg1, arg2, arg3, arg4, arg5,
                arg6, arg7, arg8, arg9, arg10,
                arg11, arg12, arg13, arg14, arg15,
                arg16, arg17, arg18, arg19, arg20,
                arg21, arg22, arg23, arg24, arg25,
                arg26 >;
        tpClosure * closure = new tpClosure26< arg1, arg2, arg3, arg4, arg5,
                arg6, arg7, arg8, arg9, arg10,
                arg11, arg12, arg13, arg14, arg15,
                arg16, arg17, arg18, arg19, arg20,
                arg21, arg22, arg23, arg24, arg25,
                arg26 > (funct, parentTP, A1, A2, A3, A4, A5,
                A6, A7, A8, A9, A10,
                A11, A12, A13, A14, A15,
                A16, A17, A18, A19, A20,
                A21, A22, A23, A24, A25,
                A26);
        myThread.threadTPsched->pushTP(closure);
    }

    template<class newTP, class arg1, class arg2, class arg3, class arg4, class arg5,
    class arg6, class arg7, class arg8, class arg9, class arg10,
    class arg11, class arg12, class arg13, class arg14, class arg15,
    class arg16, class arg17, class arg18, class arg19, class arg20,
    class arg21, class arg22, class arg23, class arg24, class arg25,
    class arg26 >
    tpClosure *
    launch(arg1 A1, arg2 A2, arg3 A3, arg4 A4, arg5 A5,
            arg6 A6, arg7 A7, arg8 A8, arg9 A9, arg10 A10,
            arg11 A11, arg12 A12, arg13 A13, arg14 A14, arg15 A15,
            arg16 A16, arg17 A17, arg18 A18, arg19 A19, arg20 A20,
            arg21 A21, arg22 A22, arg23 A23, arg24 A24, arg25 A25,
            arg26 A26) {
        tpfactory funct = &TPFactory< newTP, arg1, arg2, arg3, arg4, arg5,
                arg6, arg7, arg8, arg9, arg10,
                arg11, arg12, arg13, arg14, arg15,
                arg16, arg17, arg18, arg19, arg20,
                arg21, arg22, arg23, arg24, arg25,
                arg26 >;
        return new tpClosure26< arg1, arg2, arg3, arg4, arg5,
                arg6, arg7, arg8, arg9, arg10,
                arg11, arg12, arg13, arg14, arg15,
                arg16, arg17, arg18, arg19, arg20,
                arg21, arg22, arg23, arg24, arg25,
                arg26 > (funct, NULL, A1, A2, A3, A4, A5,
                A6, A7, A8, A9, A10,
                A11, A12, A13, A14, A15,
                A16, A17, A18, A19, A20,
                A21, A22, A23, A24, A25,
                A26);
    }

    template<class newTP, class arg1, class arg2, class arg3, class arg4, class arg5,
    class arg6, class arg7, class arg8, class arg9, class arg10,
    class arg11, class arg12, class arg13, class arg14, class arg15,
    class arg16, class arg17, class arg18, class arg19, class arg20,
    class arg21, class arg22, class arg23, class arg24, class arg25,
    class arg26, class arg27 >
    ThreadedProcedure *
    TPFactory(tpClosure * closure) {
        tpClosure27< arg1, arg2, arg3, arg4, arg5,
                arg6, arg7, arg8, arg9, arg10,
                arg11, arg12, arg13, arg14, arg15,
                arg16, arg17, arg18, arg19, arg20,
                arg21, arg22, arg23, arg24, arg25,
                arg26, arg27 > * args = static_cast<tpClosure27< arg1, arg2, arg3, arg4, arg5,
                arg6, arg7, arg8, arg9, arg10,
                arg11, arg12, arg13, arg14, arg15,
                arg16, arg17, arg18, arg19, arg20,
                arg21, arg22, arg23, arg24, arg25,
                arg26, arg27 >*> (closure);
        myThread.tempParent = args->parent;
        ThreadedProcedure * temp = new newTP(args->a1, args->a2, args->a3, args->a4, args->a5,
                args->a6, args->a7, args->a8, args->a9, args->a10,
                args->a11, args->a12, args->a13, args->a14, args->a15,
                args->a16, args->a17, args->a18, args->a19, args->a20,
                args->a21, args->a22, args->a23, args->a24, args->a25,
                args->a26, args->a27);
        if (temp->decRef()) {
            delete temp;
            return NULL;
        }
        myThread.tempParent = NULL;
        return temp;
    }

    template<class newTP, class arg1, class arg2, class arg3, class arg4, class arg5,
    class arg6, class arg7, class arg8, class arg9, class arg10,
    class arg11, class arg12, class arg13, class arg14, class arg15,
    class arg16, class arg17, class arg18, class arg19, class arg20,
    class arg21, class arg22, class arg23, class arg24, class arg25,
    class arg26, class arg27 >
    void
    invoke(ThreadedProcedure * parentTP, arg1 A1, arg2 A2, arg3 A3, arg4 A4, arg5 A5,
            arg6 A6, arg7 A7, arg8 A8, arg9 A9, arg10 A10,
            arg11 A11, arg12 A12, arg13 A13, arg14 A14, arg15 A15,
            arg16 A16, arg17 A17, arg18 A18, arg19 A19, arg20 A20,
            arg21 A21, arg22 A22, arg23 A23, arg24 A24, arg25 A25,
            arg26 A26, arg27 A27) {
        parentTP->incRef();
        tpfactory funct = &TPFactory< newTP, arg1, arg2, arg3, arg4, arg5,
                arg6, arg7, arg8, arg9, arg10,
                arg11, arg12, arg13, arg14, arg15,
                arg16, arg17, arg18, arg19, arg20,
                arg21, arg22, arg23, arg24, arg25,
                arg26, arg27 >;
        tpClosure * closure = new tpClosure27< arg1, arg2, arg3, arg4, arg5,
                arg6, arg7, arg8, arg9, arg10,
                arg11, arg12, arg13, arg14, arg15,
                arg16, arg17, arg18, arg19, arg20,
                arg21, arg22, arg23, arg24, arg25,
                arg26, arg27 > (funct, parentTP, A1, A2, A3, A4, A5,
                A6, A7, A8, A9, A10,
                A11, A12, A13, A14, A15,
                A16, A17, A18, A19, A20,
                A21, A22, A23, A24, A25,
                A26, A27);
        myThread.threadTPsched->pushTP(closure);
    }

    template<class newTP, class arg1, class arg2, class arg3, class arg4, class arg5,
    class arg6, class arg7, class arg8, class arg9, class arg10,
    class arg11, class arg12, class arg13, class arg14, class arg15,
    class arg16, class arg17, class arg18, class arg19, class arg20,
    class arg21, class arg22, class arg23, class arg24, class arg25,
    class arg26, class arg27 >
    tpClosure *
    launch(arg1 A1, arg2 A2, arg3 A3, arg4 A4, arg5 A5,
            arg6 A6, arg7 A7, arg8 A8, arg9 A9, arg10 A10,
            arg11 A11, arg12 A12, arg13 A13, arg14 A14, arg15 A15,
            arg16 A16, arg17 A17, arg18 A18, arg19 A19, arg20 A20,
            arg21 A21, arg22 A22, arg23 A23, arg24 A24, arg25 A25,
            arg26 A26, arg27 A27) {
        tpfactory funct = &TPFactory< newTP, arg1, arg2, arg3, arg4, arg5,
                arg6, arg7, arg8, arg9, arg10,
                arg11, arg12, arg13, arg14, arg15,
                arg16, arg17, arg18, arg19, arg20,
                arg21, arg22, arg23, arg24, arg25,
                arg26, arg27 >;
        return new tpClosure27< arg1, arg2, arg3, arg4, arg5,
                arg6, arg7, arg8, arg9, arg10,
                arg11, arg12, arg13, arg14, arg15,
                arg16, arg17, arg18, arg19, arg20,
                arg21, arg22, arg23, arg24, arg25,
                arg26, arg27 > (funct, NULL, A1, A2, A3, A4, A5,
                A6, A7, A8, A9, A10,
                A11, A12, A13, A14, A15,
                A16, A17, A18, A19, A20,
                A21, A22, A23, A24, A25,
                A26, A27);
    }

    template<class newTP, class arg1, class arg2, class arg3, class arg4, class arg5,
    class arg6, class arg7, class arg8, class arg9, class arg10,
    class arg11, class arg12, class arg13, class arg14, class arg15,
    class arg16, class arg17, class arg18, class arg19, class arg20,
    class arg21, class arg22, class arg23, class arg24, class arg25,
    class arg26, class arg27, class arg28 >
    ThreadedProcedure *
    TPFactory(tpClosure * closure) {
        tpClosure28< arg1, arg2, arg3, arg4, arg5,
                arg6, arg7, arg8, arg9, arg10,
                arg11, arg12, arg13, arg14, arg15,
                arg16, arg17, arg18, arg19, arg20,
                arg21, arg22, arg23, arg24, arg25,
                arg26, arg27, arg28 > * args = static_cast<tpClosure28< arg1, arg2, arg3, arg4, arg5,
                arg6, arg7, arg8, arg9, arg10,
                arg11, arg12, arg13, arg14, arg15,
                arg16, arg17, arg18, arg19, arg20,
                arg21, arg22, arg23, arg24, arg25,
                arg26, arg27, arg28 >*> (closure);
        myThread.tempParent = args->parent;
        ThreadedProcedure * temp = new newTP(args->a1, args->a2, args->a3, args->a4, args->a5,
                args->a6, args->a7, args->a8, args->a9, args->a10,
                args->a11, args->a12, args->a13, args->a14, args->a15,
                args->a16, args->a17, args->a18, args->a19, args->a20,
                args->a21, args->a22, args->a23, args->a24, args->a25,
                args->a26, args->a27, args->a28);
        if (temp->decRef()) {
            delete temp;
            return NULL;
        }
        myThread.tempParent = NULL;
        return temp;
    }

    template<class newTP, class arg1, class arg2, class arg3, class arg4, class arg5,
    class arg6, class arg7, class arg8, class arg9, class arg10,
    class arg11, class arg12, class arg13, class arg14, class arg15,
    class arg16, class arg17, class arg18, class arg19, class arg20,
    class arg21, class arg22, class arg23, class arg24, class arg25,
    class arg26, class arg27, class arg28 >
    void
    invoke(ThreadedProcedure * parentTP, arg1 A1, arg2 A2, arg3 A3, arg4 A4, arg5 A5,
            arg6 A6, arg7 A7, arg8 A8, arg9 A9, arg10 A10,
            arg11 A11, arg12 A12, arg13 A13, arg14 A14, arg15 A15,
            arg16 A16, arg17 A17, arg18 A18, arg19 A19, arg20 A20,
            arg21 A21, arg22 A22, arg23 A23, arg24 A24, arg25 A25,
            arg26 A26, arg27 A27, arg28 A28) {
        parentTP->incRef();
        tpfactory funct = &TPFactory< newTP, arg1, arg2, arg3, arg4, arg5,
                arg6, arg7, arg8, arg9, arg10,
                arg11, arg12, arg13, arg14, arg15,
                arg16, arg17, arg18, arg19, arg20,
                arg21, arg22, arg23, arg24, arg25,
                arg26, arg27, arg28 >;
        tpClosure * closure = new tpClosure28< arg1, arg2, arg3, arg4, arg5,
                arg6, arg7, arg8, arg9, arg10,
                arg11, arg12, arg13, arg14, arg15,
                arg16, arg17, arg18, arg19, arg20,
                arg21, arg22, arg23, arg24, arg25,
                arg26, arg27, arg28 > (funct, parentTP, A1, A2, A3, A4, A5,
                A6, A7, A8, A9, A10,
                A11, A12, A13, A14, A15,
                A16, A17, A18, A19, A20,
                A21, A22, A23, A24, A25,
                A26, A27, A28);
        myThread.threadTPsched->pushTP(closure);
    }

    template<class newTP, class arg1, class arg2, class arg3, class arg4, class arg5,
    class arg6, class arg7, class arg8, class arg9, class arg10,
    class arg11, class arg12, class arg13, class arg14, class arg15,
    class arg16, class arg17, class arg18, class arg19, class arg20,
    class arg21, class arg22, class arg23, class arg24, class arg25,
    class arg26, class arg27, class arg28 >
    tpClosure *
    launch(arg1 A1, arg2 A2, arg3 A3, arg4 A4, arg5 A5,
            arg6 A6, arg7 A7, arg8 A8, arg9 A9, arg10 A10,
            arg11 A11, arg12 A12, arg13 A13, arg14 A14, arg15 A15,
            arg16 A16, arg17 A17, arg18 A18, arg19 A19, arg20 A20,
            arg21 A21, arg22 A22, arg23 A23, arg24 A24, arg25 A25,
            arg26 A26, arg27 A27, arg28 A28) {
        tpfactory funct = &TPFactory< newTP, arg1, arg2, arg3, arg4, arg5,
                arg6, arg7, arg8, arg9, arg10,
                arg11, arg12, arg13, arg14, arg15,
                arg16, arg17, arg18, arg19, arg20,
                arg21, arg22, arg23, arg24, arg25,
                arg26, arg27, arg28 >;
        return new tpClosure28< arg1, arg2, arg3, arg4, arg5,
                arg6, arg7, arg8, arg9, arg10,
                arg11, arg12, arg13, arg14, arg15,
                arg16, arg17, arg18, arg19, arg20,
                arg21, arg22, arg23, arg24, arg25,
                arg26, arg27, arg28 > (funct, NULL, A1, A2, A3, A4, A5,
                A6, A7, A8, A9, A10,
                A11, A12, A13, A14, A15,
                A16, A17, A18, A19, A20,
                A21, A22, A23, A24, A25,
                A26, A27, A28);
    }

    template<class newTP, class arg1, class arg2, class arg3, class arg4, class arg5,
    class arg6, class arg7, class arg8, class arg9, class arg10,
    class arg11, class arg12, class arg13, class arg14, class arg15,
    class arg16, class arg17, class arg18, class arg19, class arg20,
    class arg21, class arg22, class arg23, class arg24, class arg25,
    class arg26, class arg27, class arg28, class arg29 >
    ThreadedProcedure *
    TPFactory(tpClosure * closure) {
        tpClosure29< arg1, arg2, arg3, arg4, arg5,
                arg6, arg7, arg8, arg9, arg10,
                arg11, arg12, arg13, arg14, arg15,
                arg16, arg17, arg18, arg19, arg20,
                arg21, arg22, arg23, arg24, arg25,
                arg26, arg27, arg28, arg29 > * args = static_cast<tpClosure29< arg1, arg2, arg3, arg4, arg5,
                arg6, arg7, arg8, arg9, arg10,
                arg11, arg12, arg13, arg14, arg15,
                arg16, arg17, arg18, arg19, arg20,
                arg21, arg22, arg23, arg24, arg25,
                arg26, arg27, arg28, arg29 >*> (closure);
        myThread.tempParent = args->parent;
        ThreadedProcedure * temp = new newTP(args->a1, args->a2, args->a3, args->a4, args->a5,
                args->a6, args->a7, args->a8, args->a9, args->a10,
                args->a11, args->a12, args->a13, args->a14, args->a15,
                args->a16, args->a17, args->a18, args->a19, args->a20,
                args->a21, args->a22, args->a23, args->a24, args->a25,
                args->a26, args->a27, args->a28, args->a29);
        if (temp->decRef()) {
            delete temp;
            return NULL;
        }
        myThread.tempParent = NULL;
        return temp;

    }

    template<class newTP, class arg1, class arg2, class arg3, class arg4, class arg5,
    class arg6, class arg7, class arg8, class arg9, class arg10,
    class arg11, class arg12, class arg13, class arg14, class arg15,
    class arg16, class arg17, class arg18, class arg19, class arg20,
    class arg21, class arg22, class arg23, class arg24, class arg25,
    class arg26, class arg27, class arg28, class arg29 >
    void
    invoke(ThreadedProcedure * parentTP, arg1 A1, arg2 A2, arg3 A3, arg4 A4, arg5 A5,
            arg6 A6, arg7 A7, arg8 A8, arg9 A9, arg10 A10,
            arg11 A11, arg12 A12, arg13 A13, arg14 A14, arg15 A15,
            arg16 A16, arg17 A17, arg18 A18, arg19 A19, arg20 A20,
            arg21 A21, arg22 A22, arg23 A23, arg24 A24, arg25 A25,
            arg26 A26, arg27 A27, arg28 A28, arg29 A29) {
        parentTP->incRef();
        tpfactory funct = &TPFactory< newTP, arg1, arg2, arg3, arg4, arg5,
                arg6, arg7, arg8, arg9, arg10,
                arg11, arg12, arg13, arg14, arg15,
                arg16, arg17, arg18, arg19, arg20,
                arg21, arg22, arg23, arg24, arg25,
                arg26, arg27, arg28, arg29 >;
        tpClosure * closure = new tpClosure29< arg1, arg2, arg3, arg4, arg5,
                arg6, arg7, arg8, arg9, arg10,
                arg11, arg12, arg13, arg14, arg15,
                arg16, arg17, arg18, arg19, arg20,
                arg21, arg22, arg23, arg24, arg25,
                arg26, arg27, arg28, arg29 > (funct, parentTP, A1, A2, A3, A4, A5,
                A6, A7, A8, A9, A10,
                A11, A12, A13, A14, A15,
                A16, A17, A18, A19, A20,
                A21, A22, A23, A24, A25,
                A26, A27, A28, A29);
        myThread.threadTPsched->pushTP(closure);
    }

    template<class newTP, class arg1, class arg2, class arg3, class arg4, class arg5,
    class arg6, class arg7, class arg8, class arg9, class arg10,
    class arg11, class arg12, class arg13, class arg14, class arg15,
    class arg16, class arg17, class arg18, class arg19, class arg20,
    class arg21, class arg22, class arg23, class arg24, class arg25,
    class arg26, class arg27, class arg28, class arg29 >
    tpClosure *
    launch(arg1 A1, arg2 A2, arg3 A3, arg4 A4, arg5 A5,
            arg6 A6, arg7 A7, arg8 A8, arg9 A9, arg10 A10,
            arg11 A11, arg12 A12, arg13 A13, arg14 A14, arg15 A15,
            arg16 A16, arg17 A17, arg18 A18, arg19 A19, arg20 A20,
            arg21 A21, arg22 A22, arg23 A23, arg24 A24, arg25 A25,
            arg26 A26, arg27 A27, arg28 A28, arg29 A29) {
        tpfactory funct = &TPFactory< newTP, arg1, arg2, arg3, arg4, arg5,
                arg6, arg7, arg8, arg9, arg10,
                arg11, arg12, arg13, arg14, arg15,
                arg16, arg17, arg18, arg19, arg20,
                arg21, arg22, arg23, arg24, arg25,
                arg26, arg27, arg28, arg29 >;
        return new tpClosure29< arg1, arg2, arg3, arg4, arg5,
                arg6, arg7, arg8, arg9, arg10,
                arg11, arg12, arg13, arg14, arg15,
                arg16, arg17, arg18, arg19, arg20,
                arg21, arg22, arg23, arg24, arg25,
                arg26, arg27, arg28, arg29 > (funct, NULL, A1, A2, A3, A4, A5,
                A6, A7, A8, A9, A10,
                A11, A12, A13, A14, A15,
                A16, A17, A18, A19, A20,
                A21, A22, A23, A24, A25,
                A26, A27, A28, A29);
    }

    template<class newTP, class arg1, class arg2, class arg3, class arg4, class arg5,
    class arg6, class arg7, class arg8, class arg9, class arg10,
    class arg11, class arg12, class arg13, class arg14, class arg15,
    class arg16, class arg17, class arg18, class arg19, class arg20,
    class arg21, class arg22, class arg23, class arg24, class arg25,
    class arg26, class arg27, class arg28, class arg29, class arg30 >
    ThreadedProcedure *
    TPFactory(tpClosure * closure) {
        tpClosure30< arg1, arg2, arg3, arg4, arg5,
                arg6, arg7, arg8, arg9, arg10,
                arg11, arg12, arg13, arg14, arg15,
                arg16, arg17, arg18, arg19, arg20,
                arg21, arg22, arg23, arg24, arg25,
                arg26, arg27, arg28, arg29, arg30 > * args = static_cast<tpClosure30< arg1, arg2, arg3, arg4, arg5,
                arg6, arg7, arg8, arg9, arg10,
                arg11, arg12, arg13, arg14, arg15,
                arg16, arg17, arg18, arg19, arg20,
                arg21, arg22, arg23, arg24, arg25,
                arg26, arg27, arg28, arg29, arg30 >*> (closure);
        myThread.tempParent = args->parent;
        ThreadedProcedure * temp = new newTP(args->a1, args->a2, args->a3, args->a4, args->a5,
                args->a6, args->a7, args->a8, args->a9, args->a10,
                args->a11, args->a12, args->a13, args->a14, args->a15,
                args->a16, args->a17, args->a18, args->a19, args->a20,
                args->a21, args->a22, args->a23, args->a24, args->a25,
                args->a26, args->a27, args->a28, args->a29, args->a30);
        if (temp->decRef()) {
            delete temp;
            return NULL;
        }
        myThread.tempParent = NULL;
        return temp;
    }

    template<class newTP, class arg1, class arg2, class arg3, class arg4, class arg5,
    class arg6, class arg7, class arg8, class arg9, class arg10,
    class arg11, class arg12, class arg13, class arg14, class arg15,
    class arg16, class arg17, class arg18, class arg19, class arg20,
    class arg21, class arg22, class arg23, class arg24, class arg25,
    class arg26, class arg27, class arg28, class arg29, class arg30 >
    void
    invoke(ThreadedProcedure * parentTP, arg1 A1, arg2 A2, arg3 A3, arg4 A4, arg5 A5,
            arg6 A6, arg7 A7, arg8 A8, arg9 A9, arg10 A10,
            arg11 A11, arg12 A12, arg13 A13, arg14 A14, arg15 A15,
            arg16 A16, arg17 A17, arg18 A18, arg19 A19, arg20 A20,
            arg21 A21, arg22 A22, arg23 A23, arg24 A24, arg25 A25,
            arg26 A26, arg27 A27, arg28 A28, arg29 A29, arg30 A30) {
        parentTP->incRef();
        tpfactory funct = &TPFactory< newTP, arg1, arg2, arg3, arg4, arg5,
                arg6, arg7, arg8, arg9, arg10,
                arg11, arg12, arg13, arg14, arg15,
                arg16, arg17, arg18, arg19, arg20,
                arg21, arg22, arg23, arg24, arg25,
                arg26, arg27, arg28, arg29, arg30 >;
        tpClosure * closure = new tpClosure30< arg1, arg2, arg3, arg4, arg5,
                arg6, arg7, arg8, arg9, arg10,
                arg11, arg12, arg13, arg14, arg15,
                arg16, arg17, arg18, arg19, arg20,
                arg21, arg22, arg23, arg24, arg25,
                arg26, arg27, arg28, arg29, arg30 > (funct, parentTP, A1, A2, A3, A4, A5,
                A6, A7, A8, A9, A10,
                A11, A12, A13, A14, A15,
                A16, A17, A18, A19, A20,
                A21, A22, A23, A24, A25,
                A26, A27, A28, A29, A30);
        myThread.threadTPsched->pushTP(closure);
    }

    template<class newTP, class arg1, class arg2, class arg3, class arg4, class arg5,
    class arg6, class arg7, class arg8, class arg9, class arg10,
    class arg11, class arg12, class arg13, class arg14, class arg15,
    class arg16, class arg17, class arg18, class arg19, class arg20,
    class arg21, class arg22, class arg23, class arg24, class arg25,
    class arg26, class arg27, class arg28, class arg29, class arg30 >
    tpClosure *
    launch(arg1 A1, arg2 A2, arg3 A3, arg4 A4, arg5 A5,
            arg6 A6, arg7 A7, arg8 A8, arg9 A9, arg10 A10,
            arg11 A11, arg12 A12, arg13 A13, arg14 A14, arg15 A15,
            arg16 A16, arg17 A17, arg18 A18, arg19 A19, arg20 A20,
            arg21 A21, arg22 A22, arg23 A23, arg24 A24, arg25 A25,
            arg26 A26, arg27 A27, arg28 A28, arg29 A29, arg30 A30) {
        tpfactory funct = &TPFactory< newTP, arg1, arg2, arg3, arg4, arg5,
                arg6, arg7, arg8, arg9, arg10,
                arg11, arg12, arg13, arg14, arg15,
                arg16, arg17, arg18, arg19, arg20,
                arg21, arg22, arg23, arg24, arg25,
                arg26, arg27, arg28, arg29, arg30 >;
        return new tpClosure30< arg1, arg2, arg3, arg4, arg5,
                arg6, arg7, arg8, arg9, arg10,
                arg11, arg12, arg13, arg14, arg15,
                arg16, arg17, arg18, arg19, arg20,
                arg21, arg22, arg23, arg24, arg25,
                arg26, arg27, arg28, arg29, arg30 > (funct, NULL, A1, A2, A3, A4, A5,
                A6, A7, A8, A9, A10,
                A11, A12, A13, A14, A15,
                A16, A17, A18, A19, A20,
                A21, A22, A23, A24, A25,
                A26, A27, A28, A29, A30);
    }

    template<class newTP, class arg1, class arg2, class arg3, class arg4, class arg5,
    class arg6, class arg7, class arg8, class arg9, class arg10,
    class arg11, class arg12, class arg13, class arg14, class arg15,
    class arg16, class arg17, class arg18, class arg19, class arg20,
    class arg21, class arg22, class arg23, class arg24, class arg25,
    class arg26, class arg27, class arg28, class arg29, class arg30,
    class arg31 >
    ThreadedProcedure *
    TPFactory(tpClosure * closure) {
        tpClosure31< arg1, arg2, arg3, arg4, arg5,
                arg6, arg7, arg8, arg9, arg10,
                arg11, arg12, arg13, arg14, arg15,
                arg16, arg17, arg18, arg19, arg20,
                arg21, arg22, arg23, arg24, arg25,
                arg26, arg27, arg28, arg29, arg30,
                arg31 > * args = static_cast<tpClosure31< arg1, arg2, arg3, arg4, arg5,
                arg6, arg7, arg8, arg9, arg10,
                arg11, arg12, arg13, arg14, arg15,
                arg16, arg17, arg18, arg19, arg20,
                arg21, arg22, arg23, arg24, arg25,
                arg26, arg27, arg28, arg29, arg30,
                arg31 >*> (closure);
        myThread.tempParent = args->parent;
        ThreadedProcedure * temp = new newTP(args->a1, args->a2, args->a3, args->a4, args->a5,
                args->a6, args->a7, args->a8, args->a9, args->a10,
                args->a11, args->a12, args->a13, args->a14, args->a15,
                args->a16, args->a17, args->a18, args->a19, args->a20,
                args->a21, args->a22, args->a23, args->a24, args->a25,
                args->a26, args->a27, args->a28, args->a29, args->a30,
                args->a31);
        if (temp->decRef()) {
            delete temp;
            return NULL;
        }
        myThread.tempParent = NULL;
        return temp;
    }

    template<class newTP, class arg1, class arg2, class arg3, class arg4, class arg5,
    class arg6, class arg7, class arg8, class arg9, class arg10,
    class arg11, class arg12, class arg13, class arg14, class arg15,
    class arg16, class arg17, class arg18, class arg19, class arg20,
    class arg21, class arg22, class arg23, class arg24, class arg25,
    class arg26, class arg27, class arg28, class arg29, class arg30,
    class arg31 >
    void
    invoke(ThreadedProcedure * parentTP, arg1 A1, arg2 A2, arg3 A3, arg4 A4, arg5 A5,
            arg6 A6, arg7 A7, arg8 A8, arg9 A9, arg10 A10,
            arg11 A11, arg12 A12, arg13 A13, arg14 A14, arg15 A15,
            arg16 A16, arg17 A17, arg18 A18, arg19 A19, arg20 A20,
            arg21 A21, arg22 A22, arg23 A23, arg24 A24, arg25 A25,
            arg26 A26, arg27 A27, arg28 A28, arg29 A29, arg30 A30,
            arg31 A31) {
        parentTP->incRef();
        tpfactory funct = &TPFactory< newTP, arg1, arg2, arg3, arg4, arg5,
                arg6, arg7, arg8, arg9, arg10,
                arg11, arg12, arg13, arg14, arg15,
                arg16, arg17, arg18, arg19, arg20,
                arg21, arg22, arg23, arg24, arg25,
                arg26, arg27, arg28, arg29, arg30,
                arg31 >;
        tpClosure * closure = new tpClosure31< arg1, arg2, arg3, arg4, arg5,
                arg6, arg7, arg8, arg9, arg10,
                arg11, arg12, arg13, arg14, arg15,
                arg16, arg17, arg18, arg19, arg20,
                arg21, arg22, arg23, arg24, arg25,
                arg26, arg27, arg28, arg29, arg30,
                arg31 > (funct, parentTP, A1, A2, A3, A4, A5,
                A6, A7, A8, A9, A10,
                A11, A12, A13, A14, A15,
                A16, A17, A18, A19, A20,
                A21, A22, A23, A24, A25,
                A26, A27, A28, A29, A30,
                A31);
        myThread.threadTPsched->pushTP(closure);
    }

    template<class newTP, class arg1, class arg2, class arg3, class arg4, class arg5,
    class arg6, class arg7, class arg8, class arg9, class arg10,
    class arg11, class arg12, class arg13, class arg14, class arg15,
    class arg16, class arg17, class arg18, class arg19, class arg20,
    class arg21, class arg22, class arg23, class arg24, class arg25,
    class arg26, class arg27, class arg28, class arg29, class arg30,
    class arg31 >
    tpClosure *
    launch(arg1 A1, arg2 A2, arg3 A3, arg4 A4, arg5 A5,
            arg6 A6, arg7 A7, arg8 A8, arg9 A9, arg10 A10,
            arg11 A11, arg12 A12, arg13 A13, arg14 A14, arg15 A15,
            arg16 A16, arg17 A17, arg18 A18, arg19 A19, arg20 A20,
            arg21 A21, arg22 A22, arg23 A23, arg24 A24, arg25 A25,
            arg26 A26, arg27 A27, arg28 A28, arg29 A29, arg30 A30,
            arg31 A31) {
        tpfactory funct = &TPFactory< newTP, arg1, arg2, arg3, arg4, arg5,
                arg6, arg7, arg8, arg9, arg10,
                arg11, arg12, arg13, arg14, arg15,
                arg16, arg17, arg18, arg19, arg20,
                arg21, arg22, arg23, arg24, arg25,
                arg26, arg27, arg28, arg29, arg30,
                arg31 >;
        return new tpClosure31< arg1, arg2, arg3, arg4, arg5,
                arg6, arg7, arg8, arg9, arg10,
                arg11, arg12, arg13, arg14, arg15,
                arg16, arg17, arg18, arg19, arg20,
                arg21, arg22, arg23, arg24, arg25,
                arg26, arg27, arg28, arg29, arg30,
                arg31 > (funct, NULL, A1, A2, A3, A4, A5,
                A6, A7, A8, A9, A10,
                A11, A12, A13, A14, A15,
                A16, A17, A18, A19, A20,
                A21, A22, A23, A24, A25,
                A26, A27, A28, A29, A30,
                A31);
    }

    template<class newTP, class arg1, class arg2, class arg3, class arg4, class arg5,
    class arg6, class arg7, class arg8, class arg9, class arg10,
    class arg11, class arg12, class arg13, class arg14, class arg15,
    class arg16, class arg17, class arg18, class arg19, class arg20,
    class arg21, class arg22, class arg23, class arg24, class arg25,
    class arg26, class arg27, class arg28, class arg29, class arg30,
    class arg31, class arg32 >
    ThreadedProcedure *
    TPFactory(tpClosure * closure) {
        tpClosure32< arg1, arg2, arg3, arg4, arg5,
                arg6, arg7, arg8, arg9, arg10,
                arg11, arg12, arg13, arg14, arg15,
                arg16, arg17, arg18, arg19, arg20,
                arg21, arg22, arg23, arg24, arg25,
                arg26, arg27, arg28, arg29, arg30,
                arg31, arg32 > * args = static_cast<tpClosure32< arg1, arg2, arg3, arg4, arg5,
                arg6, arg7, arg8, arg9, arg10,
                arg11, arg12, arg13, arg14, arg15,
                arg16, arg17, arg18, arg19, arg20,
                arg21, arg22, arg23, arg24, arg25,
                arg26, arg27, arg28, arg29, arg30,
                arg31, arg32 >*> (closure);
        myThread.tempParent = args->parent;
        ThreadedProcedure * temp = new newTP(args->a1, args->a2, args->a3, args->a4, args->a5,
                args->a6, args->a7, args->a8, args->a9, args->a10,
                args->a11, args->a12, args->a13, args->a14, args->a15,
                args->a16, args->a17, args->a18, args->a19, args->a20,
                args->a21, args->a22, args->a23, args->a24, args->a25,
                args->a26, args->a27, args->a28, args->a29, args->a30,
                args->a31, args->a32);
        if (temp->decRef()) {
            delete temp;
            return NULL;
        }
        myThread.tempParent = NULL;
        return temp;
    }

    template<class newTP, class arg1, class arg2, class arg3, class arg4, class arg5,
    class arg6, class arg7, class arg8, class arg9, class arg10,
    class arg11, class arg12, class arg13, class arg14, class arg15,
    class arg16, class arg17, class arg18, class arg19, class arg20,
    class arg21, class arg22, class arg23, class arg24, class arg25,
    class arg26, class arg27, class arg28, class arg29, class arg30,
    class arg31, class arg32 >
    void
    invoke(ThreadedProcedure * parentTP, arg1 A1, arg2 A2, arg3 A3, arg4 A4, arg5 A5,
            arg6 A6, arg7 A7, arg8 A8, arg9 A9, arg10 A10,
            arg11 A11, arg12 A12, arg13 A13, arg14 A14, arg15 A15,
            arg16 A16, arg17 A17, arg18 A18, arg19 A19, arg20 A20,
            arg21 A21, arg22 A22, arg23 A23, arg24 A24, arg25 A25,
            arg26 A26, arg27 A27, arg28 A28, arg29 A29, arg30 A30,
            arg31 A31, arg32 A32) {
        parentTP->incRef();
        tpfactory funct = &TPFactory< newTP, arg1, arg2, arg3, arg4, arg5,
                arg6, arg7, arg8, arg9, arg10,
                arg11, arg12, arg13, arg14, arg15,
                arg16, arg17, arg18, arg19, arg20,
                arg21, arg22, arg23, arg24, arg25,
                arg26, arg27, arg28, arg29, arg30,
                arg31, arg32 >;
        tpClosure * closure = new tpClosure32< arg1, arg2, arg3, arg4, arg5,
                arg6, arg7, arg8, arg9, arg10,
                arg11, arg12, arg13, arg14, arg15,
                arg16, arg17, arg18, arg19, arg20,
                arg21, arg22, arg23, arg24, arg25,
                arg26, arg27, arg28, arg29, arg30,
                arg31, arg32 > (funct, parentTP, A1, A2, A3, A4, A5,
                A6, A7, A8, A9, A10,
                A11, A12, A13, A14, A15,
                A16, A17, A18, A19, A20,
                A21, A22, A23, A24, A25,
                A26, A27, A28, A29, A30,
                A31, A32);
        myThread.threadTPsched->pushTP(closure);
    }

    template<class newTP, class arg1, class arg2, class arg3, class arg4, class arg5,
    class arg6, class arg7, class arg8, class arg9, class arg10,
    class arg11, class arg12, class arg13, class arg14, class arg15,
    class arg16, class arg17, class arg18, class arg19, class arg20,
    class arg21, class arg22, class arg23, class arg24, class arg25,
    class arg26, class arg27, class arg28, class arg29, class arg30,
    class arg31, class arg32 >
    tpClosure *
    launch(arg1 A1, arg2 A2, arg3 A3, arg4 A4, arg5 A5,
            arg6 A6, arg7 A7, arg8 A8, arg9 A9, arg10 A10,
            arg11 A11, arg12 A12, arg13 A13, arg14 A14, arg15 A15,
            arg16 A16, arg17 A17, arg18 A18, arg19 A19, arg20 A20,
            arg21 A21, arg22 A22, arg23 A23, arg24 A24, arg25 A25,
            arg26 A26, arg27 A27, arg28 A28, arg29 A29, arg30 A30,
            arg31 A31, arg32 A32) {
        tpfactory funct = &TPFactory< newTP, arg1, arg2, arg3, arg4, arg5,
                arg6, arg7, arg8, arg9, arg10,
                arg11, arg12, arg13, arg14, arg15,
                arg16, arg17, arg18, arg19, arg20,
                arg21, arg22, arg23, arg24, arg25,
                arg26, arg27, arg28, arg29, arg30,
                arg31, arg32 >;
        return new tpClosure32< arg1, arg2, arg3, arg4, arg5,
                arg6, arg7, arg8, arg9, arg10,
                arg11, arg12, arg13, arg14, arg15,
                arg16, arg17, arg18, arg19, arg20,
                arg21, arg22, arg23, arg24, arg25,
                arg26, arg27, arg28, arg29, arg30,
                arg31, arg32 > (funct, NULL, A1, A2, A3, A4, A5,
                A6, A7, A8, A9, A10,
                A11, A12, A13, A14, A15,
                A16, A17, A18, A19, A20,
                A21, A22, A23, A24, A25,
                A26, A27, A28, A29, A30,
                A31, A32);
    }
}
#endif	/* invoke_H */

