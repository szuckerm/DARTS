#ifndef DARTS_STENCIL2DPartition_H
#define DARTS_STENCIL2DPartition_H


#include "SIMPLIFYING_DARTS.h"
//#include "Stencil2DRowDecomposition.h"
#include <stdint.h>


using namespace darts;
extern uint32_t g_nSU;

DEF_CODELET(Stencil2DPartitionChunks,0,SHORTWAIT);
DEF_CODELET(Stencil2DPartitionSwap,1,LONGWAIT);

DEF_TP(Stencil2DPartition){
	double *Initial; //matrix pointer initial matrix[M][N]
	const uint64_t nRows; // matrix M row
	const uint64_t nCols; // Matrix N column
	double *New; //matrix pointer New matrix[M][N]
	uint64_t timeStep;
	Stencil2DPartitionChunks nChunks;
	Stencil2DPartitionSwap	swapMatrix;
	Codelet *signalUP;
	
	Stencil2DPartition( double *inimatrix,const uint64_t m,const uint64_t n,double *newmatrix,uint64_t ts, Codelet *up)
	:Initial(inimatrix)
	,nRows(m)
	,nCols(n)
	,New(newmatrix)
	,timeStep(ts)
	,nChunks(0,0,this,SHORTWAIT)
	,swapMatrix(g_nSU,g_nSU,this,LONGWAIT)
	,signalUP(up)
	{
		add(&nChunks);
	}		


};





#endif

