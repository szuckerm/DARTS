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

#ifndef _MSC_VER

	#include <pthread.h>

#else

	#include <windows.h>

#endif


namespace darts
{
/*
	Class: Lock

	A class used to provide generic locking objects works for windows
	and any OS with pthreads.
*/
#ifndef _MSC_VER
class Lock
{
private:
		/* Locking object with pthreads. */
		pthread_mutex_t mutex_;

public:
	/* Creates the lock for use. */
	Lock( void ) { pthread_mutex_init ( &mutex_, NULL ); }

	/* Destroys the lock. */
	~Lock( void ) { pthread_mutex_destroy ( &mutex_ ); }

	/* Waits until the lock is secured. */
	void lock ( void ) { pthread_mutex_lock ( &mutex_ ); }

	/*
			Tries to lock otherwise returns.
			Returns: True if the lock was secured.
	*/
    bool trylock ( void ) { return 0 == pthread_mutex_trylock ( &mutex_ ); }

	/* Yields the lock for others to use. */
    void unlock ( void ) { pthread_mutex_unlock ( &mutex_ ); }
};

#else

class Lock
{
private:
		/* Locking object on windows. */
		HANDLE mutex_;

public:
	/* Creates the lock for use. */
	Lock( void ) { mutex_ = CreateMutex( NULL, FALSE, NULL ); } 

	/* Destroys the lock. */
	~Lock( void ) { CloseHandle( mutex_ ); }

	/* Waits until the lock is secured. */
	void lock ( void ) { WaitForSingleObject( mutex_, INFINITE ); }

	/*
			Tries to lock (waits for 1 millisecond) otherwise returns.
			Returns: True if the lock was secured.
	*/
    bool trylock ( void ) { return WAIT_OBJECT_0 == WaitForSingleObject( mutex_, 1 ); }

	/* Yields the lock for others to use. */
    void unlock ( void ) { ReleaseMutex( mutex_ ); }
};

#endif


} // namespace darts
