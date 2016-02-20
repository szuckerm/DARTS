

#include <stdint.h>
#include <stdlib.h>
#include "Stencil2DKernel.h"

/**
* Naive 4pt stencil for 2D array
*/
void stencil2d_seq(double *dst,double *src,const uint64_t n_rows,const uint64_t n_cols,uint64_t n_tsteps){
    
	typedef double (*Array2D)[n_cols];
	Array2D DST = (Array2D) dst,
			SRC = (Array2D) src;
    for (size_t ts = 0; ts < n_tsteps; ++ts) {
		for (size_t i = 1; i < n_rows-1; ++i) {
            for (size_t j = 1; j < n_cols-1; ++j) {
                DST[i][j] = (SRC[i-1][j] + SRC[i+1][j] + SRC[i][j-1] + SRC[i][j+1]) / 4;
			}
		}
		SWAP_PTR(&DST,&SRC);
	}

}

/*
//compute inner blocks for no sub cut 
void computeInner_stencil2d(uint64_t BlockPosition,double *Initial,double *share,uint64_t BlockM,const uint64_t InitialM, const uint64_t InitialN){

	double *upper = new double[InitialN];//upper is used to store current line which can be used for next line computing
	double *lower = new double[InitialN];
	double *current=new double[InitialN];
	
	if(BlockM > InitialM){
		std::cout << "Inner error \n"<<std::endl;
		return;
	}

	memcpy(current,share,sizeof(double)*InitialN);
	memcpy(lower,Initial+BlockPosition-1,sizeof(double)*InitialN);
	for(uint64_t i=0;i<BlockM;++i){
		memcpy(upper,current,sizeof(double)*InitialN);
		memcpy(current,lower,sizeof(double)*InitialN);
		//memcpy(lower,Initial+BlockPosition+i*InitialN-1,sizeof(double)*(BlockNPlus2));
		double *LOWER = (i==(BlockM-1))? (share+InitialN):(Initial+BlockPosition+(i+1)*InitialN-1);
		memcpy(lower,LOWER,sizeof(double)*(InitialN));
		for(uint64_t j=0;j<InitialN-2;++j){
			Initial[BlockPosition+i*InitialN+j]=(upper[j+1]+current[j]+current[j+2]+lower[j+1])/4;
		}
	}
	delete [] upper;
	delete [] lower;
	delete [] current;
	return;
}
*/
//compute inner blocks   
void computeInner_stencil2d(uint64_t BlockPosition,double *Initial,double *share,uint64_t BlockM,uint64_t BlockN,const uint64_t InitialM, const uint64_t InitialN){

	uint64_t BlockNPlus2=BlockN+2;
	double *upper = new double[BlockNPlus2];//upper is used to store current line which can be used for next line computing
	double *lower = new double[BlockNPlus2];
	double *current=new double[BlockNPlus2];
	
	if(BlockM > InitialM){
		std::cout << "Inner error \n"<<std::endl;
		return;
	}

	memcpy(current,share,sizeof(double)*(BlockNPlus2));
	memcpy(lower,Initial+BlockPosition-1,sizeof(double)*(BlockNPlus2));
	for(uint64_t i=0;i<BlockM;++i){
		memcpy(upper,current,sizeof(double)*(BlockNPlus2));
		memcpy(current,lower,sizeof(double)*(BlockNPlus2));
		//memcpy(lower,Initial+BlockPosition+i*InitialN-1,sizeof(double)*(BlockNPlus2));
		double *LOWER = (i==(BlockM-1))? (share+BlockNPlus2):(Initial+BlockPosition+(i+1)*InitialN-1);
		memcpy(lower,LOWER,sizeof(double)*(BlockNPlus2));
		for(uint64_t j=0;j<BlockN;++j){
			Initial[BlockPosition+i*InitialN+j]=(upper[j+1]+current[j]+current[j+2]+lower[j+1])/4;
		}
	}
	delete [] upper;
	delete [] lower;
	delete [] current;
	return;
}
/*
// when we compute inner matrix, we first should copy the block to the inner of codelet
void copyMatrix_stencil2d(uint64_t BlockPosition, uint64_t BlockM, uint64_t BlockN,double *InitialMatrix,double *CopyMatrix,const uint64_t InitialM, const uint64_t InitialN){

	uint64_t i,j,k,l;
	uint64_t i_begin = BlockPosition/InitialN;
	uint64_t j_begin = BlockPosition%InitialN;
	uint64_t i_end = i_begin + BlockM-1;
	uint64_t j_end = j_begin + BlockN-1;
	
	if(i_end > InitialM){
		std::cout << "Inner error \n"<<std::endl;
		return;
	}
	for(i=i_begin,k=0;i<=i_end;++i,++k)
		for(j=j_begin,l=0;j<=j_end;++j,++l){
			CopyMatrix[k*BlockN+l]=InitialMatrix[i*InitialN+j];
		}
	return;
}
*/

/*
//copy RowDecomposition block share lines (up+lower lines)
void copyShareLines_stencil2d(uint64_t BlockPosition,double *InitialMatrix,double *CopyMatrix,uint64_t StepM,const uint64_t InitialM, const uint64_t InitialN){

	uint64_t i = BlockPosition/InitialN;

	if((i+StepM) > InitialM){
		std::cout << "Inner error \n"<<std::endl;
		return;
	}

	for(uint64_t j=0;j<InitialN;++j){
		CopyMatrix[j]=InitialMatrix[i*InitialN+j];
		CopyMatrix[InitialN+j]=InitialMatrix[(i+StepM+1)*InitialN+j];
	}
	return;
}
*/

void copyLine_stencil2d(uint64_t BlockPosition,double *Initial,double *Copy,const uint64_t InitialN){

	uint64_t i = BlockPosition/InitialN;

	memcpy(Copy,Initial+i*InitialN,sizeof(double)*InitialN);
	
	return;
}
