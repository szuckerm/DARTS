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

#include "Resource.h"
#include "NullResource.h"
#include "ResourceNeed.h"
#include "MemoryResource.h"
#include "HeapResource.h"
#include "MemoryAllocator.h"


namespace darts
{

/*
	Class: HeapAllocator

	A class to represent heap memory resource creation. It provides
	basic interfaces for allocating a heap resource type.

	Inherits:
		<MemoryAllocator>
*/
class HeapAllocator :
	public MemoryAllocator
{
private:

public:
//Section: Public ->

	/*
		Constructor: HeapAllocator

		Initializes the object.
	*/
	HeapAllocator( void );

	/*
		Destructor: HeapAllocator

		Destroys the object.
	*/
	~HeapAllocator( void );

	/*
		Function: getTypeOfMyHandle

		This allocator can handle memory types.

			Returns:

			The heap memory resource inheritance.
	*/
	unsigned int
	getTypeOfMyHandle( void );

	/*
		Function: allocate

		Allocates a memory resource given a place to store and
		quantity in bytes defined by the reference.

		Parameters:
			masterResource - resource to allocate from.
			specifier - a <LimitSpecifier> to set the size.

		Returns:

			A auto pointer to a memory resource on success.
			Otherwise, a NullResource is returned.

		See Also:

			<MemoryResourceNeed>
			<Allocator>

	*/
	std::auto_ptr< Resource >
	allocate( MasterResource & masterResource, const Specifier & specifier );

	/*
		Function: allocate

		Allocates a memory resource given a place to store and
		quantity in bytes defined by the reference.

		Parameters:
			masterResource - resource to allocate from.
			specifier - a <LimitSpecifier> to set the size.

		Returns:

			A auto pointer to a memory resource on success.
			Otherwise, a NullResource is returned.

		See Also:

			<MemoryResourceNeed>
			<Allocator>

	*/
	bool
	allocate( MasterResource & masterResource, const Specifier & specifier,
	          void * whereToAllocate );

	/*
		Function: deallocate

		Remove a heap resource given a reference.

		Parameters:
			resource - the heap resource to deallocate.

		Returns:

			True on success.
	*/
	bool
	deallocate( Resource & resource );

	/*
		Function: allocate

		Allocates a memory resource on the heap using the master resource
		given a size in bytes.

		Parameters:
			masterResource - resource to allocate from.
			sizeInBytes - allocate byte amount of space.

		Returns:

			Memory resource of size allocated.

		See Also:

			<MemoryResourceNeed>
			<Allocator>

	*/
	std::auto_ptr< Resource >
	allocate( MasterResource & masterResource, unsigned int sizeInBytes );
};

} // namespace darts
