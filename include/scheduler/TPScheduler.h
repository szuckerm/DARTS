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
#include "Scheduler.h"
#include "tpClosure.h"
#include "ThreadedProcedure.h"
#include <vector>
#include <stdlib.h>
#include "dartsPool.h"

#ifdef TRACE
#include "getClock.h"
#endif

namespace darts
{
    enum TPSCHED {TPPUSHFULL      = 0, 
                  TPROUNDROBIN    = 1, 
                  TPSTATIC        = 2,
                  TPDYNAMIC       = 3,
                  TPWORKPUSH      = 4};


    class TPScheduler : public Scheduler
    {
    private:
        size_t numberOfPeers;
        TPScheduler** peers_;
        std::vector<Scheduler*> children_;
        
    protected:
        dartsPool<tpClosure*> ready_;
        dartsPool<Codelet*> codelets_;

    public:
        
        TPScheduler(void):
        numberOfPeers(0),
        peers_(NULL)
        {
            
        }
        
	~TPScheduler(void){}

        Scheduler *
        getSubScheduler(size_t pos) const
        {
            if(children_.size()>pos)
                return children_.at(pos);
            return 0;
        }

        void
        setSubScheduler(Scheduler * aSub)
        {
            children_.push_back(aSub);
        }

        size_t 
        getNumSub(void) const
        {
            return children_.size();
        }
        
        void addPeer(TPScheduler * toAdd, size_t pos)
        {
            peers_[pos] = toAdd;
        }

        void
        setNumPeers(size_t numPeers)
        {
            numberOfPeers = numPeers;
            if(!peers_)
                peers_ = new TPScheduler*[numPeers];
        }
                
        size_t 
        getNumPeers(void) const
        {
            return numberOfPeers;
        }

        TPScheduler * 
        getPeer(size_t pos) const
        {
            if(pos<numberOfPeers)
                return peers_[pos];
            return 0;
        }
        
        tpClosure *
        steal(void)
        {
            if(numberOfPeers)
            {
                uint64_t random = rand() % numberOfPeers;
                if(random!=getID())
                {
                    return peers_[random]->popTP();
                }
            }
            return NULL;
        }  
        
        virtual void policy(void) = 0;
                
        virtual bool 
        pushTP(tpClosure * TPtoPush)
        {
            return ready_.push(TPtoPush);
        }
        
        virtual tpClosure * 
        popTP(void)
        {
            return ready_.pop();
        }
        
        virtual bool 
        pushCodelet(Codelet * CodeletToPush)
        {
            return codelets_.push(CodeletToPush);
        }
        
        virtual Codelet * 
        popCodelet(void)
        {
            return codelets_.pop();
        }
        
        static TPScheduler * create(unsigned int type);
    };
}

