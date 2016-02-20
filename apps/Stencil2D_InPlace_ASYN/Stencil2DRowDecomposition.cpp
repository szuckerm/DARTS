#define __STDC_FORMAT_MACROS
#include <stdint.h>
#include "Stencil2DRowDecomposition.h"
#include "Stencil2DKernel.h"
#include "Stencil2D_main.h"
#include <math.h>
#include <inttypes.h>

uint32_t Stencil2DRowDecomposition::computeRowDecomposition(const uint64_t n_rows, const uint64_t n_cols){

	uint64_t nTotalSize = (n_rows-2)*(n_cols-2);//the total number of pixel in inner matrix (the whole matrix - left_edge - right_edge - upper_edge - down_edge)
	uint64_t nRowsCut = nTotalSize/TOTAL_TILE_SZ ;	
	uint64_t nThreads = (g_nCU+1)*g_nSU*N_THREADS;//(nCU+1)*nSU is available cores, N_THREADS are number of threads per cores

	uint32_t nRowsCut_final = (nRowsCut<1)?1:nThreads;
//	uint32_t nRowsCut_final = (nRowsCut<1)?1:((nRowsCut<nThreads)?nRowsCut:nThreads);
	return nRowsCut_final;
}


void Stencil2DRowLoopPre::fire(void){
	LOAD_FRAME(Stencil2DRowDecomposition);
	uint64_t Id = getID();
//	SYNC(compute[Id]);
	SYNC(copyUp[Id]);
	SYNC(copyDown[Id]);
	EXIT_TP();
}

void Stencil2DRowLoopCopyUp::fire(void) 
{
	LOAD_FRAME(Stencil2DRowDecomposition);
	uint64_t nRowsCut = FRAME(nRowsCut);	//rows decomposition number	
	double *initial = FRAME(initial); //matrix pointer initial Matrix[M][n]
	const uint64_t n_rows = FRAME(nRows); // matrix M row
	const uint64_t n_cols = FRAME(nCols); // Matrix N column
	uint64_t bm=n_rows - 2;//blockM
	//uint64_t bn=n_cols - 2;//blockN
	uint64_t Id = getID();
	double *share = FRAME(shareRows+Id*2*n_cols);
	const uint64_t rows_ini = bm / nRowsCut; // initially, the total number of rows in every nRowsCut
	uint64_t pos = Id*rows_ini * n_cols; 
	
	copyLine_stencil2d(pos,initial,share,n_cols);//copy shared upper line between blocks (up+lower lines)
	
	RESET(copyUp[Id]);	
//	SYNC(compute[Id]);
//	EXIT_TP();

	if(Id==0){
		SYNC(compute[Id]);
		SYNC(compute[Id]);
	}else{
		SYNC(compute[Id]);
		SYNC(compute[Id-1]);
	}
	EXIT_TP();

}

void Stencil2DRowLoopCopyDown::fire(void) 
{
	LOAD_FRAME(Stencil2DRowDecomposition);
	uint64_t nRowsCut = FRAME(nRowsCut);	
	double *initial = FRAME(initial); //matrix pointer initial Matrix[M][n]
	const uint64_t n_rows = FRAME(nRows); // matrix M row
	const uint64_t n_cols = FRAME(nCols); // Matrix N column
	//uint64_t bp= n_cols + 1;//block position
	uint64_t bm=n_rows - 2;//blockM
	//uint64_t bn=n_cols - 2;//blockN
	uint64_t Id = getID();
	double *share = FRAME(shareRows+Id*2*n_cols);
	const uint64_t rows_ini = bm / nRowsCut; // initially, the total number of rows in every nRowsCut
	uint64_t bm_final = ((Id==(nRowsCut-1))? (bm%nRowsCut):0) + rows_ini;
	uint64_t pos = Id*rows_ini* n_cols+(bm_final+1)*n_cols; 
	
	copyLine_stencil2d(pos,initial,share+n_cols,n_cols);//copy shared lines between blocks (up+lower lines)

	RESET(copyDown[Id]);	
//	SYNC(compute[Id]);
//	EXIT_TP();


	if((Id==nRowsCut-1)){
		SYNC(compute[Id]);
		SYNC(compute[Id]);
	}else{
		SYNC(compute[Id]);
		SYNC(compute[Id+1]);
	}
	EXIT_TP();


}

