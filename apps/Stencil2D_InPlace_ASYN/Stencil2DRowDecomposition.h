#ifndef DARTS_SPENDIAL2D_ROW_SPLIT_H
#define DARTS_SPENDIAL2D_ROW_SPLIT_H

#include <stdint.h>
#include <stdlib.h>
#include <darts.h>
#include "SIMPLIFYING_DARTS.h"
//#include "Stencil2D.h"
#include "Stencil2DKernel.h"
#include "Stencil2D_main.h"

using namespace darts;


DEF_CODELET_ITER(Stencil2DRowLoopCopyUp,2,SHORTWAIT);
DEF_CODELET_ITER(Stencil2DRowLoopCopyDown,2,SHORTWAIT);
DEF_CODELET_ITER(Stencil2DRowLoopPre,0,SHORTWAIT);
DEF_CODELET_ITER(Stencil2DRowLoop,4,SHORTWAIT);
DEF_CODELET(Stencil2DRowSync,2,LONGWAIT);

DEF_TP(Stencil2DRowDecomposition)
{
//	uint64_t nRowsCut;
	double *initial; //matrix pointer initial matrix[M][N]
	const uint64_t nRows; // matrix M row
	const uint64_t nCols; // Matrix N column
	uint64_t timeStep;	
	Stencil2DRowLoopCopyUp *copyUp;//codelet copy shared upper line 
	Stencil2DRowLoopCopyDown *copyDown;//codelet copy shared Down line
	Stencil2DRowLoopPre *pre;
	Stencil2DRowLoop *compute;
	Stencil2DRowSync  sync;
	Codelet*   signalUp;
	double * shareRows;//every nt has an inner matrix which is used to story original data 
	uint64_t *tSteps;
	uint32_t nRowsCut;
	bool *finalize;

	Stencil2DRowDecomposition(double *inimatrix,const uint64_t inim,const uint64_t inin,uint64_t ts, Codelet *up)
//	:nRowsCut(nt)
	 :initial(inimatrix)
	 ,nRows(inim)
	 ,nCols(inin)
	 ,timeStep(ts)
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
