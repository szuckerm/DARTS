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


#include <unistd.h>
#include "MSchedPolicy.h"
#include "MicroScheduler.h"
#include "TPScheduler.h"
#include "TPSchedPolicy.h"
#include "Codelet.h"

#ifdef TRACE
#include "getClock.h"
#endif
namespace darts
{

    void
    MicroStandard::policy(void)
    {
        useconds_t usecs = 1, 
                   range = 1;
#ifdef TRACE
        addRecord(getTime(), (void*) &MicroStandard::policy);
#endif
        while (alive())
        {
            Codelet * tempCodelet = popCodelet();

            while (tempCodelet)
            {
                usecs = range; // reset sleep time
                ThreadedProcedure * checkTP = tempCodelet->getTP();
                //Does our codelet have a TP (not final codelet)
                //If yes then does that TP have a parent (means not a serial loop)
                //If yes then delete the TP
                //Else do not delete the TP
                bool deleteTP = (checkTP) ? checkTP->checkParent() : false;

#ifdef TRACE
                addRecord(getTime(), tempCodelet->returnFunct());
#endif
#ifdef COUNT
                if(getAffinity()) getAffinity()->startCounters(getID());
#endif
                tempCodelet->fire();
#ifdef COUNT
                if(getAffinity()) getAffinity()->incrementCounters(getID());
#endif
#ifdef TRACE
                addRecord(getTime(), (void*) &MicroStandard::policy);
#endif
                if (deleteTP)
                {
                    if (checkTP->decRef())
                        delete checkTP;
                }

                tempCodelet = popCodelet();
            }

            if (!tempCodelet) {
                usleep(usecs);
                usecs += range;
            }
        }
    }
    
    void
    MicroStatic::policy(void)
    {
        useconds_t usecs = 1,
                   range = 1;
#ifdef TRACE
        addRecord(getTime(), (void*) &MicroStatic::policy);
#endif
        while (alive())
        {
            Codelet * tempCodelet = popCodelet();

            while (tempCodelet)
            {
                usecs = range; // reset sleep time
                ThreadedProcedure * checkTP = tempCodelet->getTP();
                //Does our codelet have a TP (not final codelet)
                //If yes then does that TP have a parent (means not a serial loop)
                //If yes then delete the TP
                //Else do not delete the TP
                bool deleteTP = (checkTP) ? checkTP->checkParent() : false;

#ifdef TRACE
                addRecord(getTime(), tempCodelet->returnFunct());
#endif
#ifdef COUNT
                if(getAffinity()) getAffinity()->startCounters(getID());
#endif
                tempCodelet->fire();
#ifdef COUNT
                if(getAffinity()) getAffinity()->incrementCounters(getID());
#endif
#ifdef TRACE
                addRecord(getTime(), (void*) &MicroStatic::policy);
#endif
                if (deleteTP)
                {
                    if (checkTP->decRef())
                        delete checkTP;
                }
                tempCodelet = popCodelet();
            }
            if (!tempCodelet) {
                usleep(usecs);
                usecs += range;
            }
        }
    }
    
    void
    MicroDynamic::policy()
    {
        useconds_t usecs = 1, 
                   range = 1;
#ifdef TRACE
        addRecord(getTime(), (void*) &MicroDynamic::policy);
#endif 
        while (alive())
        {
            TPScheduler * myTPSched = getParentScheduler();

            Codelet * tempCodelet = myTPSched->popCodelet();

            while (tempCodelet)
            {
                usecs = range; // reset sleep time
                ThreadedProcedure * checkTP = tempCodelet->getTP();
                //Does our codelet have a TP (not final codelet)
                //If yes then does that TP have a parent (means not a serial loop)
                //If yes then delete the TP
                //Else do not delete the TP
                bool deleteTP = (checkTP) ? checkTP->checkParent() : false;

#ifdef TRACE
                addRecord(getTime(), tempCodelet->returnFunct());
#endif
#ifdef COUNT
                if(getAffinity()) getAffinity()->startCounters(getID());
#endif
                tempCodelet->fire();
#ifdef COUNT
                if(getAffinity()) getAffinity()->incrementCounters(getID());
#endif
#ifdef TRACE
                addRecord(getTime(), (void*) &MicroDynamic::policy);
#endif
                if (deleteTP)
                {
                    if (checkTP->decRef())
                        delete checkTP;
                }

                tempCodelet = myTPSched->popCodelet();
            }

            if (!tempCodelet) {
                usleep(usecs);
                usecs += range;
            }
        }
    }
    
    void
    MicroSteal::policy()
    {
        useconds_t usecs = 1, 
                   range = 1;
#ifdef TRACE
        addRecord(getTime(), (void*) &MicroSteal::policy);
#endif 
        while (alive())
        {
            Codelet * tempCodelet = popCodelet();
            if(!tempCodelet)
                tempCodelet = stealCodelet();

            if(tempCodelet)
            {
                usecs = range; // reset sleep time
                ThreadedProcedure * checkTP = tempCodelet->getTP();
                bool deleteTP = (checkTP) ? checkTP->checkParent() : false;

#ifdef TRACE
                addRecord(getTime(), tempCodelet->returnFunct());
#endif
#ifdef COUNT
                if(getAffinity()) getAffinity()->startCounters(getID());
#endif
                tempCodelet->fire();
#ifdef COUNT
                if(getAffinity()) getAffinity()->incrementCounters(getID());
#endif
#ifdef TRACE
                addRecord(getTime(), (void*) &MicroSteal::policy);
#endif
                if (deleteTP)
                {
                    if (checkTP->decRef())
                        delete checkTP;
                }
            } else { 
                usleep(usecs);
                usecs += range;
            }
        }
    }
    
    MScheduler *
    MScheduler::create(unsigned int type)
    {
        if (type==MCSTANDARD) return new MicroStandard;
        if (type==MCSTATIC) return new MicroStatic;
        if (type==MCDYNAMIC) return new MicroDynamic;
        if (type==MCSTEAL) return new MicroSteal;
        else return NULL;
    }
    
}
