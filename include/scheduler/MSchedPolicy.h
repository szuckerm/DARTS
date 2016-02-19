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
#include "Codelet.h"
#include "MicroScheduler.h"
#include "ringbuffer.h"
#include "dartsPool.h"

#define THRESHOLD 4

namespace darts
{
    class MicroStandard : public MScheduler
    {
    private:
        ringBuffer<Codelet*, THRESHOLD> buff;
    public:
        bool 
        pushCodelet(Codelet * codeletToPush)
        {
            return buff.push(codeletToPush);
        }
        
        bool
        pushLocal(Codelet *)
        {
            return false;
        }
        
        Codelet * 
        popCodelet(void)
        {
            return buff.pull();
        }
        
        virtual void policy(void);
    };
       
    class MicroStatic : public MScheduler
    {
    private:
        dartsPool<Codelet*> buff;
    public:
        
        bool
        pushCodelet(Codelet * codeletToPush)
        {
            return buff.push(codeletToPush);
        }
        
        bool
        pushLocal(Codelet * codeletToPush)
        {
            return buff.push(codeletToPush);
        }
        
        Codelet *
        popCodelet(void)
        {
            return buff.pop();
        }
        
        virtual void policy(void);
    };
    
    class MicroDynamic : public MScheduler
    {
    public:
        bool 
        pushCodelet(Codelet *)
        {
            return false;
        }
        
        bool
        pushLocal(Codelet *)
        {
            return false;
        }
        
        virtual void policy(void);
    };
    
    class MicroSteal : public MScheduler
    {
    private:
        dartsPool<Codelet*> buff;
    public:
        
        MicroSteal(void)
        { local_ = true; }
        
        bool 
        pushCodelet(Codelet *)
        {
            return false;
        }
        
        Codelet * 
        popCodelet(void)
        {
            return buff.pop();
        }
        
        bool pushLocal(Codelet * codeletToPush)
        {
            return buff.push(codeletToPush);
        }
        
        Codelet *
        stealCodelet(void)
        {
            TPScheduler * parent = getParentScheduler();
            size_t numberOfPeers = parent->getNumSub();
            uint64_t random = rand() % (numberOfPeers + 1);
            if(random!=getID())
            {
                if(random==numberOfPeers)
                {
                    return parent->popCodelet();
                }
                else
                {
                    MicroSteal * victim = static_cast<MicroSteal*>(parent->getSubScheduler(random));
                    return victim->popCodelet();
                }
            }
            return NULL;
        }
        virtual void policy(void);
    };
}
