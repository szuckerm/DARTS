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


#include <iostream>
#include <stdlib.h>
#include "matrix.h"

#define MIN(X,Y) (X < Y) ? (X) : (Y)

void multiply(matrix * c, matrix * a, matrix * b)
{
    for(int i=0;i<a->getM();i++)
    {
        for(int j=0;j<b->getN();j++)
        {
            double sum = 0;
            for(int k=0;k<b->getM();k++)
            {
                sum+=a->getPtr()[i*a->getN()+k]*b->getPtr()[k*b->getN()+j];
            }
            #ifdef MKL
                c->getPtr()[i*c->getN()+j]=sum;
            #else
                c->getPtr()[j*c->getN()+i]=sum;
            #endif
        }
    }
}

bool compare(matrix * a, matrix * b)
{
    for(int i=0;i<a->getM();i++)
    {
        for(int j=0;j<a->getN();j++)
        {
            if(a->getPtr()[i*a->getN()+j]!=b->getPtr()[i*b->getN()+j])
            {
                //std::cout << "i:" << i << " " << a->getPtr()[i*a->getN()+j] << " j:" << j << " " << b->getPtr()[i*b->getN()+j] << std::endl;
                return false;
            }
        }
    }
    return true;
}

void initRandomMatrix(matrix * A)
{
    double * Aptr = A->getPtr();
    int aM = A->getM();
    int aN = A->getN();
    
    for(int i = 0; i < aM; i++)
    {
        for(int j = 0; j < aN; j++)
        {
            Aptr[i*aN + j] = rand()%100;
        }
    }
}

void initOneMatrix(matrix * A)
{
    double * Aptr = A->getPtr();
    int aM = A->getM();
    int aN = A->getN();
    
    for(int i = 0; i < aM; i++)
    {
        for(int j = 0; j < aN; j++)
        {
            //Aptr[i*aN + j] = rand()%100;
            Aptr[i*aN + j] = 1;
        }
    }
}

void initCountMatrix(matrix * A)
{
    double * Aptr = A->getPtr();
    int aM = A->getM();
    int aN = A->getN();
    
    for(int i = 0; i < aM; i++)
    {
        for(int j = 0; j < aN; j++)
        {
            //Aptr[i*aN + j] = rand()%100;
            Aptr[i*aN + j] = i*aN+j;
        }
    }
}

void initIdMatrix(matrix * A)
{
    double * Aptr = A->getPtr();
    int aM = A->getM();
    int aN = A->getN();
    
    for(int i = 0; i < aM; i++)
    {
        for(int j = 0; j < aN; j++)
        {
            if(i==j)
              Aptr[i*aN + j] = 1;
            else
                Aptr[i*aN + j] = 0;
        }
    }
}


void copyMatrix(matrix * dest, matrix * source, int x, int y)
{
    double * dPtr = dest->getPtr();
    int dN = dest->getN();
    int dM = dest->getM();
    
    double * sPtr = source->getPtr();
    int sN = source->getN();
    int sM = source->getM();
    
    int col = MIN(dM,sM);
    int row = MIN(dN,sN);
    
    int dXoff, sXoff, dYoff, sYoff;
    
    if(dN > sN)
    {
      dYoff = y;
      sYoff = 0;
    }
    else if(sN > dN)
    {
      dYoff = 0;
      sYoff = y;
    }
    else
      dYoff = sYoff = 0;
    
    if(dM > sM)
    {
      dXoff = x;
      sXoff = 0;
    }
    else if(dM < sM)
    {
      dXoff = 0;
      sXoff = x;
    }
    else
      dXoff = sXoff = 0;
    
    if(dN == sN && dM == sM)
    {
        memcpy(dPtr,sPtr,sizeof(double)*dN*dM);
    }
    else
    {
      for(int i=0;i<col;i++)
	memcpy(&dPtr[(i+dXoff)*dN + dYoff],&sPtr[(i+sXoff)*sN + sYoff],sizeof(double)*row);
    }
        
    /*if(dN > sN && dM > sM)
    {
        for(int i=0;i<sM;i++)
        {
            //std::cout << (i+x)*dN << "," << y << " to here " << sN << std::endl;
            memcpy(&dPtr[(i+x)*dN + y],&sPtr[i*sN],sizeof(double)*sN);
        }
        std::cout << "a" << std::endl;
    }
    else if(dN < sN && dM < sM)
    {
        for(int i=0;i<dM;i++)
        {
            memcpy(&dPtr[i*dN],&sPtr[(i+x)*sN + y],sizeof(double)*dN);
        }
        std::cout << "b" << std::endl;
    }
    else if(dN == sN && dM == sM)
    {
        memcpy(dPtr,sPtr,sizeof(double)*dN*dM);
	std::cout << "e" << std::endl;
    }*/
}

void acumulateMatrix(matrix * dest, matrix * a)
{
    double * aPtr = a->getPtr();
    int aN = a->getN();
    int aM = a->getM();
    
    double * dPtr = dest->getPtr();
    int dN = dest->getN();
    int dM = dest->getM();
    
    if(aN==dN && aM==dM)
    {
        for(int i=0;i<dM;i++)
        {
            for(int j=0;j<dN;j++)
            {
                dPtr[i*dN+j]+=aPtr[i*aN+j];
            }
        }
    }
}