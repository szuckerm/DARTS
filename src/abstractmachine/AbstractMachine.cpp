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


#include <AbstractMachine.h>

typedef hwloc_obj_t obj_t;

void 
darts :: hwloc :: AbstractMachine :: discoverTopologyWithLLC(void)
{
    unsigned nbSockets = hwloc_get_nbobjs_by_type(_topology,HWLOC_OBJ_SOCKET);
    hwloc_obj_t o = hwloc_get_obj_by_type(_topology,HWLOC_OBJ_SOCKET,0);

    hwloc_obj_t obj;
    for (obj = o->first_child;
            obj && obj->type != HWLOC_OBJ_CACHE;
            obj = obj->first_child)
        ;

    _nbClusters = nbSockets;
    if (obj) {
        int n = hwloc_get_nbobjs_inside_cpuset_by_type(_topology,obj->cpuset,HWLOC_OBJ_PU);
        _nbClusters = _nbTotalUnits / n; // XXX assumes homogeneous distribution of PUs
    }
    _clusterMap = new Cluster[_nbClusters];

    // TODO Refactor this code and the next function's code into a single one 
    for (o = obj; o; o = o->next_cousin)  {
        int           nUnits = hwloc_get_nbobjs_inside_cpuset_by_type(_topology,o->cpuset,HWLOC_OBJ_PU);
        Unit *units  = new Unit[nUnits];
        for (int i = 0; i < nUnits; ++i) {
            hwloc_obj_t t = hwloc_get_obj_inside_cpuset_by_type(_topology,o->cpuset,HWLOC_OBJ_PU,i);
            Unit hwu(o->logical_index,t->logical_index,t->os_index);
            units[i] = hwu; // simple shallow copy
        }
        Cluster cluster(o->logical_index,o->logical_index,nUnits,units);
        _clusterMap[o->logical_index] = cluster; // simple shallow copy
    }
}

void 
darts :: hwloc :: AbstractMachine :: discoverTopology(void)
{
    _nbClusters   = hwloc_get_nbobjs_by_type(_topology,HWLOC_OBJ_SOCKET);
    _clusterMap   = new Cluster[_nbClusters];
    hwloc_obj_t o = hwloc_get_obj_by_type(_topology,HWLOC_OBJ_SOCKET,0);
    // TODO Refactor this code and the previous function's code into a single one
    for (; o; o = o->next_cousin)  {
        int           nUnits = hwloc_get_nbobjs_inside_cpuset_by_type(_topology,o->cpuset,HWLOC_OBJ_PU);
        Unit *units  = new Unit[nUnits];
        for (int i = 0; i < nUnits; ++i) {
            hwloc_obj_t t = hwloc_get_obj_inside_cpuset_by_type(_topology,o->cpuset,HWLOC_OBJ_PU,i);
            Unit hwu(o->logical_index,t->logical_index,t->os_index);
            units[i] = hwu; // simple shallow copy
        }
        Cluster cluster(o->logical_index,o->logical_index,nUnits,units);
        _clusterMap[o->logical_index] = cluster; // simple shallow copy
    }
}


