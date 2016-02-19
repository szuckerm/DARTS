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
#ifndef MERGE_H
#define MERGE_H

#include "DARTS.h"

DEF_CODELET(MergeSplit,0,SHORTWAIT);
DEF_CODELET(MergeSync,2,LONGWAIT);
class Merge : public ThreadedProcedure
{
public:
    int *src, *dst;
    int lo1, hi1, lo2, hi2, lo3;
    MergeSplit  split;
    MergeSync   sync;
    Codelet    *final;
    Merge(int* source, int low1, int high1, int low2, int high2, int* destination, int low3, Codelet *fin)
    : src(source), dst(destination)
    , lo1(low1), hi1(high1), lo2(low2), hi2(high2), lo3(low3)
    , split(this), sync(this), final(fin)
    {
        //add(&sync);
        add(&split);
    }
};

#endif // MERGE_H