void Stencil2DRowLoop::fire(void) 
{
	LOAD_FRAME(Stencil2DRowDecomposition);
	uint64_t nRowsCut = FRAME(nRowsCut);	
	double *initial = FRAME(initial); //matrix pointer initial Matrix[M][n]
	const uint64_t n_rows = FRAME(nRows); // matrix M row
	const uint64_t n_cols = FRAME(nCols); // Matrix N column
	uint64_t bp= n_cols + 1;//block position
	uint64_t bm=n_rows - 2;//blockM
	uint64_t bn=n_cols - 2;//blockN
	uint64_t Id = getID();	
	double *share = FRAME(shareRows+Id *2*n_cols);
	const uint64_t rows_ini = bm / nRowsCut; // initially, the total number of rows in every nRowsCut
	uint64_t bm_final = ((Id ==(nRowsCut-1))? (bm%nRowsCut):0) + rows_ini;
	uint64_t pos = Id*rows_ini * n_cols; 
	

	computeInner_stencil2d(bp+pos, initial,share,bm_final,bn,n_rows,n_cols);

//-------------------------- this part is used for solving cache size limition------------------------------------------//
//	/**
//	* if block size < TILE_SZ then compute_inner()
//	* else decompose the block into sub_blocks.
//	*/
//	uint64_t block_sz = bm_final * bn; //block size
//	if(block_sz <= TOTAL_TILE_SZ ){
//		computeInner_stencil2d(bp+pos, initial,share,bm_final,bn,n_rows,n_cols);
//	}else{
//		uint64_t M = bm_final/N_ROWS_TILE_SZ;
//		uint64_t N = bn/N_COLS_TILE_SZ;
//		double share_sub[(N_COLS_TILE_SZ+2)*2]; //double *share_sub = new double[(N_COLS_TILE_SZ+2)*2];
//		for (size_t i=0;i<= M;i+=N_ROWS_TILE_SZ)
//			for(size_t j=0;j<= N;j+=N_COLS_TILE_SZ){
//				uint64_t sub_m =(i==M)?(bm_final-i*N_ROWS_TILE_SZ):( (bm_final<N_ROWS_TILE_SZ)? bm_final:N_ROWS_TILE_SZ);
//				uint64_t sub_n = (j==N)?(bn-j*N_ROWS_TILE_SZ):((bn<N_COLS_TILE_SZ)?bn:N_COLS_TILE_SZ);
//				uint64_t sub_pos = i*n_cols*N_COLS_TILE_SZ+j*sub_n;
//				
//				double *UPPER_SUB = (i==0)?share:initial+pos+sub_pos;
//				double *LOWER_SUB = (i==M)?share+n_cols:initial+bp+pos+sub_pos+sub_n*n_cols-1;
//				memcpy(share_sub,UPPER_SUB,sizeof(double)*(sub_n+2));
//				memcpy(share_sub+sub_n+2,LOWER_SUB,sizeof(double)*(sub_n+2));
//				computeInner_stencil2d(bp+pos+sub_pos,initial,share_sub, sub_m,sub_n,n_rows, n_cols);
//			}
//		//delete [] share_sub;
//	}
		

//	printf("Line CPU %d: %" PRIu64 " - %" PRIu64 "\n",(int)getID(),(BlockPosition+pos_final),BlockM_final);
    
	RESET(compute[Id]);	

	Stencil2DRowLoopPre *pre = FRAME(pre);

	uint64_t *ts = FRAME(tSteps);
	--(ts[Id]);

	bool *finalize = FRAME(finalize);
	if( finalize[Id] == true)
		EXIT_TP();
	
	if(nRowsCut==1){
		SYNC(copyUp[Id]);
		SYNC(copyDown[Id]);
	}else{
		if(Id ==0){
			SYNC(copyUp[Id]);
			SYNC(copyUp[Id+1]);
		}else if(Id==(nRowsCut-1)){
			SYNC(copyDown[Id]);
			SYNC(copyDown[Id-1]);
		}else {
			SYNC(copyUp[Id+1]);
			SYNC(copyDown[Id-1]);
		}
	}

	add(&pre[Id]);
	if(ts[Id]==0){
		SYNC(sync);
		finalize[Id]=true;
		//std::cout <<"finish ID: " << Id <<std::endl;	
	}
//	std::cout <<"compute: " << Id <<std::endl;	
	EXIT_TP();

}

void
Stencil2DRowSync::fire(void)
{
    LOAD_FRAME(Stencil2DRowDecomposition);
	SIGNAL(signalUp);
    EXIT_TP();
}

