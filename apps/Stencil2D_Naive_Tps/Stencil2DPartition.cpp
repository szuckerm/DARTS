
#include "Stencil2DPartition.h"
#include "Stencil2D_main.h"
#include "Stencil2DRowDecomposition.h"
#include "Stencil2DKernel.h"

void Stencil2DPartitionChunks::fire(void){
	LOAD_FRAME(Stencil2DPartition);
	
	double *Initial = FRAME(Initial); //matrix pointer initial Matrix[M][N]
	const uint64_t n_rows = FRAME(nRows); // matrix M row
	const uint64_t n_cols = FRAME(nCols); // Matrix N column
	double *New = FRAME(New);

	uint64_t nTpRows = n_rows-2;
	uint64_t nChunks=nTpRows/g_nSU;
	
	for(size_t i=0; i<g_nSU; ++i){
		uint64_t pos = nChunks*i*n_cols;
		uint64_t nTpRowsFinal = ((i==(g_nSU-1))? (nTpRows%g_nSU):0) + nChunks;
		INVOKE(Stencil2DRowDecomposition,i,Initial+pos,nTpRowsFinal+2,n_cols,New+pos, &FRAME(swapMatrix)); 
	}

	EXIT_TP();
}



void Stencil2DPartitionSwap::fire(void){
	LOAD_FRAME(Stencil2DPartition);
	uint64_t timestep = FRAME(timeStep);
	double *src = FRAME(Initial); //matrix pointer initial Matrix[M][N]
	const uint64_t InitialM = FRAME(nRows); // matrix M row
	const uint64_t InitialN = FRAME(nCols); // Matrix N column
	double *dst = FRAME(New);
	timestep --;

	typedef double (*Array2D)[InitialN];
	Array2D DST = (Array2D) dst,
			SRC = (Array2D) src;
	SWAP_PTR(&DST,&SRC);

	if (timestep == 0)
		SIGNAL(signalUP);
	else if (timestep !=0){
	//	INVOKE(Stencil2D,NewMatrix,InitialM,InitialN,InitialMatrix,timestep,&Runtime::finalSignal);

		INVOKE(Stencil2DPartition,src,InitialM,InitialN,dst,timestep,&Runtime::finalSignal);
	}
	EXIT_TP();
}

