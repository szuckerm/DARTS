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
#ifndef UTIL_DARTS_H
#define UTIL_DARTS_H


#include <darts.h>

using namespace darts;

#define DEF_CODELET(name,deps,wait)        \
struct name : public darts::Codelet        \
{                                          \
    name(darts::ThreadedProcedure *frame)  \
    : darts::Codelet(deps,deps,frame,wait) \
    {                                      \
    }                                      \
    virtual void fire();                   \
} 



#ifdef USE_TERAFLUX
#define EXIT_TP() delete myTP_
#define DARTS_EXIT() df_exit()
#else 
#define DARTS_EXIT() Runtime::finalSignal.decDep()
#define EXIT_TP()
#endif

#endif // UTIL_DARTS_H

