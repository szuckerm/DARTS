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
#include <stdint.h>
#include "SyncSlot.h"
#include "thread_safe_vector.h"

namespace darts
{
    //This is a forward declaration since there is a circular dependence
    class Codelet;

    class ThreadedProcedure 
    {
    protected:
	/*
	 * Variable: ref_
	 * ref_ says when the TP is done
	*/
        unsigned int ref_;
    public:
        ThreadedProcedure * parentTP_;
        ThreadedProcedure(void);
        //ThreadedProcedure(unsigned int num, ThreadedProcedure * parentTP);
        //Destructor
        virtual ~ThreadedProcedure();
        
        bool decRef (void);
        void incRef (void);
        bool zeroRef (void);
        bool checkParent(void);
        /*
        * Method: addCodelet
        * Adds a codelet to the TP's list
        */
        void add (Codelet * toAdd);
        
    };    
} // namespace darts
