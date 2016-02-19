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
#ifndef MERGE_SORT_H
#define MERGE_SORT_H

#include "DARTS.h"

extern int CUTOFF_SORT;

DEF_CODELET(MergeSortSplit,0,SHORTWAIT);
DEF_CODELET(MergeSortSync,2,LONGWAIT);
class MergeSort : public ThreadedProcedure
{
public:
    int *src, *dst;
    int  lo,   hi;
    MergeSortSplit split;
    MergeSortSync  sync;
    Codelet*       final;
    MergeSort(int* source, int low, int high, int* destination, Codelet* fin)
    : src(source), dst(destination)
    , lo(low), hi(high)
    , split(this), sync(this), final(fin)
    {
        //add(&sync);
        add(&split);
    }
};


#endif // MERGE_SORT_H
