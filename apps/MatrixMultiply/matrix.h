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
#ifndef MATRIX_H
#define	MATRIX_H
#include "Atomics.h"
#include <stdint.h>
#include <cstring>
#include <assert.h>

#ifdef MKL
#include <mkl_cblas.h>
#define INT MKL_INT
#define DGEMM(i, j, k, alpha, aPtr, aSize, bPtr, bSize, beta, cPtr, cSize) cblas_dgemm(CblasRowMajor, CblasNoTrans, CblasNoTrans, i, j, k, alpha, aPtr, aSize, bPtr, bSize, beta, cPtr, cSize)
#else
#include "/opt/shared/ACML/5.3.0/gfortran64_fma4/include/acml.h"
#define INT int
#define DGEMM(i, j, k, alpha, aPtr, aSize, bPtr, bSize, beta, cPtr, cSize) dgemm('T', 'T', i, j, k, alpha, aPtr, aSize, bPtr, bSize, beta, cPtr, cSize)
#endif

class matrix
{
private:
    double * ptr;
    INT M; //Columns
    INT N; //Row
    bool save;
public:
    matrix(void):
    ptr(0),
    M(0),
    N(0),
    save(true){ }
    
    matrix(INT m, INT n, double * pt):
    ptr(pt),
    M(m),
    N(n),
    save(true) { }
    
    matrix(INT m, INT n, bool set = true):
    M(m),
    N(n),
    save(false)
    {
        ptr = new double[M*N];
	if(set)
	  memset(ptr,0,sizeof(double)*M*N);
	else
	  ptr[0]=0;
    }
    
    matrix(matrix * source, int x, int y,INT m, INT n):
    M(m),
    N(n),
    save(false)
    {
        ptr = new double[M*N];
        
        double * sPtr = source->getPtr();
        INT sN = source->getN();
        
        for(int i=0;i<M;i++)
        {
            memcpy(&ptr[i*N],&sPtr[(i+x)*sN + y],sizeof(double)*N);       
        }
    }
    
    inline double * getPtr() { return ptr; }
    inline INT getM() { return M; }
    inline INT getN() { return N; }
    
    void resetMatrix(void)
    {
        memset(ptr,0,sizeof(double)*M*N);
    }
    
    void printMatrix(void)
    {
        for(int i = 0; i < M; i++)
        {
            for(int j = 0; j < N; j++)
            {
                std::cout << ptr[i*N + j] << " ";
            }
            std::cout << "\n" << std::endl;
        }
    }
    
    ~matrix(void)
    {
        if(!save)
            delete [] ptr;
    }
};

struct mmArgs
{
    matrix * a;
    matrix * b;
    matrix * c;
    
    int msi;
    int msj;
    int msk;
    
    int iCut;
    int jCut;
    
    int iTile;
    int jTile;
    
    int iMod;
    int jMod;
    
    mmArgs(matrix * A, matrix * B, matrix * C, int MSI, int MSJ, int MSK, int IC, int JC):
    a(A), b(B), c(C),
    msi(MSI), msj(MSJ), msk(MSK),
    iCut(IC), jCut(JC),
    iTile(msi/iCut), jTile(msj/jCut),
    iMod(msi%iCut), jMod(msj%jCut)
    { }    
};


void multiply(matrix * c, matrix * a, matrix * b);
bool compare(matrix * a, matrix * b);
void copyMatrix(matrix * dest, matrix * source, int x, int y);
void acumulateMatrix(matrix * dest, matrix * a);

void initRandomMatrix(matrix * A);
void initOneMatrix(matrix * A);
void initCountMatrix(matrix * A);
void initIdMatrix(matrix * A);

#endif	/* MATRIX_H */

