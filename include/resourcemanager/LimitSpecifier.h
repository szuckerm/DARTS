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
#include "Specifier.h"


namespace darts
{

/*
	Class: LimitSpecifier

	A class used to represent limited resources. It provides
	methods and guarantees for limiting a resource.

	InstanceOf:
		<Resource>
*/
class LimitSpecifier: public Specifier
{
private:
//Section: Protected ->

	/*
		Variable: quantity__

		The amount of this resource.
	*/
	unsigned int quantity__;

public:
//Section: Public ->

	/*
		Constructor: LimitedResource

		Parameters:

			 quantityToSet - the quantity of this resource.
	*/
	LimitSpecifier( unsigned int quantityToSet ):
	quantity__( quantityToSet )
	{

	}

	LimitSpecifier()
	{
	
	}

	/*
		Variable: classType
			Type of this class.
	*/
	const static typing::ResourceType classType =
	                                         typing::LimitedResource;
	/*
		Variable: classInherit
			Inheritance information for this class.
	*/
	const static unsigned int classInherit = classType *
		                                     Resource::classInherit;

	/*
		Function: getQuantity

		Returns the quantity available of this resource.

		Returns:

			Amount of available for this resource.
	*/
	int
	getQuantity( void ) const;
};

} // namespace darts
