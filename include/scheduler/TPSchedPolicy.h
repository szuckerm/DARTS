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
#include "TPScheduler.h"
#include "Codelet.h"
#include <stdlib.h>


namespace darts
{
    static const unsigned outstanding = 2;

    class TPRoundRobin : public TPScheduler
    {
    private:
        size_t whichSub_;

    public:

        TPRoundRobin(void) :
        whichSub_(0)
        {
        }

        void policy(void);

        size_t
        getSubIndexInc(void)
        {
            size_t temp = whichSub_;
            whichSub_ = (whichSub_ + 1) % getNumSub();
            return temp;
        }

        size_t
        getSubIndex(void)
        {
            return whichSub_;
        }

        void
        setSubIndex(size_t index)
        {
            whichSub_ = index;
        }
    };
    
    class TPPushFull : public TPScheduler
    {
    private:
        size_t whichSub_;

    public:

        TPPushFull(void) :
        whichSub_(0)
        {
        }

        void policy(void);

        size_t
        getSubIndexInc(void)
        {
            size_t temp = whichSub_;
            whichSub_ = (whichSub_ + 1) % getNumSub();
            return temp;
        }

        size_t
        getSubIndex(void)
        {
            return whichSub_;
        }

        void
        setSubIndex(size_t index)
        {
            whichSub_ = index;
        }
    };
   
    class TPStatic : public TPScheduler
    {
    public:
        void policy(void);
        
        bool
        pushCodelet(Codelet * CodeletToPush);
    };
    
    class TPDynamic : public TPScheduler
    {    
    public:
        void policy(void);
    };
    
    class TPWorkPush : public TPScheduler
    {
    private:
        size_t whichMC_;
        size_t whichTP_;
    public:
        TPWorkPush(void):
        whichMC_(0),
        whichTP_(0)
        { 
        
        }
        
        void policy(void);
        
        size_t
        getSubIndexInc(void)
        {
            size_t temp = whichMC_;
            whichMC_ = (whichMC_ + 1) % getNumSub();
            return temp;
        }
        
        bool
        takeTP(tpClosure * aTP)
        {
            return ready_.push(aTP);
        }
        
        virtual bool 
        pushTP(tpClosure * TPtoPush)
        {
            size_t numPeers = getNumPeers();
            if(numPeers)
            {
                if(whichTP_ % numPeers == getID())
                    whichTP_++;
                bool ret = static_cast<TPWorkPush*>(getPeer(whichTP_ % numPeers))->takeTP(TPtoPush);
                whichTP_++;
                return ret;
            }
            return ready_.push(TPtoPush);
        }
                
    };    
}
