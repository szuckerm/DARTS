
#include "Stencil2DPartition.h"
#include "Stencil2D_main.h"
#include "Stencil2DRowDecomposition.h"
#include "Stencil2DKernel.h"

void StencilComputeInner::fire(void){
	LOAD_FRAME(Stencil2DPartition);
	
	double *Initial = FRAME(Initial); //matrix pointer initial Matrix[M][N]
	const uint64_t n_rows = FRAME(nRows); // matrix M row
	const uint64_t n_cols = FRAME(nCols); // Matrix N column
	double *New = FRAME(New);
	uint64_t n_totalsize = (n_rows-2)*(n_cols-2);//the total number of pixel in inner matrix (the whole matrix - left_edge - right_edge - upper_edge - down_edge)
	uint64_t n_rowscut = n_totalsize/TOTAL_TILE_SZ ;	
	uint64_t n_threads = (g_nCU+1)*g_nSU*N_THREADS;//(nCU+1)*nSU is available cores, N_THREADS are number of threads per cores
	/*
	*if the matrix < 84*84 (n_rowscut <1)
	*then final_cut =1, only allocate one core to compute 
	*if the matrix larger one core cache (matrix are very large or suitable for available cores)   
	*then final_cut = n_threads
	*if the matrix is very large (larger than total available core cache size), we will cut them to suitable size within the rowdecomposition TP.
	**/
	uint64_t n_rowscut_final = (n_rowscut<1)?1:n_threads;

	ADD(swapMatrix);
	INVOKE(Stencil2DRowDecomposition,n_rowscut_final,Initial,n_rows,n_cols,New,&FRAME(swapMatrix));
	EXIT_TP();

}



void StencilSwap::fire(void){
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

