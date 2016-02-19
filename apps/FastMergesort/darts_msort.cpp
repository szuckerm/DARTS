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
#include "darts_msort.h"
#include "MergeSort.h"
#include <algorithm>
#include <cstdio>

static inline void 
usage(const char *name) 
{
    std::cout << "USAGE: " << name << "<n elems, n>0>" << std::endl;
    DARTS_EXIT();
    exit(0);
}

template<typename T>
static inline void 
display(const T& a, const int len) 
{
    std::cout << "array = [\t";
    for (int i = 0; i < len; ++i) {
        std::cout << a[i] << '\t';
    }
    std::cout << "]" << std::endl;
}

bool
verify(int *a, int len)
{
    bool isCorrect = true;
    for (int i = 0; i < len-1; ++i) {
        if (a[i] > a[i+1]) {
            isCorrect = false;
            printf("[ERROR]\ta[%d] > a[%d] <=> %d > %d\n",  i, i+1, a[i], a[i+1]);
        }
    }
    return isCorrect;
}

void
Starter::fire()
{
    Monitor* frame = static_cast<Monitor*>(myTP_);

    if (frame->argc != 2) 
        usage(frame->argv[0]);

//  int nbproc = 0;
//  if ( 0 == (nbproc = atoi(frame->argv[1])) )
//      usage(frame->argv[0]);

    if ( 0 == (frame->N = atoi(frame->argv[1])) )
        usage(frame->argv[0]);

    //CUTOFF_SORT = frame->N/nbproc;

    int *a = new int[frame->N];
    int *b = new int[frame->N];

    for (int i = 0; i < frame->N; ++i) a[i] = i;
    std::random_shuffle(a,a+frame->N);
    std::copy(a,a+frame->N,b);

//  std::cout << "Initial values in arrays a and b:\n";
//  display(a,frame->N);
    frame->a = a;
    frame->b = b;

    invoke<MergeSort>(frame, frame->a, 0, frame->N-1, frame->b, &frame->stop);
}

void
Reporter::fire()
{
    Monitor* frame = static_cast<Monitor*>(myTP_);

    if (verify(frame->a,frame->N)) std::cout << "No errors detected.\n";
    DARTS_EXIT(); // decrements the "global" final codelet's dependencies
    EXIT_TP(); // not necessary on regular x86
}

int
main(int argc, char *argv[])
{
    uint32_t nCUsPerCluster = 3U,
             nClusters      = 1U; // or could be called 'nSUs'

    // to look at all possible policies, go to
    // $DARTS/include/scheduler/MicroScheduler.h (for the CU's schedulers) and
    // $DARTS/include/scheduler/MicroScheduler.h (for the TP/SU's schedulers)
    ThreadAffinity affin(nCUsPerCluster, nClusters, COMPACT, TPPUSHFULL, MCSTANDARD);
    if (affin.generateMask())
    {
        Runtime * rt = new Runtime(&affin);
        uint64_t startTime = getTime(); // time in nanoseconds
        rt->run(launch<Monitor>(argc, argv));
        uint64_t endTime = getTime(); // time in nanoseconds
        std::cout << "Elapsed time: " << (endTime-startTime) << "ns" << std::endl;
    } else {
        std::cerr << "Could not generate required abstract machine -- something went wrong. :(\n";
        return EXIT_FAILURE;
    }
    
    return 0;
}
