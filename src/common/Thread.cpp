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


#include "Thread.h"
#include <iostream>

using namespace darts;

Thread::Thread(void):
function_(0),
argument_(0) 
{ 
    #ifndef _MSC_VER
      pthread_attr_init(&attr);
    #endif
}

Thread::Thread( void * (* functionToSet) (void *), void * argToSet):
function_(functionToSet),
argument_(argToSet)
{
    #ifndef _MSC_VER
      pthread_attr_init(&attr);
      pthread_attr_setscope(&attr, PTHREAD_SCOPE_SYSTEM);
    #endif
}

Thread::Thread ( void *(*functionToSet) (void*)):
function_(functionToSet)
{
    #ifndef _MSC_VER
      pthread_attr_init (&attr);
      pthread_attr_setscope(&attr, PTHREAD_SCOPE_SYSTEM);
    #endif
}

bool Thread::run()
{
	#ifndef _MSC_VER

		int rc = pthread_create( &thread_, &attr, function_, argument_ );
    //int rc = pthread_create( &thread_, NULL, function_, argument_ );
		if( rc != 0 )
			return false;

		return true;
	#else

		LPVOID argument = static_cast < LPVOID >( argument_ );

		LPTHREAD_START_ROUTINE function =
		reinterpret_cast < LPTHREAD_START_ROUTINE > ( function_ );

		threadHandle_ = CreateThread( 0, 0, function,
		                              argument, 0, &thread_ );

		if( threadHandle_ == 0 )
			return false;

		return true;

	#endif
}

bool Thread::join()
{
	#ifndef _MSC_VER

		//FIXME
		pthread_join( thread_, 0 );

		return true;

	#else

		DWORD result;

		result = WaitForSingleObject( threadHandle_, INFINITE );

		if( result == WAIT_OBJECT_0 )
			return true;

		return false;

	#endif
}

void Thread::resetArgument( void * resetToMe )
{
	argument_ = resetToMe;
}

void Thread::resetFunction( void * (* functionToSet) (void *) )
{
	function_ = functionToSet;
}

bool Thread::setAffinity( int cpu )
{
#ifndef _MSC_VER
    cpu_set_t cpuset;
    CPU_ZERO(&cpuset);
    CPU_SET(cpu, & cpuset);
    return ( pthread_attr_setaffinity_np(&attr,sizeof(cpuset),&cpuset) );
#endif
    return false;
}

Thread::~Thread(void)
{
#ifndef _MSC_VER
    pthread_attr_destroy(&attr);
#endif  
}

