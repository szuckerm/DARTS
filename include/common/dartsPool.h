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

#ifdef TBB
#include <tbb/concurrent_queue.h>
#else
#include "thread_safe_vector.h"
#endif

template <class T>
class dartsPool
{
#ifdef TBB
    private:
        tbb::concurrent_queue<T> pool;
#else
    private:
        thread_safe::deque<T> pool;
#endif
    public:
        T pop(void);

        bool push(T input);
        
        bool pushHead(T input);
        
        bool pushTail(T input);
        
        T popHead(void);
        
        T popTail(void);
        
        bool empty(void);

};

#ifdef TBB
template <class T>
T dartsPool<T>::pop(void)
{
    T temp;
    if (pool.try_pop(temp))
        return temp;
    else
        return 0;
}

template <class T>
bool dartsPool<T>::push(T input)
{
    pool.push(input);
    return true;
}

template <class T>
bool dartsPool<T>::pushHead(T input)
{
    pool.push(input);
    return true;
}

template <class T>
bool dartsPool<T>::pushTail(T input)
{
    pool.push(input);
    return true;
}

template <class T>
T dartsPool<T>::popHead(void)
{
    T temp;
    if (pool.try_pop(temp))
        return temp;
    else
        return 0;
}

template <class T>
T dartsPool<T>::popTail(void)
{
    T temp;
    if (pool.try_pop(temp))
        return temp;
    else
        return 0;
}

template <class T>
bool dartsPool<T>::empty(void)
{
    return pool.empty();    
}

#else

template <class T>
T dartsPool<T>::pop(void)
{
    return pool.popBack();
}

template <class T>
bool dartsPool<T>::push(T input)
{
    pool.push_back(input);
    return true;
}

template <class T>
bool dartsPool<T>::pushHead(T input)
{
    pool.push_front(input);            
    return true;
}

template <class T>
bool dartsPool<T>::pushTail(T input)
{
    pool.push_back(input);            
    return true;
}

template <class T>
T dartsPool<T>::popHead(void)
{
    return pool.popFront();
}

template <class T>
T dartsPool<T>::popTail(void)
{
    return pool.popBack();
}

template <class T>
bool dartsPool<T>::empty(void)
{
    return pool.empty();    
}

#endif  
