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


/*The all methods are separated because there is a circular dependency
 between codelet and threaded procedure classes*/

//Don't Mess with the order of these includes
#include "codeletDefines.h"
#include "SyncSlot.h"
#include "Codelet.h"
#include "ThreadedProcedure.h"
#include "threadlocal.h"
#include "MSchedPolicy.h"
#include <cassert>

namespace darts
{
    
    Codelet::Codelet(uint32_t dep, uint32_t res, ThreadedProcedure * theTp, uint32_t stat):
    status_(stat),
    sync_(dep,res),
    myTP_(theTp) 
    {
    }

    Codelet::Codelet(void):
    status_(NIL),
    sync_(0U,0U),
    myTP_(0) { }

    void
    Codelet::initCodelet(uint32_t dep, uint32_t res, ThreadedProcedure * theTp, uint32_t stat)
    {
        sync_.initSyncSlot(dep,res);
        status_ = stat ;
        myTP_ = theTp;
    }

    void
    Codelet::decDep(void)
    {
        if(sync_.decCounter())
        {
            if(myTP_)
                myTP_->incRef();
            if(myThread.threadMCsched)
            {
                if(myThread.threadMCsched->getLocal())
                {
                        if(myThread.threadMCsched->pushLocal(this))
                                return;
                }
            }
            myThread.threadTPsched->pushCodelet(this);
        }
    }

    void 
    Codelet::resetCodelet(void)
    {
        sync_.resetCounter();
        //The check is just in case we are reseting the final codelet
        //if(sync_.ready())
        //{
            //myTP_->incRef();
           //myThread.threadTPsched->placeCodelet(this);
        //}
    }

    bool 
    Codelet::codeletReady(void)
    {
        return sync_.ready();
    }

    void 
    Codelet::setStatus(uint32_t stat)
    {
        status_ = stat;
    }

    uint32_t Codelet::getStatus(void) const{
        return status_;
    }
    
    bool
    Codelet::casStatus(uint32_t oldval, uint32_t newval )
    {
        return Atomics::boolcompareAndSwap(status_,oldval,newval);
    }

    ThreadedProcedure * 
    Codelet::getTP(void)
    {
        return myTP_;
    }

    void 
    Codelet::setTP(ThreadedProcedure * aTP)
    {
        myTP_ = aTP;
    }

    void
    Codelet::add(Codelet * aCodelet)
    {
        if(aCodelet->codeletReady())
        {
            myTP_->incRef();
            myThread.threadTPsched->pushCodelet(aCodelet);
        }
    }

    uint32_t 
    Codelet::getCounter(void) const{
        return sync_.getCounter();
    }
    
    SyncSlot *
    Codelet::getSyncSlot(void)
    {
        return &sync_;
    }

    
    #ifdef TRACE
    void *
    Codelet::returnFunct(void)
    {
        void (Codelet::*f)(void) = &Codelet::fire; 
        return (void*) f;
    }
    #endif
    
} // namespace darts
