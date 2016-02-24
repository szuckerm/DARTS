/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * 
 * DARTS - A fine-grain dataflow-inspired runtime system.                          *
 * Copyright (C) 2011-2014  University of Delaware                                 *
 *                                                                                 *
 * This library is free software; you can redistribute it and/or                   *
 * modify it under the terms of the GNU Lesser General Public                      *
 * License as published by the Free Software Foundation; either                    *
 * version 2.1 of the License, or (at your option) any later version.              *
 *                                                                                 *
 * This library is distributed in the hope that it will be useful,                 *
 * but WITHOUT ANY WARRANTY; without even the implied warranty of                  *
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU               *
 * Lesser General Public License for more details.                                 *
 *                                                                                 *
 * You should have received a copy of the GNU Lesser General Public                *
 * License along with this library; if not, write to the Free Software             *
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA  *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
#include <unistd.h>
#include <climits>
#include <cstdio>
#include <cerrno>
#include <iostream>
#include <algorithm>
#include "Stencil2D_main.h"
//#include <mkl_cblas.h>

static inline void usage(const char *name) 
{
	std::cout << "USAGE: " << name << "<num vector elems, num>0>" << std::endl;
	//std::cout << "please input number of row, number of column,timesteps,nCU and nSU "<<"\n"<<std::endl;
	DARTS_EXIT();
	exit(0);
}

uint32_t g_nCU, g_nSU;

/**
* 
* inputs:
* n_rows -- the number of rows in <orig> and <res> 
* n_cols -- the number of columns in <orig> and <res>
* orig   -- a "true" 2D array which holds the reference results
* res    -- a "true" 2D array which holds the values to be verified
*
* output:
* True if <orig> and <res> have identical results within an epsilon. False
* otherwise.
*/
bool
result_is_correct(const size_t  n_rows, const size_t  n_cols,const double* orig,   const double* res)
{
	    typedef double (*Array2D)[n_cols];
	    const Array2D ORIG       = (const Array2D) orig,
                    RES        = (const Array2D) res;
	    bool          is_correct =   true;
	    const double  epsilon    = 0.0001;

	    for (size_t i = 0; is_correct && i < n_rows; ++i) 
	        for (size_t j = 0; is_correct && j < n_cols; ++j) 
				if ( !( is_correct = fabs( RES[i][j] - ORIG[i][j] ) <= epsilon ) )
					printf("Values mismatch! [%lu,%lu]\tORIG = %5.5f != RES = %5.5f\n",i, j, ORIG[i][j], RES[i][j]);

		return is_correct;
}

/**
 * brief <init2Darray> takes a 2D array (assumed to be allocated in contiguous
 * memory) and initializes it with arbitrary (well-formed) double precision
 * values.
 *
 * inputs:
 * a      -- the 2D array to initialize
 * n_rows -- the number of rows in <a>
 * n_cols -- the number of columns in <a>
 *
 * output: N/A
 */
void init2Darray ( double* a, const size_t n_rows, const size_t n_cols )
{
    typedef double (*Array2D)[n_cols];
    Array2D A = (Array2D) a;
    for (size_t i = 0; i < n_rows; ++i) 
        for (size_t j = 0; j < n_cols; ++j) 
            A[i][j] = (1+i)*j + 1.3;
}

int main(int argc, char *argv[])
{
	if (argc != 7)
		usage(argv[0]);

	uint64_t N_ROWS = strtoul(argv[1],NULL,0);
	uint64_t N_COLS = strtoul(argv[2],NULL,0);
	uint64_t N_TSTEPS= strtoul(argv[3],NULL,0);
	uint64_t N_REPES = strtoul(argv[4],NULL,0);
	uint32_t nCUsPerCluster = strtoul(argv[5],NULL,0);
	uint32_t nClusters= strtoul(argv[6],NULL,0);
	g_nCU = nCUsPerCluster;
	g_nSU = nClusters;

	//if (( 0 == N_COLS )||(0==N_ROWS))
        //	usage(argv[0]);

	double* OriginalMatrix = new double[N_ROWS*N_COLS];
	double* InitialMatrix  = new double [ N_ROWS*N_COLS ];
	double* NewMatrix = new double [ N_ROWS*N_COLS ];

	init2Darray(OriginalMatrix,N_ROWS,N_COLS);// initial 2D array

	uint64_t StartTime_k=0,StartTime_w=0; //time for runtime kernal and the whole procedure
	uint64_t EndTime=0; //end time for procedure
	double AvgTime_k =0, AvgTime_w =0;
	
	ThreadAffinity affin(nCUsPerCluster, nClusters, COMPACT, TPPUSHFULL, MCSTANDARD);

	if (affin.generateMask()){
		for(size_t i=0; i<N_REPES;++i){
			memcpy(InitialMatrix,OriginalMatrix,sizeof(double)*N_ROWS*N_COLS);
			memcpy(NewMatrix,OriginalMatrix,sizeof(double)*N_ROWS*N_COLS);//the main reason copy date to newMatrix is copy the outerMatrix, the outer martix is always keeping a constant value.
			StartTime_w +=getTime();//start time for whole procedure
			Runtime rt(&affin);		
			StartTime_k +=getTime();//start time for kernal procedure
			rt.run(launch<Stencil2DPartition>(InitialMatrix,N_ROWS,N_COLS,NewMatrix,N_TSTEPS, &Runtime::finalSignal)); 
			EndTime +=getTime();//end time
		}
		AvgTime_k = (EndTime-StartTime_k)/N_REPES;
		AvgTime_w = (EndTime-StartTime_w)/N_REPES;
		std::cout << N_ROWS<<"*"<<N_COLS<<","<<g_nCU<<","<<g_nSU<<","<<g_nSU*(1+g_nCU)<<","<<N_TSTEPS<<","<<std::setprecision(18)<< AvgTime_k<<","<<AvgTime_w<<std::endl;

	}else{
		std::cerr << "Could not generate required abstract machine -- something went wrong. :(\n";
		return EXIT_FAILURE;
	}

	// the remain code are for testing and verifying
	double* SeqMatrix  = new double [ N_ROWS*N_COLS ];
	memcpy(SeqMatrix,OriginalMatrix,sizeof(double)*N_ROWS*N_COLS);
	bool iscorrect;
	stencil2d_seq(SeqMatrix,OriginalMatrix,N_ROWS,N_COLS,N_TSTEPS);	
	iscorrect = result_is_correct(N_ROWS,N_COLS,SeqMatrix,InitialMatrix);
	if (!iscorrect)
		std::cout << "error\t"<< "\n";
	delete[] InitialMatrix;
	delete[] NewMatrix;
	delete[] SeqMatrix;

	return 0;
}
