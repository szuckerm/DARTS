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

//keyword: allocator

#include <vector>
#include "Allocator.h"
#include "Specifier.h"


namespace darts
{

/*
	Class: NullAllocator

	A class to represent null resource creation. It provides basic
	interfaces for allocating a given resource type.
*/
class NullAllocator: public Allocator
{
public:
//Section: Public ->

	/*
		Function: getTypeOfMyHandle

		Returns:

			The type inheritance this can allocate.
	*/
	unsigned int
	getTypeOfMyHandle( void )
	{
		return typing::NullResource;
	}

	/*
		Function: allocate

		Returns an empty pointer.

		Parameters:

			masterResource - resource to allocate from.
			specifier - how to handle the request.

		Returns:

			Null pointer.

	*/
	std::auto_ptr< Resource >
	allocate( MasterResource & masterResource, const Specifier & specifier )
	{
		// Prevent compiler warning about unused arguments
		(void) masterResource;
		(void) specifier;

		std::auto_ptr< Resource > dummy;
		return dummy;
	}

	/*
		Function: allocate

		Returns false always.

		Parameters:

			masterResource - resource to allocate from.
			specifier - how to handle the request.
			whereToAllocate - allocates resource there...

		Returns:

			false.

	*/
	bool
	allocate( MasterResource & masterResource, const Specifier & specifier,
	          void * whereToAllocate )
	{
		// Prevent compiler warning about unused arguments
		(void) masterResource;
		(void) specifier;
		(void) whereToAllocate;

		return false;
	}

	/*
		Function: deallocate

		Does nothing.

		Parameters:
			resource - the resource to deallocate.

		Returns:

			True always.
	*/
	bool
	deallocate( Resource & resource )
	{
		// Prevent compiler warning about unused arguments
		(void) resource;

		return true;
	}

};

} // namespace darts
