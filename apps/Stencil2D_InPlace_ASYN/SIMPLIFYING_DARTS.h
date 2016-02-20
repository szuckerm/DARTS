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
#ifndef SIMPLIFYING_DARTS_H
#define SIMPLIFYING_DARTS_H

#include <stdint.h>
#include <darts.h>

using namespace darts;

#define DEF_TP(TPName) struct TPName : public ThreadedProcedure

#define DEF_CODELET_ITER(name,deps,wait)               \
class name : public darts::Codelet                     \
{                                                      \
private:                                               \
    uint64_t _id;                                      \
public:                                                \
    name(uint32_t           dep,   uint32_t reset,     \
         ThreadedProcedure *frame, uint64_t meta,      \
         uint64_t id)                                  \
    : Codelet(dep,reset,frame,meta)                    \
    , _id(id)                                          \
    {                                                  \
    }                                                  \
    name(darts::ThreadedProcedure *frame=0)            \
    : Codelet(deps,deps,frame,wait)                    \
    , _id(0)                                           \
    {                                                  \
    }                                                  \
    uint64_t     getID() const { return _id; }         \
    virtual void fire();                               \
} 

#define DEF_CODELET(name,deps,wait)                    \
struct name : public darts::Codelet                    \
{                                                      \
    name(uint32_t           dep=0,   uint32_t reset=0, \
         ThreadedProcedure *frame=0, uint64_t meta=0)  \
    : Codelet(dep,reset,frame,meta)                    \
    {                                                  \
    }                                                  \
    name(darts::ThreadedProcedure *frame)              \
    : Codelet(deps,deps,frame,wait)                    \
    {                                                  \
    }                                                  \
    virtual void fire();                               \
} 

#define LOAD_FRAME(TPName) TPName* frame = static_cast<TPName*>(myTP_)
#define GET_FRAME()        (*frame)
#define FRAME(field)       (*frame).field
#define INVOKE(TPName,...) invoke<TPName>(frame,__VA_ARGS__)
#define SIGNAL(field)      (*frame).field->decDep()
#define SYNC(field)        (*frame).field.decDep()
#define ADD(cd_name)       frame->cd_name.add()
#define RESET(cd_name)	   frame->cd_name.resetCodelet()

#define DARTS_EXIT() Runtime::finalSignal.decDep()
#define EXIT_TP() return




#endif // SIMPLIFYING_DARTS_H




