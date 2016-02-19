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
#include "MasterResource.h"
#include "NullAllocator.h"


namespace darts
{

/*
	Class: NullResource

	A resource that hass no value. Used for error checking.

*/
class NullResource: public Resource
{
private:

	template <typename T> inline T& 
	getLvalue( void ) 
	{
	  static T t;
	  return t;
	}

	MasterResource &
	getMasterResourceLvalue( void )
	{
	  static MasterResource t(typing::NullResource,0,0);

	  return t;
	}



public:
//Section: Public ->


	/*
		Constructor: NullResource

		Initializes the object.
	*/
	NullResource( ):
	Resource( getMasterResourceLvalue() , getLvalue< NullAllocator >() )
	{
	}

	/*
		Variable: classType
			Type of this class.
	*/
	const static typing::ResourceType classType = typing::NullResource;
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
	typing::ResourceType 
	getType( void ) 
	{ 
		return classType;
	}

	/*
		Function: getInherit

		Returns the inheritance of this instantiation.

		Returns:

			The inheritance value of this instantiation.

	*/
	unsigned int getInherit( void )
	{ 
		return classInherit;
	}

	/*
		Function: read

		Returns an empty <ByteT> vector.
	*/
	std::vector< ByteT > read() 
	{ 
		std::vector< ByteT> vec; 
		return vec; 
	};

	/*
		Function: write

		Doesn't write anything.

		Parameters:

			stuffToWrite - bytes to write to the resource.

		Returns:

			True if written.
	*/
	bool write( std::vector< ByteT > const & stuffToWrite )
	{
		// Prevent compiler warning about unused arguments
		(void) stuffToWrite;

		return false; 
	}

};

} // namespace darts
