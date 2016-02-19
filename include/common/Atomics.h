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
#include <iostream>
#ifndef _MSC_VER

#else

	#include <windows.h>

#endif

namespace darts
{

/*
	Class: Lock

	A class used to provide architecture independent atomic instructions.
	These are not cheap... Usually they lock the bus...
*/
class Atomics
{
public:
//Section: Public ->

	/*
			Function: fetchAdd

			Atomically fetches a value then adds to it.

			Parameters:
				updateMe - value to add to
				valueToAdd - amount to add to updateMe
	*/

	template < class T > static T fetchAdd ( volatile T & updateMe, T valueToAdd )
	{

		T returnValue;

		#ifdef __GNUC__

			returnValue = __sync_fetch_and_add( &updateMe, valueToAdd );

		#elif _MSC_VER
				
			returnValue = InterlockedExchangeAdd(  &updateMe, 
			                                       valueToAdd );

		#endif

				return returnValue;
	}

	/*
			Function: fetchSub

			Atomically fetches a value then subtracts to it.

			Parameters:
				updateMe - value to subtract to
				valueToAdd - amount to subtract to updateMe
	*/

	template < class T > static T fetchSub ( volatile T & updateMe, T valueToAdd )
	{

		T returnValue;

		#ifdef __GNUC__

			returnValue = __sync_fetch_and_sub( &updateMe, valueToAdd );

		#elif _MSC_VER
				
			returnValue = InterlockedExchangeSubtract(  &updateMe, 
			                                            valueToAdd );

		#endif

				return returnValue;
	}

	template < class T > static T compareAndSwap ( volatile T & destination, T oldVal, T newval )
	{

		T returnValue;

		#ifdef __GNUC__

			returnValue = __sync_val_compare_and_swap( &destination, 
			                                        oldVal, newval);

		#elif _MSC_VER
				
			returnValue = InterlockedCompareExchange(  &destination, 
			                                       newval, oldVal );

		#endif

				return returnValue;
	}
        
  template < class T > static bool boolcompareAndSwap ( volatile T & destination, T oldVal, T newval )
	{

		#ifdef __GNUC__

			return __sync_bool_compare_and_swap( &destination, 
			                                        oldVal, newval);

		#elif _MSC_VER
				
			returnValue = InterlockedCompareExchange(  &destination, 
			                                       newval, oldVal );
                        return(returnValue==comparison)

		#endif
	}
  
  template < class T > static T swap ( volatile T & destination, T newval )
	{

		T returnValue;

		#ifdef __GNUC__

			returnValue = __sync_lock_test_and_set( &destination, 
			                                        newval);

		#elif _MSC_VER
				
			returnValue = InterlockedExchange(  destination, 
			                                       newval, oldVal );

		#endif

				return returnValue;
	}
        
};

} // namespace darts
