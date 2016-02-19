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

#include <stdint.h> // using C++98, so including '.h' version

#ifdef TBB
#include <tbb/concurrent_queue.h>
#else
#include "thread_safe_deque.h"
#endif

#include "Affinity.h"

#ifdef TRACE
#include <vector>
#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#endif

namespace darts
{

#ifdef TRACE

    struct record
    {
        uint64_t cycle;
        void * funct;

        record(void) :
        cycle(0), funct(0)
        {
        }

        record(uint64_t theCycle, void * fn) :
        cycle(theCycle), funct(fn)
        {
        }
    };
#endif
    
    class Scheduler
    {
    private:
        uint64_t id_;
        volatile bool alive_;
	ThreadAffinity * affin_;
	
#ifdef TRACE
        std::vector<record> schedTrace_;
#endif
    public:

        Scheduler(void) :
        id_(0),
        alive_(true),
	affin_(0)
        {

        }

        virtual ~Scheduler()
        {
#ifdef TRACE
            printRecord();
#endif
        }
        
        void
        setAffinity(ThreadAffinity * affin)
	{
	  affin_ = affin;
	}
	
	ThreadAffinity *
	getAffinity(void)
	{
	  return affin_;
	}
        
        void
        setID(uint64_t theID)
        {
            id_ = theID;
        }

        uint64_t
        getID(void)
        {
            return id_;
        }

        void
        kill(void)
        {
            alive_ = false;
        }

        void
        resurrect(void)
        {
            alive_ = true;
        }

        bool
        alive(void)
        {
            return alive_;
        }
        
        virtual void policy(void) = 0;

#ifdef TRACE       

        void
        addRecord(uint64_t theCycle, void * fn)
        {
            schedTrace_.push_back(record(theCycle, fn));
        }

        void
        printRecord(void)
        {
            std::ofstream myfile;
            std::stringstream ss;
            ss << "thread" << id_ << ".txt";
            std::string s = ss.str();
            myfile.open(s.c_str());
            if (!myfile.is_open())
            {
                std::cout << "Could not open " << s.c_str() << std::endl;
            } else
            {
                std::vector<record>::iterator it;
                for (it = schedTrace_.begin(); it < schedTrace_.end(); ++it)
                {
                    myfile << (*it).cycle << " " << (*it).funct << "\n";
                }
                myfile.close();
            }
        }

#endif
        
    };    
}
