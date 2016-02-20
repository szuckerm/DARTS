#ifndef SPENCIL2D_KERNEL_H
#define SPENCIL2D_KERNEL_H

#include <stddef.h>
#include <stdlib.h>
#include <stdint.h>
#include "SIMPLIFYING_DARTS.h"
#include <stdio.h>



static inline void swap_ptr(void** left, void** right) {
	    void* tmp = *left;
		    *left     = *right;
		    *right    = tmp;
}

#define SWAP_PTR(left,right) swap_ptr((void**)left,(void**)right)
/**
* Naive 4pt stencil for 2D array
*/
void stencil2d_seq(double *dst,double *src,const uint64_t n_rows,const uint64_t n_cols,uint64_t n_tsteps);

void computeInner_stencil2d(uint64_t BlockPosition,double *Initial,double *share,uint64_t BlockM,uint64_t BlockN,const uint64_t InitialM, const uint64_t InitialN);

//void copyShareLines_stencil2d(uint64_t BlockPosition,double *InitialMatrix,double *CopyMatrix,uint64_t StepM,const uint64_t InitialM, const uint64_t InitialN);


void copyLine_stencil2d(uint64_t BlockPosition,double *Initial,double *Copy,const uint64_t InitialN);



#endif
