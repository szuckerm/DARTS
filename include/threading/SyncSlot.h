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
//#include <cstdint>
#include <iostream>
#include <stdint.h>
#include "Atomics.h"


namespace darts
{

  /*
	 * Class: SyncSlot
   * This class contains to ints which are used as a counter and reset. This is to allow
   * a codelet to run.
	 * 
	 * See Also:
	 * <Atomics>
	*/
  
  class SyncSlot
  {
  private:
    unsigned int counter_;
    unsigned int reset_;
  public:
    SyncSlot(uint32_t dep, uint32_t res):
    counter_(dep),
    reset_(res) { }
    
    void
    initSyncSlot(uint32_t dep, uint32_t res)
    {
        counter_ = dep;
        reset_ = res;
    }
    
    //dec the counter
    bool 
    decCounter(void)
    {
        return (1==Atomics::fetchSub(counter_, 1U));
    }
    
    //inc the counter
    void
    incCounter(void)
    {
      Atomics::fetchAdd(counter_, 1U);
      Atomics::fetchAdd(reset_, 1U);
    }
    
    //resets the counter
    void 
    resetCounter(void)
    {
        counter_ = reset_;
        //return Atomics::boolcompareAndSwap(counter_,0U,reset_);
    }
    
    uint32_t getCounter(void) const{
        return counter_;
    }
    
    //returns the if the counter has reached zero
    bool ready(void) const{
        return (counter_ == 0);
    }  
  };

} // namespace darts