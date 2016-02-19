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
#include "MasterResource.h"
#include "ResourceNeed.h"
#include "Specifier.h"
#include <memory>


namespace darts
{

class Resource;

/*
	Class: Allocator

	An abstract class to represent resource creation. It provides basic
	interfaces for allocating a given resource type.
*/
class Allocator
{
public:
//Section: Public ->

	/*
		Function: getTypeOfMyHandle

			Returns:

			The inheritance this allocator can handle
	*/
	virtual unsigned int
	getTypeOfMyHandle( void ) = 0;

	/*
		Function: allocate

		Allocates a given resource from a <MasterResource> given a
		specifier of information to determine how to allocate.

		Parameters:
			masterResource - resource to allocate from.
			specifier - how to handle the request.

		Returns:

			A auto pointer to the allocated resource.

		See Also:

			<ResourceNeed>
			<MemoryAllocator>

	*/
	virtual std::auto_ptr< Resource >
	allocate( MasterResource & masterResource,
	          const Specifier & specifier ) = 0;

	/*
		Function: allocate

		Allocates a given resource from a <MasterResource> given a
		specifier of information to determine how to allocate.

		Parameters:
			masterResource - resource to allocate from.
			specifier - how to handle the request.

		Returns:

			A auto pointer to the allocated resource.

		See Also:

			<ResourceNeed>
			<MemoryAllocator>

	*/
	virtual bool
	allocate( MasterResource & masterResource,
	          const Specifier & specifier, void * whereToAllocate ) = 0;

	/*
		Function: deallocate

		Remove a given resource given a reference.

		Parameters:
			resource - the resource to deallocate.

		Returns:

			True on success.

		See Also:

			<ResourceNeed>
			<MemoryAllocator>

	*/
	virtual bool
	deallocate( Resource & resource ) = 0;

	/*
		Function: handles

		Returns true if the allocator can handle allocating the type.

		Parameters:
			type - the type we wish to know if we can allocate.

		Returns:

			True on success.

	*/
	bool
	handles ( typing::ResourceType type );

};

} // namespace darts
