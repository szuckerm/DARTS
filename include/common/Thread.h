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


#pragma once

#ifndef _MSC_VER

	#include <pthread.h>
#else

	#include <windows.h>
	#include <tchar.h>
	#include <strsafe.h>
#endif


namespace darts
{

    /*
    Class: Thread

    A class used to provide a common interface for running threads across
    different OSs.
    */
    class Thread
    {
    // Section: Private ->
    private:

        /*
        Variable: function_
        Function to start as a thread.
        */
        void * (* function_) (void *);

        /*
        Variable: argument_
        Argument to the thread.
        */
        void * argument_;

        /*
        Variable: thread_
        Natively repesents the thread.
        */
        #ifndef _MSC_VER
            pthread_t thread_;
            pthread_attr_t attr;
        #else
            DWORD thread_;
            HANDLE threadHandle_;
        #endif


    public:
    //Section: Public ->

        /*
        Constructor: Thread

        Creates a thread object to run on natively as a thread
        on the architecture.

        Parameters:
        functionToSet - function to run as a thread.
        argToSet - argument pass to the thread.

        */
        Thread ( void * (* functionToSet) (void *), void * argToSet);
        Thread ( void * (*functionToSet) (void*));
        Thread ( void );

        /*
        Function: run

        Starts the thread to run.

        Returns:

        True if the thread was created succesfully.
        */
        bool run();

        /*
        Function: join

        Waits for the thread to get done running.

        Returns:

        True if the thread exited succesfully.
        */
        bool join();

        void resetArgument( void * resetToMe );
        
        void resetFunction( void * (* functionToSet) (void *) );
        
        bool setAffinity( int cpu );
        
        ~Thread(void);

    };

} // namespace darts
