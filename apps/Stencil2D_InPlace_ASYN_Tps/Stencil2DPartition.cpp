#define __STDC_FORMAT_MACROS
#include <stdint.h>
#include "Stencil2DPartition.h"
#include "Stencil2DRowDecomposition.h"
#include "Stencil2DKernel.h"
#include "Stencil2D_main.h"
#include <math.h>
#include <inttypes.h>

void Stencil2DPartitionChunks::fire(void) 
{
	LOAD_FRAME(Stencil2DPartition);
	double *initial = FRAME(initial); //matrix pointer initial Matrix[M][n]
	const uint64_t n_rows = FRAME(nRows); // matrix M row
	const uint64_t n_cols = FRAME(nCols); // Matrix N column
//	double *share = FRAME(shareChunks);
	uint64_t ts=FRAME(timeStep);	
	uint64_t nTpRows = n_rows-2;
	uint64_t nChunks=nTpRows/g_nSU;
	uint64_t	*n_tpSync = FRAME(nTpSync);
	
	for(size_t i=0; i<g_nSU; ++i){
		uint64_t pos = nChunks*i*n_cols;
		uint64_t nTpRowsFinal = ((i==(g_nSU-1))? (nTpRows%g_nSU):0) + nChunks;
		INVOKE(Stencil2DRowDecomposition,initial+pos,nTpRowsFinal+2,n_cols,ts,i,n_tpSync, &FRAME(sync)); 
	}

	EXIT_TP();

}

void
Stencil2DPartitionSync::fire(void)
{
    LOAD_FRAME(Stencil2DPartition);
	SIGNAL(signalUp);
    EXIT_TP();
}

