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
#include "Merge.h"

int CUTOFF_MERGE = 500;

template<typename T>
void
merge(T& src, int lo1, int hi1, int lo2, int hi2, T& dst, int lo3)
{
    while (lo1 <= hi1 && lo2 <= hi2) 
        dst[lo3++] = src[lo1] < src[lo2] ? src[lo1++] : src[lo2++];
    while (lo1 <= hi1)
        dst[lo3++] = src[lo1++];
    while (lo2 <= hi2) 
        dst[lo3++] = src[lo2++];
}

template<typename T>
void
swap(T& t1, T& t2)
{
    T tmp = t1;
    t1    = t2;
    t2    = tmp;
}

template<typename T>
int
bin_search(T* a, int lo, int hi, T& elem)
{
    hi = lo > hi+1 ? lo : hi+1;
    while (lo < hi) {
        int mid = (lo+hi)/2;
        if (a[mid] < elem) lo = mid+1;
        else               hi = mid;
    }
    return hi;
}

void
MergeSplit::fire()
{
    Merge* frame = static_cast<Merge*>(myTP_);
    int *src = frame->src, 
        *dst = frame->dst,
         lo1 = frame->lo1,
         lo2 = frame->lo2,
         lo3 = frame->lo3,
         hi1 = frame->hi1,
         hi2 = frame->hi2;

    int len1 = hi1 - lo1 + 1,
        len2 = hi2 - lo2 + 1;

    if (len1 < len2) {
        swap(lo1,lo2);
        swap(hi1,hi2);
        swap(len1,len2);
    }

    if (len1+len2 <= CUTOFF_MERGE) {
        if (len1 != 0)  // cutoff reached
            merge(src, lo1, hi1, lo2, hi2, dst, lo3);

        frame->final->decDep();
        return;
    }

    int mid1 = (lo1 + hi1) / 2;
    int mid2 = bin_search(src,lo2,hi2,src[mid1]);
    int mid3 = lo3 + (mid1-lo1) + (mid2-lo2);
    dst[mid3] = src[mid1];

    frame->sync.add(); // XXX NEW! really adds the `sync` codelet to the system
    
    invoke<Merge>(frame, src, lo1,    mid1-1, lo2,  mid2-1, dst, lo3,    &frame->sync);
    invoke<Merge>(frame, src, mid1+1, hi1,    mid2, hi2,    dst, mid3+1, &frame->sync);
}


void MergeSync::fire()
{
    Merge* frame = static_cast<Merge*>(myTP_);
    frame->final->decDep();
    EXIT_TP();
}
