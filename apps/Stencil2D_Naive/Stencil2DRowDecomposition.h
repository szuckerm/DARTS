#ifndef DARTS_SPENDIAL2D_ROW_SPLIT_H
#define DARTS_SPENDIAL2D_ROW_SPLIT_H

#include <stdint.h>
#include <darts.h>
#include "SIMPLIFYING_DARTS.h"
#include "Stencil2DPartition.h"
#include "Stencil2DKernel.h"
#include "Stencil2D_main.h"

using namespace darts;

DEF_CODELET_ITER(Stencil2DRowLoop,0,SHORTWAIT);
DEF_CODELET(Stencil2DRowSync,2,LONGWAIT);

DEF_TP(Stencil2DRowDecomposition)
{
	uint64_t nRowsCut;
	double *Initial; //matrix pointer initial matrix[M][N]
	const uint64_t nRows; // matrix M row
	const uint64_t nCols; // Matrix N column
	double *New;

    Stencil2DRowLoop *compute;
    Stencil2DRowSync  sync;
    Codelet*   signalUp;

	Stencil2DRowDecomposition(uint64_t nr, double *inimatrix,const uint64_t inim,const uint64_t inin,double *newmatrix, Codelet *up)
	:nRowsCut(nr)
	,Initial(inimatrix)
	,nRows(inim)
	,nCols(inin)
	,New(newmatrix)
	,compute(new Stencil2DRowLoop[nr])
	,sync(nr,nr,this,LONGWAIT)
	,signalUp(up)
	{
		add(&sync);
        for ( size_t i = 0; i < nr; ++i ) {
            compute[i] = Stencil2DRowLoop {0,0,this,SHORTWAIT,i};
            add( compute + i );
        }

	}
	~Stencil2DRowDecomposition(){delete []compute;}
};

#endif
