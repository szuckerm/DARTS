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


#include "darts.h"
#include "mergeUnrolledTP.h"

using namespace darts;

void mergeSort::Check::fire(void)
{
    mergeSort * myMerge = static_cast<mergeSort*>(myTP_);
    
    if(myMerge->size==1)
        myMerge->toSignal->decDep();
    else
    {
        if( myMerge->size/2 < myMerge->base)
        {
            invoke<quickSort>(myMerge, myMerge->in, myMerge->size, &myMerge->merge);
        }
        else if((myMerge->size/2)/myMerge->base < 9)
        {
            invoke<mergeBase>(myMerge, myMerge->out, myMerge->in, myMerge->size/2, &myMerge->merge);
            invoke<mergeBase>(myMerge, myMerge->out+myMerge->size/2, myMerge->in+myMerge->size/2, myMerge->size - myMerge->size/2, &myMerge->merge);
        }
        else
        {
            invoke<mergeSort>(myMerge, myMerge->out, myMerge->in, myMerge->size/2,  myMerge->base, &myMerge->merge);
            invoke<mergeSort>(myMerge, myMerge->out+myMerge->size/2, myMerge->in+myMerge->size/2, myMerge->size - myMerge->size/2, myMerge->base, &myMerge->merge);    
        }
    }   
}

void mergeSort::Merge::fire(void)
{
    mergeSort * myMerge = static_cast<mergeSort*>(myTP_);
    int j = 0;
    int k = myMerge->size/2;
    int length = myMerge->size;
    
    for(int i=0; i<length; i++)
    {
        if(j < length/2 && k < length)
        {
            if(myMerge->in[j] < myMerge->in[k])
            {
                myMerge->out[i] = myMerge->in[j++];
            }
            else
            {
                myMerge->out[i] = myMerge->in[k++];
            }
        }
        else if(j < length/2)
        {
            myMerge->out[i] = myMerge->in[j++];
        }
        else if(k < length)
        {
            myMerge->out[i] = myMerge->in[k++];
        }
    }
    
    myMerge->toSignal->decDep();
}

void swap(int &a, int &b)
{
    int c = a;
    a = b;
    b = c;
}

int partition(int * array, int left, int right, int pivotIndex)
{
    int pivotValue = array[pivotIndex];
    swap(array[pivotIndex], array[right]);
    int storeIndex = left;
    
    for(int i=left; i<right; i++)
    {
        if(array[i]<=pivotValue)
        {
            swap(array[i],array[storeIndex]);
            storeIndex++;
        }
    }
    swap(array[storeIndex],array[right]);
    return storeIndex;
}

void quicksort(int * array, int left, int right)
{
    if(left < right)
    {
        int pivotIndex = ( rand() % (right-left) ) + left;
        //int pivotIndex = ((right-left)/2) + left;
        int pivotNewIndex = partition(array, left, right, pivotIndex);
        quicksort(array,left,pivotNewIndex-1);
        quicksort(array,pivotNewIndex+1,right);
    }
}

void mergeBase::quick::fire(void)
{
    quicksort(in, left, right);
    toSignal->decDep();
}

void mergeBase::merge::fire(void)
{
    int j = 0;
    int k = size/2;
    int length = size;
    
    for(int i=0; i<length; i++)
    {
        if(j < length/2 && k < length)
        {
            if(in[j] < in[k])
            {
                out[i] = in[j++];
            }
            else
            {
                out[i] = in[k++];
            }
        }
        else if(j < length/2)
        {
            out[i] = in[j++];
        }
        else if(k < length)
        {
            out[i] = in[k++];
        }
    }
    toSignal->decDep();
}

void quickSort::quick::fire(void)
{
    quicksort(in, left, right);
    toSignal->decDep();
}