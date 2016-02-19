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

#include <map>
#include <vector>
#include "Defines.h"
#include "Typing.h"
#include "MasterResource.h"
#include "ResourceNeed.h"
#include "Allocator.h"


namespace darts
{

//class Allocator;

/*
	Class: Resource

	An abstract class used to represent resources. It provides basic
	interfaces for reading a writing resources. All resources are exclusive
	by default. Resources are polymorphic.

	The resource class also provides fast inheritance
	relationship/typing checking via prime numbers.
*/
class Resource
{
private:
//Section: Private->
	/*
		Variable: id
			Identifies the resource.
	*/
	IdT id__;
	/*	Variable: owner
			Owner of the resource.
	*/
	IdT owner__;

	/*
		Variable: ourMaster

		A pointer to the master resource we are based on.
	*/
	MasterResource * ourMaster__;

	/*
		Variable: ourAllocator

		A pointer to our allocator.
	*/
	Allocator * ourAllocator__;

public:
//Section: Public ->

	/*
		Constructor: Resource

		Initializes the object.

		Parameters:

			masterToSet - resource we allocated from.
			allocatorToSet - which allocator created us.
	*/
	Resource( MasterResource & masterToSet, Allocator & allocatorToSet );

	Resource();

	/*
		Variable: classType
			Type of this class.
	*/
	const static typing::ResourceType classType = typing::Resource;
	/*
		Variable: classInherit
			Inheritance information for this class.
	*/
	const static unsigned int classInherit = classType;

	/*
		Function: getType

		Returns the type of this instantiation.

		Returns:

			The <typing::ResourceType> of this instantation.

		See Also:

			<typing>
	*/
	virtual typing::ResourceType
	getType( void ) = 0;

	/*
		Function: getInherit

		Returns the inheritance of this instantiation.

		Returns:

			The inheritance value of this instantiation.

	*/
	virtual unsigned int
	getInherit( void ) = 0;

	/*
		Function: instanceOf

		Returns true if this instantiation is the child of the type given.

		Returns:

			A bool to indicate inheritance.

		See Also:

			<typing>
	*/
	bool
	instanceOf ( typing::ResourceType typeCheck );

	/*
		Function: isType

		Returns true if this instantiation is the type given.

		Returns:

			True if it is the indicated type.
	*/
	bool
	isType ( typing::ResourceType typeCheck );

	/*
		Function: isValid

		Returns true if this resource is a null resource.

		Returns:

			True if not a valid resource.
	*/
	bool
	isValid ( void );

	/*
		Function: getId

		Returns the id of this instantiation.

		Returns:

			The <IdT> id of this instantiation.
	*/
	IdT
	getId( void );

	/*
		Function: getOwner

		Returns the owner of this instantiation.

		Returns:

			The <IdT> owner of this instantiation.
	*/
	IdT
	getOwner( void );

	/*
		Function: getAllocator

		Returns the allocator of this instantiation.

		Returns:

			The <Allocator> of this instantiation.
	*/
	Allocator &
	getAllocator( void );

	/*
		Function: changeOwner

		Changes the owner of this instantiation.

		Parameters:

			ownerToSet - sets the owner of the resource to this.
	*/
	void
	changeOwner( IdT ownerToSet );

	/*
		Function: lock

		Lock this resource for use: non-blocking.

		Parameters:

			userId - the id of the user who wants access.

		Returns:

			Id of the owner.
	*/
	IdT
	lock( IdT userId );
	/*
		Function: unlock

		Unlock this resource from use.

		Parameters:

			userId - the owner of the resource who wants to free.
	*/
	void
	unlock( IdT userId );

	/*
		Function: read

		Reads the resource and returns some amount of bytes.

		Returns:

			<ByteT> vector of bytes read.
	*/
	virtual std::vector< ByteT >
	read( void ) = 0 ;
	/*
		Function: write

		Writes bytes to the resource and returns if successfully written.

		Parameters:

			stuffToWrite - bytes to write to the resource.

		Returns:

			True if written.
	*/
	virtual bool
	write( std::vector< ByteT > const & stuffToWrite ) = 0;

};

} // namespace darts
