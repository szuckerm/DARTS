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
#ifndef DARTS_MSORT_H
#define DARTS_MSORT_H

#include "DARTS.h"

DEF_CODELET(Starter,  0, SHORTWAIT);
DEF_CODELET(Reporter, 1, LONGWAIT);
class Monitor : public ThreadedProcedure
{
public:
    int   argc;
    char **argv;
    int   N;
    int  *a, *b;
    Starter  start;
    Reporter stop;
    Monitor(int ac, char *av[])
    : argc(ac), argv(av)
    , N(0), a(0), b(0)
    , start(this), stop(this)
    {
        add(&stop);
        add(&start);
    }

    ~Monitor() { delete[] a; delete[] b; }
};

#endif // DARTS_MSORT_H
