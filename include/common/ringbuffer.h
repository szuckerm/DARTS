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


#ifndef RINGBUFFER_H
#define	RINGBUFFER_H
#include <cstdio>
#include "Atomics.h"
#include "SyncSlot.h"

namespace darts
{
    template <class T, size_t num>
    class ringBuffer
    {
        private:
            unsigned int produceCount;
            char pad1[64-sizeof(int)];
            unsigned int consumeCount;
            char pad2[64-sizeof(int)];
            T buffer_[num];
        public:
            ringBuffer(void):
            produceCount(0),
            consumeCount(0) { }

            bool push(T toAdd )
            {
                if(produceCount - consumeCount == num)
                    return false;
                buffer_[produceCount & (num -1)] = toAdd;
                //produceCount++;
                Atomics::fetchAdd(produceCount, 1U);
                return true;
            }

            T pull(void)
            {
                if(produceCount - consumeCount == 0)
                    return 0;
                T temp = buffer_[consumeCount & (num -1)];
                //consumeCount++;
                Atomics::fetchAdd(consumeCount, 1U);
                return temp;
            }
    };
}

#endif	/* RINGBUFFER_H */

