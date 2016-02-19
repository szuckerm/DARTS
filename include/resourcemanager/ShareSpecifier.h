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

#include <list>
#include "Resource.h"
#include "Specifier.h"


namespace darts
{

/*
	Class: ShareSpecifier

	A class used to represent shared resources. It provides
	methods query, adding, and removing users from a given resource.

	InstanceOf:
		<Resource>
*/
class ShareSpecifier: public Specifier
{
private:
//Section: private ->

	/*
		Variable: users

		A list of users for the given resource. These people use
		the resource.
	*/
	std::list< IdT > users__;

public:
//Section: Public ->

	/*
		Variable: classType
			Type of this class.
	*/
	const static typing::ResourceType classType =
	                                          typing::SharedResource;
	/*
		Variable: classInherit
			Inheritance information for this class.
	*/
	const static unsigned int classInherit = classType *
		                                     Resource::classInherit;

	/*
		Function: getUsers

		Returns a list of users of the resource.

		Returns:

			A list of <IdTs> using the current resource.
	*/
	std::list< IdT >::iterator
	getUsers( void );

	/*
		Function: addUser

		Adds a user to the list of users of this resource,

		Parameters:

			user - user to add to the list of users.
	*/
	void
	addUser( IdT user );

	/*
		Function: removeUser

		Removes a user to the list of users of this resource,

		Parameters:

			user - user to remove from the list of users.
	*/
	void
	removeUser( IdT user );
};

} // namespace darts
