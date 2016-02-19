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
	Class: HardwareSpecifier

	An abstract class used to represent hardware resources. It provides
	methods for polling hardware and interfacing with it.

	Adding this specifier to a any resource requires a polling method
	to be implemented.

	InstanceOf:
		<Resource>
*/
class HardwareSpecifier: public Specifier
{
public:
//Section: Public ->

	/*
		Variable: classType
			Type of this class.
	*/
	const static typing::ResourceType classType =
	                                        typing::HardwareResource;
	/*
		Variable: classInherit
			Inheritance information for this class.
	*/
	const static unsigned int classInherit = classType *
		                                     Resource::classInherit;

	/*
		Function: poll

		Does a hardware check for the resource to see if it is available.

		Returns:

			True if the hardware is available.
	*/
	virtual bool
	poll( void ) = 0;
};

} // namespace darts
