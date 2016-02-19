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
#include "codeletDefines.h"

namespace darts
{

    //This is a forward declaration since there is a circular dependence
    class ThreadedProcedure;    
    /*
		 * Class: Codelet
		 * The codelet class is a virutal class. Use this class to instantiate codelets
		 * and provide a funct method to execute.
		 * 
		 * See Also:
		 * <ThreadedProcedure>
		 * <ABCScheduler>
    */

    class Codelet
    {
    private:
				/*
				 * Variable: status_
				 * The status of the codelet TODO: Explicit?
				*/
        uint32_t status_;

    protected:
                                /*
				 * Variable: sync_
				 * The codelets counter
				*/
        SyncSlot sync_;
				/*
				 * Variable: myTP_
				 * Pointer to TP frame/context
				*/
        ThreadedProcedure * myTP_;

    public:
        /**
				 * Constructor: Codelet(uint32_t dep, uint32_t res, ThreadedProcedure * theTp, uint32_t stat);
				 * 
				 * Parameters:
				 *	dep - The dependence counter of the codelet
				 *	res - The value of the dependence counter if the codelet has to be reset
				 *	theTp - The TP the codelet belongs to
				 *	stat - Locality parameter (TODO: has to be explicited)
         */
        Codelet(uint32_t dep, uint32_t res, ThreadedProcedure * theTp=NULL, uint32_t stat=SHORTWAIT);
        Codelet(void);

        //Destructors
        virtual ~Codelet() {}

				/**
				 * Method: initCodelet
         * Implements a delayed Codelet init. We may need them for an array of codelets
				 * when the constructor is not called
				 * 
				 * Parameters:
				 *	dep - The dependence counter of the codelet
				 *	res - The value of the dependence counter if the codelet has to be reset
				 *	theTp - The TP the codelet belongs to
				 *	stat - Locality parameter (TODO: has to be explicited)
         */
        void initCodelet(uint32_t dep, uint32_t res, ThreadedProcedure * theTp, uint32_t stat);

				/**
				 * Method: decDep
         * Decrements the dependence counter of the codelet
         */
        virtual void decDep (void);
        
				/**
				 * Method: resetCodelet
         * Resets the codelet
         */
        void resetCodelet (void);

        /**
				 * Method: resetCodelet
         * Returns:
				 * Whether or not the codelet counter is 0. If it is, all the dependences have been satisfied and
				 * the codelet can now be fired
         */
        bool codeletReady (void);

        /**
				 * Method: setStatus
				 * Sets the status of the codelet (TODO: Has to be explained)
         */
        void setStatus (uint32_t stat);

        /**
				 * Method: getStatus
				 * Gets the status of the codelet (TODO: Has to be explained)
         */
        uint32_t getStatus (void) const;  

				/**
				 * Method: getTP
				 * Returns:
				 * The parent ThreadedProcedure pointer
         */
        ThreadedProcedure * getTP(void);
				
				/**
				 * Method: setTP
				 * Sets the parent ThreadedProcedure pointer
         */
        void setTP(ThreadedProcedure * aTP);
				
				/**
				 * Method: casStatus
				 * TODO description
         */
        bool casStatus(uint32_t oldval, uint32_t newval);

				/**
				 * Method: Do
				 * Wrapper to push codelets to the parent scheduler
         */
        void add(Codelet * aCodelet);
        void add() { add(this); }
				
        /**
				 * Method: getCounter
				 * Returns:
				 * The dependence counter of the codelet
         */
        uint32_t getCounter(void) const;
        
        SyncSlot * getSyncSlot(void);
        
				/**
				 * Method: funct
				 * This is the code of the codelet to be executed.
         */
        virtual void fire(void) = 0;
                 
        #ifdef TRACE
        void * returnFunct(void);
        #endif
    };    
} // namespace darts
