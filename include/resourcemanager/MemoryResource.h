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
#include "LimitSpecifier.h"
#include "ShareSpecifier.h"
#include "HardwareSpecifier.h"


namespace darts
{

/*
	Class: MemoryResource

	A class used to represent any memory resources. It provides
	methods for reading and writing to memory.

	InstanceOf/Inherits:
		<Resource>, <LimitedResource>, <SharedResource>, <HardwareResource>
*/
class MemoryResource:
	public Resource,
	public LimitSpecifier,
	public ShareSpecifier,
	public HardwareSpecifier
{
private:
//Section: Private ->

	/*
		Variable: pointer__

		A pointer to the beginning of memory.
	*/
	ByteT * pointer__;

public:

	/*
		Variable: classType
			Type of this class.
	*/
	const static typing::ResourceType classType =
	                                          typing::MemoryResource;
	/*
		Variable: classInherit
			Inheritance information for this class.
	*/
	const static unsigned int classInherit = classType *
	             LimitSpecifier::classInherit * ShareSpecifier::classInherit *
	                 HardwareSpecifier::classInherit;

	/*
		Constructor: MemoryResource

		Initializes the object.

		Parameters:

			masterToSet - the master resource we were allocated from.
			allocatorToSet - the allocator we were allocated from.
			pointerToAssign - assigns the memory pointer to this.
			sizeInBytes - sets the quantity to this memory to this byte size.
	*/
	MemoryResource( MasterResource & masterToSet, Allocator & allocatorToSet,
		            int sizeInBytes, ByteT * pointerToAssign );

	MemoryResource();

	/*
		Destructor: MemoryResource

		Destroys the object.
	*/
	~MemoryResource( void );

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

	/*
		Function: getPointer

		Returns a pointer to the beginning of memory.

		Returns:

			<ByteT> pointer to the beginning of memory.
	*/
	ByteT *
	getPointer( void );

	/*
		Function: read

		Reads one byte from the beginning of memory and returns it.

		Returns:

			<ByteT> vector of size 1.
	*/
	std::vector< ByteT >
	read( void );

	/*
		Function: write

		Writes the vector <ByteT> array into memory. If the array
		is bigger than the size of the resource the array is not written
		and false is returned.

		Returns:

			True on write success and false on failure.
	*/
	bool
	write( std::vector< ByteT > const & stuffToWrite );
	/*
		Function: read

		Reads bytes from memory and stores it in the given array.
		The array needs to be the size wish to be read.
		A special offset allows the programmer
		to offset by byte size into the memory. If the read is greater
		than the memory size it is not done.

		Returns:

			True on read success and false on failure.
	*/
	bool
	read( std::vector< ByteT > & stuffToStore, unsigned int initialOffset );
	/*
		Function: write

		Writes the vector <ByteT> array into memory. If the array
		is bigger than the size of the resource the array is not written
		and false is returned. A special offset allows the programmer
		to offset by byte size into the memory.

		Returns:

			True on write success and false on failure.
	*/
	bool
	write( std::vector< ByteT > const & stuffToWrite,
	       unsigned int initialOffset );

	/*
		Function: poll

		Implement me...

		Returns:
			False always...
	*/
	bool
	poll( void );
};

} // namespace darts
