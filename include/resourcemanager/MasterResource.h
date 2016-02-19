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
#include <list>
#include "Defines.h"
#include "Typing.h"
#include "ResourceNeed.h"
#include "Lock.h"


namespace darts
{

class Resource;

/*
	Class: MasterResource

	Used to keep a master list of resource and information.
	MasterResources are used to allocate <Resources>.

	The master resource class also provides fast inheritance
	relationship/typing checking via prime numbers.
*/
class MasterResource
{
private:
//Section: Private->

	/*
		Variable: type__
			Type of this resource
	*/
	typing::ResourceType type__;
	/*
		Variable: inherit__
			Inheritance information for this resource.
	*/
	unsigned int inherit__;

	/*
		Variable: linkedResources__
			Maps this resource to other resources using a goodness value.
	*/
	std::multimap< int, MasterResource const * > linkedResources__;

	/*
		Variable: dependencyList__
			List of resources that are dependent on me.
	*/
	std::list< MasterResource * > dependencyList__;

	/*
		Variable: alive__
			tells if the resource is usable.
	*/
	bool alive__;

	/*
		Variable: ourResourceStats__

		A link to the resource that defines us.
	*/
	Resource * ourResourceStats__;

public:
//Section: Public ->

	/*
		Constructor: MasterResource

		Initializes the object.

		Parameters:
			typeToSet - the type of this resource.
			inheritToSet - inheritance of this resource.
			ourResourceStatsToSet - the resource to represent us.
	*/
	MasterResource( typing::ResourceType typeToSet, unsigned int inheritToSet ,
		            Resource * ourResourceStatsToSet):
	type__(typeToSet),
	inherit__(inheritToSet),
	alive__( true ),
	ourResourceStats__(ourResourceStatsToSet)
	{

	}

	/*
		Function: getType

		Returns the type of this instantiation.

		Returns:

			The <typing::ResourceType> of this master.

		See Also:

			<typing>
	*/
	typing::ResourceType
	getType() const;

	/*
		Function: getInherit

		Returns the inheritance of this instantiation.

		Returns:

			The <typing::ResourceType> of this instantation.

		See Also:

			<typing>
	*/
	unsigned int
	getInherit( void ) const;


	/*
		Function: instanceOf

		Returns true if this instantiation is the child of the type given.

		Returns:

			A bool to indicate inheritance.

		See Also:

			<typing>
	*/
	bool
	instanceOf( typing::ResourceType typeCheck ) const;

	/*
		Function: isAlive

		Returns true if this resource is alive.

		Returns:

			True if the resource is alive.
	*/
	bool
	isAlive( void ) const;

	/*
		Function: setAlive

		Says the resource is alive.
		All resources who depend on us are also set alive.
	*/
	void
	setAlive( void );


	/*
		Function: setDead

		Says the resource is dead.
		All resources who depend on us are also set dead.
	*/
	void
	setDead( void );

	/*
		Function:  getOurResourceStats

		Returns the resource info of this class.

		Returns:

			<Resource> * of this class.
	*/
	Resource *
	getOurResourceStats( void ) const;

	/*
		Function: getResourcesWhoMeetNeed

		Returns a list of resources who meet the given need that are
		mapped to this resource.

		Parameters:

			need - A need is defined by: <ResourceNeed>; A want or desire...

		Returns:

			An array of resources that meet the need.
	*/
	std::vector< MasterResource const * >
	getResourcesWhoMeetNeed ( struct ResourceNeed need );

	/*
		Function: doIMeetNeed

		Returns true if I meet the given need.

		Parameters:

			need - A need is defined by: <ResourceNeed>; A want or desire...

		Returns:

			True if the need is met.
	*/
	bool
	doIMeetNeed ( struct ResourceNeed need );

	/*
		Function: addGoodness

		Adds the reference resource to our resource map.

		Parameters:

			resource - the reference we wish to add to our map.
			goodness - how close it is to this resource.
	*/
	void
	addGoodness( MasterResource & resource, int goodness );

	/*
		Function: linksGoodness

		Adds the reference resource to our resource map and adds our
		resource to their map.

		Parameters:

			resource - the reference we wish to add to our map.
			goodness - how close the resources are together.
	*/
	void
	linkGoodness( MasterResource & resource, int goodness );

	/*
		Function: addDependency

		Adds a resource that is dependent on us to our dependency list.

		Parameters:

			resource - the reference we wish to add to our list.
	*/
	void addDependency ( MasterResource & resource );

	Lock lock;
};

} // namespace darts
