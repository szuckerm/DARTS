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

#include "Defines.h"
#include "MemoryResource.h"


namespace darts
{

/*
	Class: HeapResource

	A class used to represent a heap memory resource. It provides
	methods for reading and writing to memory.

	InstanceOf:
		<Resource>, <LimitedResource>, <SharedResource>, <HardwareResource>,
		<MemoryResource>

	Inherits:
		<MemoryResource>
*/
class HeapResource:
	public MemoryResource
{
public:

	/*
		Variable: classType
			Type of this class.
	*/
	const static typing::ResourceType classType =
	                                          typing::HeapResource;
	/*
		Variable: classInherit
			Inheritance information for this class.
	*/
	const static unsigned int classInherit = classType *
                                             MemoryResource::classInherit;

	/*
		Constructor: HeapResource

		Initializes the object.

		Parameters:

			masterToSet - the master resource we were allocated from.
			allocatorToSet - the allocator we were allocated from.
			pointerToAssign - assigns the memory pointer to this.
			sizeInBytes - sets the quantity to this memory to this byte size.
	*/
	HeapResource( MasterResource & masterToSet, Allocator & allocatorToSet,
		            int sizeInBytes, ByteT * pointerToAssign );

	/*
		Destructor: MemoryResource

		Destroys the object.
	*/
	~HeapResource( void );

	/*
		Function: getType

		Returns the type of this instantiation.

		Returns:

			The <Typing::ResourceType> of this instantation.

		See Also:

			<Typing>
	*/
	typing::ResourceType
	getType( void );

	/*
		Function: getInherit

		Returns the inheritance of this instantiation.

		Returns:

			The inheritance value of this instantiation.

	*/
	unsigned int
	getInherit( void );
};

} // namespace darts
