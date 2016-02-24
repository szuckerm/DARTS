#ifndef SPENCIL2D_KERNEL_H
#define SPENCIL2D_KERNEL_H

#include <stddef.h>
#include <stdlib.h>
#include <stdint.h>
#include "SIMPLIFYING_DARTS.h"
//#include "Stencil2DPartition.h"

/**
* Naive 4pt stencil for 2D array
*/
void stencil2d_seq(double *dst,double *src,const uint64_t n_rows,const uint64_t n_cols,uint64_t n_tsteps);

void computeInner_stencil2d(uint64_t BlockPosition,double *InitialMatrix,double *NewMatrix, uint64_t BlockM, uint64_t BlockN,const uint64_t InitialN);

static inline void swap_ptr(void** left, void** right) {
	    void* tmp = *left;
		    *left     = *right;
		    *right    = tmp;
}

#define SWAP_PTR(left,right) swap_ptr((void**)left,(void**)right)


#endif
