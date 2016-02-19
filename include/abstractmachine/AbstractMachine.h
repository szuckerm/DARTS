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


#ifndef HARDWARE_TOPOLOGY_HPP_V2
#define HARDWARE_TOPOLOGY_HPP_V2

#include <cassert>
#include <stdint.h>
#include <hwloc.h>

#include <Unit.h>
#include <Cluster.h>

// XXX TODO Move this code elsewhere

namespace darts {
namespace hwloc {

    /**
     * \brief Summarized hardware topology descriptor.
     * The current implementation wraps calls around the hwloc library to give
     * the core ids (Note: not the HW threads!).
     */
    class AbstractMachine {
    private:
        /** \TODO 
         * Use hwloc_topology_restrict() to make a "virtual block", ie in a 
         * multi-socket environment, give only the CPU set corresponding to a 
         * given socket/chip to a given scheduler.
         */ 
        hwloc_topology_t  _topology;
        Cluster         *_clusterMap;
        size_t           _nbClusters;
        size_t           _nbTotalUnits;

        /**
         * \brief Simple initialization of the topology description.
         */
        void 
        init(bool useLLC)
        {
            _nbTotalUnits = hwloc_get_nbobjs_by_type(_topology,HWLOC_OBJ_PU);
            if (useLLC == false) {
                discoverTopology();
            } else {
                discoverTopologyWithLLC();
            }
        }

        /**
         * \brief Actual "intelligence" behind the class: iterates through cores
         * and collects them in a "map". Uses last level of cache as "cluster 
         * memory."
         * \FIXME The cache ID is the same for all L1/L2/L3 - "bug" from hwloc?
         * \TODO Map the right L1D cache to its core?
         * \TODO Provide different ways of partitioning the concrete machine in 
         * an abstract one
         */
        void  discoverTopologyWithLLC(void);

        /**
         * \brief Actual "intelligence" behind the class: iterates through cores
         * and collects them in a map.
         * \FIXME The cache ID is the same for all L1/L2/L3 - "bug" from hwloc?
         * \TODO Map the right L1D cache to its core?
         * \TODO Provide different ways of partitioning the concrete machine in 
         * an abstract one
         */
        void discoverTopology(void);

    public:
        AbstractMachine(bool useLLC=false)
        : _topology(0), _clusterMap(0), _nbClusters(0), _nbTotalUnits(0)
        {
            hwloc_topology_init(&_topology);
            hwloc_topology_load(_topology);
            init(useLLC);
        }

        ~AbstractMachine() 
        {
            for (size_t i = 0; i < _nbClusters; ++i) {
                Unit *u = _clusterMap[i].getUnits();
                delete [] u;
            }
            delete [] _clusterMap;
            hwloc_topology_destroy(_topology);
        }

        size_t   getNbClusters()   const { return _nbClusters;   }
        Cluster* getClusterMap()   const { return _clusterMap;   }
        size_t   getTotalNbUnits() const { return _nbTotalUnits; }
    };
} // hwloc
} // darts
#endif
