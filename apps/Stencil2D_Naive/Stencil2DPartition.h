#ifndef DARTS_STENCIL2DPartition_H
#define DARTS_STENCIL2DPartition_H


#include "SIMPLIFYING_DARTS.h"
#include "Stencil2DRowDecomposition.h"
#include <stdint.h>


using namespace darts;


DEF_CODELET(StencilComputeInner,0,SHORTWAIT);
DEF_CODELET(StencilSwap,1,LONGWAIT);

DEF_TP(Stencil2DPartition){
	double *Initial; //matrix pointer initial matrix[M][N]
	const uint64_t nRows; // matrix M row
	const uint64_t nCols; // Matrix N column
	double *New; //matrix pointer New matrix[M][N]
	uint64_t timeStep;
	StencilComputeInner computeInner;
	StencilSwap	swapMatrix;
	Codelet *signalUP;
	
	Stencil2DPartition( double *inimatrix,const uint64_t m,const uint64_t n,double *newmatrix,uint64_t ts, Codelet *up)
	:Initial(inimatrix)
	,nRows(m)
	,nCols(n)
	,New(newmatrix)
	,timeStep(ts)
	,computeInner(this)
	,swapMatrix(this)
	,signalUP(up)
	{
		add(&computeInner);
	}		


};





#endif

