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

#include "Typing.h"
#include "Specifier.h"


namespace darts
{

/*
	Enum: GoodnessOper

	EQ  - Goodness is equal to.
	N   - Goodness is not equal to.
	L   - Goodness less than.
	LEQ - Goodness is less than or equal to.
	G   - Goodness is greater than.
	GEQ - Goodness is greater than or equal to.
*/
enum GoodnessOper{EQ, N, L, LEQ, G, GEQ};

/*
	Structure: ResourceNeed

	A tuple of the <typing::ResourceType> of resource needed, the goodness
	needed, and an operator to bound the goodness level of the needs.
*/
struct ResourceNeed
{
	typing::ResourceType typeOfNeed;
	int goodnessLevel;
	GoodnessOper howToBound;
};

/*
	Structure: ResourcePlusItsNeed

	A  tuple of <typing::ResourceType>, <Specifier>, and a vector of its
	needed resources.

	Specifiers may set limits etc for the resource type.
*/
struct ResourcePlusItsNeeds
{
	const Specifier * setALimit;
	typing::ResourceType typeOfResource;
	std::vector< struct ResourceNeed > needs;
	void * address;

	ResourcePlusItsNeeds ( const Specifier * setLimitToMe,
		                   typing::ResourceType setTypeOfResourceToMe,
						   std::vector< struct ResourceNeed > setNeedsToMe):
	setALimit ( setLimitToMe ),
	typeOfResource( setTypeOfResourceToMe ),
	needs( setNeedsToMe ),
        address(0)
	{

	}

	ResourcePlusItsNeeds ( const Specifier * setLimitToMe,
		                   typing::ResourceType setTypeOfResourceToMe,
						   std::vector< struct ResourceNeed > setNeedsToMe,
						   void * setAddressToMe):
	setALimit ( setLimitToMe ),
	typeOfResource( setTypeOfResourceToMe ),
	needs( setNeedsToMe ),
	address( setAddressToMe )
	{

	}

	ResourcePlusItsNeeds ( const Specifier * setLimitToMe,
	                       typing::ResourceType setTypeOfResourceToMe):
	setALimit ( setLimitToMe ),
	typeOfResource( setTypeOfResourceToMe ),
        address(0)
	{

	}

	ResourcePlusItsNeeds ( const Specifier * setLimitToMe,
	                       typing::ResourceType setTypeOfResourceToMe,
						   void * setAddressToMe):
	setALimit ( setLimitToMe ),
	typeOfResource( setTypeOfResourceToMe ),
	address( setAddressToMe )
	{

	}
};

} // namespace darts
