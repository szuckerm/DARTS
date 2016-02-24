#define __STDC_FORMAT_MACROS
#include <stdint.h>
#include "Stencil2DRowDecomposition.h"
#include "Stencil2DKernel.h"
//#include "Stencil2DPartition.h"
#include <math.h>
#include <inttypes.h>

uint32_t Stencil2DRowDecomposition::computeRowDecomposition(const uint64_t n_rows, const uint64_t n_cols){

	uint64_t nTotalSize = (n_rows-2)*(n_cols-2);//the total number of pixel in inner matrix (the whole matrix - left_edge - right_edge - upper_edge - down_edge)
	uint64_t nRowsCut = nTotalSize/TOTAL_TILE_SZ ;	
	uint64_t nThreads = (g_nCU+1)*N_THREADS;//in one clustr, (nCU+1)is available cores, N_THREADS are number of threads per cores

	uint32_t nRowsCut_final = (nRowsCut<1)?1:nThreads;
	return nRowsCut_final;
}

void 
Stencil2DRowLoop::fire(void) 
{
	LOAD_FRAME(Stencil2DRowDecomposition);
	uint64_t nRowsCut = FRAME(nRowsCut);	
	double *Initial = FRAME(Initial); //matrix pointer initial Matrix[M][n]
	const uint64_t n_rows = FRAME(nRows); // matrix M row
	const uint64_t n_cols = FRAME(nCols); // Matrix N column
	double *New = FRAME(New);
	uint64_t bp = n_cols + 1;//block position begin in the [row1,cols1]
	uint64_t BlockM = n_rows-2;
	uint64_t BlockN = n_cols-2;
	

	const uint64_t rows_ini = BlockM / nRowsCut; // initially,the total number of rows in every nRowsCut
	uint64_t BlockM_final = ((getID()==(nRowsCut-1))? (BlockM%nRowsCut):0) + rows_ini;//blockM from 1 to (nRowsCut-1), is the same (nr_initial), but the last one is different with the former, it needs add the remains.
	uint64_t pos = getID()*rows_ini * n_cols;//beginning position of every nRowsCut 


	computeInner_stencil2d(bp+pos,Initial,New, BlockM_final,BlockN,n_cols);

//	uint64_t block_sz = BlockM_final * BlockN;//block size
//	/**
//	* if block size < TILE_SZ then compute_inner()
//	* else decompose the block into sub_blocks.
//	*/
//	if(block_sz <= TOTAL_TILE_SZ ){
//		computeInner_stencil2d(bp+pos, BlockM_final,BlockN,Initial,New, n_cols);
//	}else{
//		uint64_t M = BlockM_final/N_ROWS_TILE_SZ;
//		uint64_t N = BlockN/N_COLS_TILE_SZ;
//
//		for (size_t i=0;i<= M;i+=N_ROWS_TILE_SZ)
//			for(size_t j=0;j<= N;j+=N_COLS_TILE_SZ){
//				uint64_t sub_m =(i==M)?(BlockM_final-i*N_ROWS_TILE_SZ):( (BlockM_final<N_ROWS_TILE_SZ)? BlockM_final:N_ROWS_TILE_SZ);
//				uint64_t sub_n = (j==N)?(BlockN-j*N_ROWS_TILE_SZ):((BlockN<N_COLS_TILE_SZ)?BlockN:N_COLS_TILE_SZ);
//				uint64_t sub_pos = i*n_cols*N_COLS_TILE_SZ+j*sub_n;
//				computeInner_stencil2d(bp+pos+sub_pos, sub_m,sub_n,Initial,New, n_cols);
//			}
//		
//	}
//

//	printf("Line CPU %d: %" PRIu64 " - %" PRIu64 "\n",(int)getID(),(BlockPosition+pos_final),BlockM_final);

	//computeInner_stencil2d(bp+pos_final, BlockM_final,BlockN,Initial,New, n_cols);
    
	SYNC(sync);
	EXIT_TP();
}

void
Stencil2DRowSync::fire(void)
{
    LOAD_FRAME(Stencil2DRowDecomposition);
    SIGNAL(signalUp);
    EXIT_TP();
}

