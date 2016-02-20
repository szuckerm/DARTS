#ifndef DARTS_SPENDIAL2D_ROW_SPLIT_H
#define DARTS_SPENDIAL2D_ROW_SPLIT_H

#include <stdint.h>
#include <stdlib.h>
#include <darts.h>
#include "SIMPLIFYING_DARTS.h"
//#include "Stencil2D.h"
//#include "Stencil2DKernel.h"
//#include "Stencil2D_main.h"

using namespace darts;


DEF_CODELET_ITER(Stencil2DRowLoopCopyUp,2,SHORTWAIT);
DEF_CODELET_ITER(Stencil2DRowLoopCopyDown,2,SHORTWAIT);
DEF_CODELET_ITER(Stencil2DRowLoopPre,0,SHORTWAIT);
DEF_CODELET_ITER(Stencil2DRowLoop,4,SHORTWAIT);
DEF_CODELET(Stencil2DRowSync,2,LONGWAIT);
DEF_CODELET(Stencil2DRowCheckUp,0,SHORTWAIT);
DEF_CODELET(Stencil2DRowCheckDown,0,SHORTWAIT);
DEF_CODELET(Stencil2DRowComputeUp,0,SHORTWAIT);
DEF_CODELET(Stencil2DRowComputeDown,0,SHORTWAIT);

/*
*in Stencil2DRowDecomposition TP:
*
*Stencil2DRowLoop has 4 dependences:up0,down0,up1,down1
*	up0,down0: the uppest and lowest line of sub-array(inner of subarray)
*	up1,down1: the upper and lower line of sub-array(out side of subarray)
*	4 dependences means: the computation can't be execute until copy(up0,down0,up1,down1) finished. 
*
*checkUP,checkDown,ComputeUp,computeDown are related to these 4 dependences.
*
*nTpSync[4]: up,down,Up finished,Down finish
*
*/

DEF_TP(Stencil2DRowDecomposition)
{
	double *initial; //matrix pointer initial matrix[M][N]
	const uint64_t nRows; // matrix M row
	const uint64_t nCols; // Matrix N column
	uint64_t timeStep;
	uint32_t nTp;
	uint64_t *nTpSync;

	Stencil2DRowLoopCopyUp *copyUp;//codelet copy shared upper line 
	Stencil2DRowLoopCopyDown *copyDown;//codelet copy shared Down line
	Stencil2DRowLoopPre *pre;
	Stencil2DRowLoop *compute;
	Stencil2DRowSync  sync;
	Stencil2DRowCheckUp checkUp;
	Stencil2DRowCheckDown checkDown;
	Stencil2DRowComputeUp computeUp;
	Stencil2DRowComputeDown computeDown;
	Codelet*   signalUp;
	double * shareRows;//every nt has an inner matrix which is used to story original data 
	uint64_t *tSteps;
	uint32_t nRowsCut;
	bool *finalize;

	Stencil2DRowDecomposition(double *inimatrix,const uint64_t inim,const uint64_t inin,uint64_t ts,uint32_t tp,uint64_t *ntpsync, Codelet *up)
	:initial(inimatrix)
	,nRows(inim)
	,nCols(inin)
	,timeStep(ts)
	,nTp(tp)
	,nTpSync(ntpsync) 
	,checkUp(0,0,this,SHORTWAIT)
	,checkDown(0,0,this,SHORTWAIT)
	,computeUp(0,0,this,SHORTWAIT)
	,computeDown(0,0,this,SHORTWAIT)
	,signalUp(up)
	{
		nRowsCut	= computeRowDecomposition(inim,inin);
		copyUp		= new Stencil2DRowLoopCopyUp[nRowsCut];
		copyDown	= new Stencil2DRowLoopCopyDown[nRowsCut];
		pre			= new Stencil2DRowLoopPre[nRowsCut];
		compute		= new Stencil2DRowLoop[nRowsCut];
		shareRows	= new double[nRowsCut*2*inin];
		tSteps		= new uint64_t[nRowsCut];
		sync		= Stencil2DRowSync{nRowsCut,nRowsCut,this,LONGWAIT};
		finalize	= new bool[nRowsCut];	 
		add(&sync);
        
		for ( size_t i = 0; i < nRowsCut; ++i ) {
				tSteps[i]=ts;
				finalize[i]=false;
				copyUp[i] = Stencil2DRowLoopCopyUp {1,2,this,SHORTWAIT,i};
				copyDown[i] = Stencil2DRowLoopCopyDown {1,2,this,SHORTWAIT,i};

				pre[i] = Stencil2DRowLoopPre {0,0,this,SHORTWAIT,i};
           		compute[i] = Stencil2DRowLoop {4,4,this,SHORTWAIT,i};
				add (pre + i);
		}
	}
	uint32_t computeRowDecomposition(const uint64_t n_rows,const uint64_t n_cols);

	~Stencil2DRowDecomposition(){
		delete []copyUp;
		delete []copyDown;
		delete []compute;
		delete []shareRows;
		delete []pre;
		delete []tSteps;
	}
};

#endif
