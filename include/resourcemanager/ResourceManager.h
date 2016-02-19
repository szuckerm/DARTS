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

#include <vector>
#include <list>
#include "Resource.h"
#include "NullResource.h"
#include "ResourceNeed.h"
#include "Allocator.h"
#include "InformationService.h"


namespace darts
{

/*
	Class: ResourceManager

	Handles all allocation and deallocation requests for resources.
	Does individual requests and grouped requests.
*/
class ResourceManager
{

private:
//Section: Private->
	/*
		Variable: allocators__

		A list of resource allocators to handle requests.
	*/
	std::list< Allocator * > allocators__;

	/*
		Variable: informationService__

		Reference to the information service.
	*/
	InformationService & informationService__;

	/*
		Function: handleAllocateRequest

		Handles allocation request internally.

		Parameters:

			masterResource - <MasterResource> to allocate from.
			specifier - specification of this request.

		Returns:

			A unique pointer to the resource on success otherwise
			a <NullResource>.
	*/
	std::auto_ptr< Resource >
	handleAllocateRequest( MasterResource & masterResource,
	                       const Specifier & specifier );

	/*
		Function: handleAllocateRequest

		Handles allocation request internally.

		Parameters:

			masterResource - <MasterResource> to allocate from.
			specifier - specification of this request.

		Returns:

			A unique pointer to the resource on success otherwise
			a <NullResource>.
	*/
	bool
	handleAllocateRequest( MasterResource & masterResource,
	                       const Specifier & specifier, void * whereToAllocate );

	/*
		Function: handleDeallocateRequest

		Handles deallocation request internally.

		Parameters:

			resource - the resource to deallocate.

		Returns:

			True if deallocation was succesful; false otherwise.
	*/
	bool handleDeallocateRequest( Resource & resource );

	/*
		Function: queryAllocators

		Finds a list of allocators to handle the given resource.
		These allocators can create its type.

		Parameters:

			type - the resource type to check for available allocators.

		Returns:

			An array of <Allocators> & to allocate this resource.
	*/
	std::vector< Allocator * >
	queryAllocators( typing::ResourceType type );

public:
//Section: Public->
	/*
		Constructor: ResourceManager

		Initializes the object.
	*/
	ResourceManager ( InformationService & informationServiceToSet );
  /*
		Destructor: ResourceManager

		Destroys the object.
	*/
	~ResourceManager ( void );

	/*
		Function: allocate

		Given a resource and its array of needs, the allocate function
		will attempt to create a resource to meet that need.

		Parameters:

			resourcePlusNeeds - a resource type to allocate and
			                         specifier with a list of needs.

		Returns:

			A auto pointer to the resource on success otherwise
			a <NullResource>.
	*/

	std::auto_ptr< Resource >
	allocate( struct ResourcePlusItsNeeds resourcePlusNeeds );

	bool
	allocateLazy( struct ResourcePlusItsNeeds resourcePlusNeeds );

	template < class T >
	std::auto_ptr< T >
	allocateLazy( struct ResourcePlusItsNeeds resourcePlusNeeds )
	{
		std::auto_ptr< Resource > resource = allocate( resourcePlusNeeds );

		T * ptr = static_cast< T* >( resource.get() );

		resource.release();

		return std::auto_ptr< T >  ( ptr ); 
	}

	/*
		Function: coallocate

		Given an array of resources, specifiers, and their needs,
		the coallocate function will attempt to create the list
		of resource to meet those needs.
		This is all or nothing.

		Parameters:

			resourcesPlusNeeds - a vector of resources to allocate
			                                    with a list of needs.

		Returns:

			A vector of pointers to their resources on success
			otherwise a empty vector.
	*/
	std::vector < Resource * >
	coallocate( std::vector< struct ResourcePlusItsNeeds >
	            resourcesPlusNeeds );

	bool
	coallocateLazy( std::vector< struct ResourcePlusItsNeeds >
	            resourcesPlusNeeds );

	/*
		Function: deallocate

		Given an array of resources, the deallocate function
		will attempt to free those resources.

		Parameters:

			resources - an array of resources to deallocate.

		Returns:

			The true if the resource was deallocated; false otherwise.
	*/
	bool
	deallocate ( std::vector< Resource * > & resources );
        
        /*
		Function: deallocate

		Given an array of resources, the deallocate function
		will attempt to free those resources.

		Parameters:

			resources - a single resource to deallocate.

		Returns:

			The true if the resource was deallocated; false otherwise.
	*/
	bool
	deallocate ( Resource & resource );

	/*
		Function: addAllocator

		Adds an allocator to the resource manager

		Parameters:

			allocatorToAdd - adds the allocator to the list of allocators.
	*/
        
	void
	addAllocator( Allocator & allocatorToAdd );


	/*
		Function: query

		Not sure the use of this yet...

	*/
	bool
	query ( std::vector< typing::ResourceType > types );

};

} // namespace darts
