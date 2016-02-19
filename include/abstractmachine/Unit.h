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


#ifndef DARTS_HWLOC_UNIT_H
#define DARTS_HWLOC_UNIT_H
namespace darts {
namespace hwloc {

    /**
     * \brief Simple, "read-only" data structure: hardware units are immutable
     * XXX FIXME TODO Move this code to its own file
     */
    class Unit {
    private:
        uint64_t _cluster, 
                 _localMem,
                 _id;
    public:
        Unit() {}
        Unit(const uint64_t cluster,
             const uint64_t localMem,
             const uint64_t id) 
        : _cluster(cluster),
          _localMem(localMem),
          _id(id)
        {}

        /** \brief @return the cluster ID */
        uint64_t getCluster()  const { return _cluster;  }
        /** \brief @return the local memory ID */
        uint64_t getLocalMem() const { return _localMem; }
        /** \brief @return the core ID */
        uint64_t getId()       const { return _id;       }

        /**
         * \brief pins the calling thread to this HW unit.
         */
        void pin() 
        {
            cpu_set_t mask;
            CPU_ZERO(&mask);
            CPU_SET(_id,&mask);
            if ( 0 != sched_setaffinity(0, sizeof(mask), &mask) )
                perror("sched_setaffinity");
        }
    };
}
}

#endif

