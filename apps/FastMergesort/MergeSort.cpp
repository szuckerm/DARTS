/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * 
 * DARTS - A fine-grain dataflow-inspired runtime system.                          *
 * Copyright (C) 2011-2014  University of Delaware                                 *
 *                                                                                 *
 * This library is free software; you can redistribute it and/or                   *
 * modify it under the terms of the GNU Lesser General Public                      *
 * License as published by the Free Software Foundation; either                    *
 * version 2.1 of the License, or (at your option) any later version.              *
 *                                                                                 *
 * This library is distributed in the hope that it will be useful,                 *
 * but WITHOUT ANY WARRANTY; without even the implied warranty of                  *
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU               *
 * Lesser General Public License for more details.                                 *
 *                                                                                 *
 * You should have received a copy of the GNU Lesser General Public                *
 * License along with this library; if not, write to the Free Software             *
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA  *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
#include "MergeSort.h"
#include "Merge.h"
#include <sstream>
#include <algorithm>
#include <cstdlib>

int CUTOFF_SORT = 500;

int
intcmp(const void* p1, const void* p2)
{
    return *(int*)p1-*(int*)p2;
}

void
MergeSortSplit::fire()
{
    MergeSort* frame = static_cast<MergeSort*>(myTP_);

    int *src = frame->src, lo = frame->lo, hi = frame->hi, *dst = frame->dst;

    if (hi-lo+1 <= CUTOFF_SORT) { // base case + cutoff
        qsort(src+lo,hi-lo+1,sizeof(int),intcmp);
        frame->final->decDep();
        return;
    }

    int mid = (lo+hi)/2;

    frame->sync.add(); // XXX NEW! really adds the `sync` codelet to the system
    invoke<MergeSort>(frame, dst, lo,    mid, src, &frame->sync);
    invoke<MergeSort>(frame, dst, mid+1, hi,  src, &frame->sync);
}

void
MergeSortSync::fire()
{
    MergeSort* frame = static_cast<MergeSort*>(myTP_);
    int mid = (frame->lo + frame->hi) / 2;
    invoke<Merge>(frame, frame->dst, frame->lo, mid, mid+1, frame->hi, frame->src, frame->lo, frame->final);
    EXIT_TP();
}


