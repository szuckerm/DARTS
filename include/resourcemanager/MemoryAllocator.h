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

#include "Allocator.h"
#include "MemoryResource.h"
#include "LimitSpecifier.h"


namespace darts
{

/*
	Class: MemoryAllocator

	An abstarct class to represent memory resource creation. It provides
	basic interfaces for allocating a given memory resource type.

	Inherits:
		<Allocator>
*/
class MemoryAllocator :
	public Allocator
{
	// Import all "allocate" methods from the base class,
	// otherwise they will be hidden by our new "allocate" method
	using Allocator::allocate;
public:
//Section: Public ->
	/*
		Constructor: MemoryAllocator

		Initializes the object.
	*/
	MemoryAllocator( void );

	/*
		Destructor: MemoryAllocator

		Destroys the object.
	*/
	~MemoryAllocator( void );

	/*
		Function: allocate

		Allocates a memory resource using the master resource
		given a size in bytes.

		Parameters:
			masterResource - resource to allocate from.
			sizeInBytes - allocate byte amount of space.

		Returns:

			An auto pointer to the memory resource of size allocated.

		See Also:

			<MemoryResource>
			<Allocator>
	*/
	virtual std::auto_ptr< Resource >
	allocate( MasterResource & masterResource, unsigned int sizeInBytes ) = 0;
};

} // namespace darts
