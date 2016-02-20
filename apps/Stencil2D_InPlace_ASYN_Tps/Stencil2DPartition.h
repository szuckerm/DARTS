#ifndef DARTS_SPENDIAL2D_PARTITION_H
#define DARTS_SPENDIAL2D_PARTITION_H

#include <stdint.h>
#include <stdlib.h>
#include <darts.h>
#include "SIMPLIFYING_DARTS.h"
//#include "Stencil2DKernel.h"
#include "Stencil2D_main.h"

using namespace darts;

extern uint32_t g_nSU;

DEF_CODELET(Stencil2DPartitionChunks,0,SHORTWAIT);
DEF_CODELET(Stencil2DPartitionSync,1,LONGWAIT);
DEF_TP(Stencil2DPartition)
{
	double *initial; //matrix pointer initial matrix[M][N]
	const uint64_t nRows; // matrix M row
	const uint64_t nCols; // Matrix N column
	uint64_t timeStep;	
	Stencil2DPartitionChunks nChunks;
	Stencil2DPartitionSync sync;
	Codelet*   signalUp;
	uint64_t	*nTpSync;//sync TPs	 

	Stencil2DPartition(double *inimatrix,const uint64_t n_rows,const uint64_t n_cols,uint64_t ts, Codelet *up)
	:initial(inimatrix)
	,nRows(n_rows)
	,nCols(n_cols)
	,timeStep(ts)
	,nChunks(0,0,this,SHORTWAIT)
	,sync(g_nSU,g_nSU,this,LONGWAIT)
	,signalUp(up)
	,nTpSync(new uint64_t[g_nSU*4])
	{
		add(&nChunks);
		for(size_t i=0;i<g_nSU;++i){
			nTpSync[i*4]=ts;
			nTpSync[i*4+1]=ts;
			nTpSync[i*4+2]=ts;
			nTpSync[i*4+3]=ts;

		}
	}

	~Stencil2DPartition(){
		delete []nTpSync;
	}
};

#endif
