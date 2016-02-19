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


#ifndef DARTS_HWLOC_CLUSTER_H
#define DARTS_HWLOC_CLUSTER_H

#include <Unit.h>

namespace darts {
namespace hwloc {

    /**
     * \brief Cluster describes a cluster in our abstract machine. It is an immutable class.
     */
    class Cluster {
    private:
        /** \brief Cluster logical ID in the machine */
        uint64_t      _id;

        /** \brief Cluster memory. For x86, it could be the last level of cache (LLC) */
        uint64_t      _memId; 

        /** \brief Number of units in this cluster */
        uint64_t      _nbUnits;

        /** \brief units held in the cluster */
        Unit *_units;
    public:
        Cluster(uint64_t id=0, uint64_t memId=0, uint64_t nbUnits=0, Unit *units=0) 
            : _id(id), _memId(memId), _nbUnits(nbUnits), _units(units)
        {}
        ~Cluster() { }

        /** \brief Returns the ID of the cluster */
        uint64_t      getId()      const { return _id;      }
        /** \brief Returns the memory ID of the cluster */
        uint64_t      getMemId()   const { return _memId;   }
        /** \brief Returns the number of available units in the cluster */
        uint64_t      getNbUnits() const { return _nbUnits; }
        /** \brief Returns the array of units in the cluster */
        Unit *getUnits()   const { return _units;   }
    };


}
}
#endif

