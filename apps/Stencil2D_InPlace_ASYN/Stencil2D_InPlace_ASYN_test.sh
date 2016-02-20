#!/bin/bash

rm Stencil2DInPlaceAsynTestResult.csv
nCores=48
nSUs_size=(1 2 4)
ts_size=(1 5 20)
nCUs_step=(48 4 2 1)

n_reps=20
rows_size=(100 200 500 1000 2000 3000 4000 5000 6000 7000 8000 9000 10000)
cols_size=(20 40 80 200 500 1000 2000 5000)

echo "MatrixDim,nCU,nSU,TotalCores:(nSU*(1+nCU)),num.TimeSteps,Kernel Times(ns),Whole Times(ns)" >> Stencil2DInPlaceAsynTestResult.csv;
for ((ts_idx=0;ts_idx<${#ts_size[@]};++ts_idx))
do
	ts=${ts_size[${ts_idx}]}
	for((nSUs_idx=0;nSUs_idx<${#nSUs_size[@]};++nSUs_idx))
	do
		nSUs=${nSUs_size[${nSUs_idx}]}
		nCUs_size=$(($((${nCores}/${nSUs}))-1))
#		for ((nCUs=1;nCUs<${nCUs_size};nCUs=$[${nCUs}*2]))
		for ((nCUs_idx=0;nCUs_idx<${#nCUs_step[@]};++nCUs_idx))
		do
			nCUs=$((${nCUs_size}/${nCUs_step[${nCUs_idx}]}));
			if [ "$nCUs" = "0" ];then
				nCUs=1
			fi
			for ((rows_idx=0;rows_idx<${#rows_size[@]};++rows_idx))
			do
				n_rows=${rows_size[rows_idx]}
				n_cols=${rows_size[rows_idx]}
				#for ((cols_idx=0;cols_idx<${#cols_size[@]};++cols_idx))
				#do
				#	n_cols=${cols_size[cols_idx]}
				#	echo "MatrixDim,nCU,nSU,TotalCores:(nSU*(1+nCU)),num.Repeats,Kernel Times(ns),Whole Times(ns)" >> Stencil2DInPlaceAsynTestResult.csv;

					./Stencil2D_InPlace_Asyn $n_rows $n_cols $ts $n_reps $nCUs $nSUs >> Stencil2DInPlaceAsynTestResult.csv
				#	done
			done
		done
	done
done


#
#for ((sz_idx=0;sz_idx<${#rows_size[@]};++sz_idx))
#	do
#		n_rows=${rows_size[sz_idx]}
#		n_cols=${cols_size[sz_idx]}
#	
#		echo "MatrixDim,nCU,nSU,TotalCores:(nSU*(1+nCU)),num.Repeats,Kernel Times(ns),Whole Times(ns)" >> Stencil2DInPlaceAsynTestResult.csv;
#		for ((ts=1;ts<101;++ts))
#		do
#			./Stencil2D_InPlace_Asyn_Tps $n_rows $n_cols $ts $n_reps $nCUs $nSUs >> Stencil2DInPlaceAsynTpsTestResult.csv
#		done
#	done
#
#




#=================================================================#
#rm Stencil2DE3TestResult.txt

#
#./Stencil2D_E3 3 3 2 1 1 >> Stencil2DE3TestResult.txt
#./Stencil2D_E3 4 4 2 1 1 >> Stencil2DE3TestResult.txt
#./Stencil2D_E3 5 5 2 1 1 >> Stencil2DE3TestResult.txt
#./Stencil2D_E3 6 6 2 1 1 >> Stencil2DE3TestResult.txt
#./Stencil2D_E3 7 7 2 1 1 >> Stencil2DE3TestResult.txt
#./Stencil2D_E3 8 8 2 1 1 >> Stencil2DE3TestResult.txt
#./Stencil2D_E3 9 9 2 1 1 >> Stencil2DE3TestResult.txt
#./Stencil2D_E3 10 10 2 1 1 >> Stencil2DE3TestResult.txt
#./Stencil2D_E3 11 11 2 1 1 >> Stencil2DE3TestResult.txt
#./Stencil2D_E3 12 12 2 1 1 >> Stencil2DE3TestResult.txt
#./Stencil2D_E3 13 13 2 1 1 >> Stencil2DE3TestResult.txt
#./Stencil2D_E3 14 14 2 1 1 >> Stencil2DE3TestResult.txt
#./Stencil2D_E3 15 15 2 1 1 >> Stencil2DE3TestResult.txt
#./Stencil2D_E3 16 16 2 1 1 >> Stencil2DE3TestResult.txt
#./Stencil2D_E3 17 17 2 1 1 >> Stencil2DE3TestResult.txt
#./Stencil2D_E3 18 18 2 1 1 >> Stencil2DE3TestResult.txt
#./Stencil2D_E3 19 19 2 1 1 >> Stencil2DE3TestResult.txt
#./Stencil2D_E3 20 20 2 1 1 >> Stencil2DE3TestResult.txt
#./Stencil2D_E3 21 21 2 1 1 >> Stencil2DE3TestResult.txt
#./Stencil2D_E3 22 22 2 1 1 >> Stencil2DE3TestResult.txt
#./Stencil2D_E3 100 100 2 1 1 >> Stencil2DE3TestResult.txt
#./Stencil2D_E3 1000 1000 2 1 1 >> Stencil2DE3TestResult.txt
#./Stencil2D_E3 100 1000 2 1 1 >> Stencil2DE3TestResult.txt
#./Stencil2D_E3 1000 100 2 1 1 >> Stencil2DE3TestResult.txt
##
##
#./Stencil2D_E3 3 3 2 2 1 >> Stencil2DE3TestResult.txt
#./Stencil2D_E3 4 4 2 2 1 >> Stencil2DE3TestResult.txt
#./Stencil2D_E3 5 5 2 2 1 >> Stencil2DE3TestResult.txt
#./Stencil2D_E3 6 6 2 2 1 >> Stencil2DE3TestResult.txt
#./Stencil2D_E3 7 7 2 2 1 >> Stencil2DE3TestResult.txt
#./Stencil2D_E3 8 8 2 2 1 >> Stencil2DE3TestResult.txt
#./Stencil2D_E3 9 9 2 2 1 >> Stencil2DE3TestResult.txt
#./Stencil2D_E3 10 10 2 2 1 >> Stencil2DE3TestResult.txt
#./Stencil2D_E3 11 11 2 2 1 >> Stencil2DE3TestResult.txt
#./Stencil2D_E3 12 12 2 2 1 >> Stencil2DE3TestResult.txt
#./Stencil2D_E3 13 13 2 2 1 >> Stencil2DE3TestResult.txt
#./Stencil2D_E3 14 14 2 2 1 >> Stencil2DE3TestResult.txt
#./Stencil2D_E3 15 15 2 2 1 >> Stencil2DE3TestResult.txt
#./Stencil2D_E3 16 16 2 2 1 >> Stencil2DE3TestResult.txt
#./Stencil2D_E3 17 17 2 2 1 >> Stencil2DE3TestResult.txt
#./Stencil2D_E3 18 18 2 2 1 >> Stencil2DE3TestResult.txt
#./Stencil2D_E3 19 19 2 2 1 >> Stencil2DE3TestResult.txt
#./Stencil2D_E3 20 20 2 2 1 >> Stencil2DE3TestResult.txt
#./Stencil2D_E3 21 21 2 2 1 >> Stencil2DE3TestResult.txt
#./Stencil2D_E3 22 22 2 2 1 >> Stencil2DE3TestResult.txt
#./Stencil2D_E3 100 100 2 2 1 >> Stencil2DE3TestResult.txt
#./Stencil2D_E3 1000 1000 2 2 1 >> Stencil2DE3TestResult.txt
#./Stencil2D_E3 100 1000 2 2 1 >> Stencil2DE3TestResult.txt
#./Stencil2D_E3 1000 100 2 2 1 >> Stencil2DE3TestResult.txt
##
##
#./Stencil2D_E3 3 3 2 3 1 >> Stencil2DE3TestResult.txt
#./Stencil2D_E3 4 4 2 3 1 >> Stencil2DE3TestResult.txt
#./Stencil2D_E3 5 5 2 3 1 >> Stencil2DE3TestResult.txt
#./Stencil2D_E3 6 6 2 3 1 >> Stencil2DE3TestResult.txt
#./Stencil2D_E3 7 7 2 3 1 >> Stencil2DE3TestResult.txt
#./Stencil2D_E3 8 8 2 3 1 >> Stencil2DE3TestResult.txt
#./Stencil2D_E3 9 9 2 3 1 >> Stencil2DE3TestResult.txt
#./Stencil2D_E3 10 10 2 3 1 >> Stencil2DE3TestResult.txt
#./Stencil2D_E3 11 11 2 3 1 >> Stencil2DE3TestResult.txt
#./Stencil2D_E3 12 12 2 3 1 >> Stencil2DE3TestResult.txt
#./Stencil2D_E3 13 13 2 3 1 >> Stencil2DE3TestResult.txt
#./Stencil2D_E3 14 14 2 3 1 >> Stencil2DE3TestResult.txt
#./Stencil2D_E3 15 15 2 3 1 >> Stencil2DE3TestResult.txt
#./Stencil2D_E3 16 16 2 3 1 >> Stencil2DE3TestResult.txt
#./Stencil2D_E3 17 17 2 3 1 >> Stencil2DE3TestResult.txt
#./Stencil2D_E3 18 18 2 3 1 >> Stencil2DE3TestResult.txt
#./Stencil2D_E3 19 19 2 3 1 >> Stencil2DE3TestResult.txt
#./Stencil2D_E3 20 20 2 3 1 >> Stencil2DE3TestResult.txt
#./Stencil2D_E3 21 21 2 3 1 >> Stencil2DE3TestResult.txt
#./Stencil2D_E3 22 22 2 3 1 >> Stencil2DE3TestResult.txt
#./Stencil2D_E3 100 100 2 3 1 >> Stencil2DE3TestResult.txt
#./Stencil2D_E3 1000 1000 2 3 1 >> Stencil2DE3TestResult.txt
#./Stencil2D_E3 100 1000 2 3 1 >> Stencil2DE3TestResult.txt
#./Stencil2D_E3 1000 100 2 3 1 >> Stencil2DE3TestResult.txt
##
##
#./Stencil2D_E3 3 3 2 4 1 >> Stencil2DE3TestResult.txt
#./Stencil2D_E3 4 4 2 4 1 >> Stencil2DE3TestResult.txt
#./Stencil2D_E3 5 5 2 4 1 >> Stencil2DE3TestResult.txt
#./Stencil2D_E3 6 6 2 4 1 >> Stencil2DE3TestResult.txt
#./Stencil2D_E3 7 7 2 4 1 >> Stencil2DE3TestResult.txt
#./Stencil2D_E3 8 8 2 4 1 >> Stencil2DE3TestResult.txt
#./Stencil2D_E3 9 9 2 4 1 >> Stencil2DE3TestResult.txt
#./Stencil2D_E3 10 10 2 4 1 >> Stencil2DE3TestResult.txt
#./Stencil2D_E3 11 11 2 4 1 >> Stencil2DE3TestResult.txt
#./Stencil2D_E3 12 12 2 4 1 >> Stencil2DE3TestResult.txt
#./Stencil2D_E3 13 13 2 4 1 >> Stencil2DE3TestResult.txt
#./Stencil2D_E3 14 14 2 4 1 >> Stencil2DE3TestResult.txt
#./Stencil2D_E3 15 15 2 4 1 >> Stencil2DE3TestResult.txt
#./Stencil2D_E3 16 16 2 4 1 >> Stencil2DE3TestResult.txt
#./Stencil2D_E3 17 17 2 4 1 >> Stencil2DE3TestResult.txt
#./Stencil2D_E3 18 18 2 4 1 >> Stencil2DE3TestResult.txt
#./Stencil2D_E3 19 19 2 4 1 >> Stencil2DE3TestResult.txt
#./Stencil2D_E3 20 20 2 4 1 >> Stencil2DE3TestResult.txt
#./Stencil2D_E3 21 21 2 4 1 >> Stencil2DE3TestResult.txt
#./Stencil2D_E3 22 22 2 4 1 >> Stencil2DE3TestResult.txt
#./Stencil2D_E3 100 100 2 4 1 >> Stencil2DE3TestResult.txt
#./Stencil2D_E3 1000 1000 2 4 1 >> Stencil2DE3TestResult.txt
#./Stencil2D_E3 100 1000 2 4 1 >> Stencil2DE3TestResult.txt
#./Stencil2D_E3 1000 100 2 4 1 >> Stencil2DE3TestResult.txt
#
#
#./Stencil2D_E3 3 3 2 5 1 >> Stencil2DE3TestResult.txt
#./Stencil2D_E3 4 4 2 5 1 >> Stencil2DE3TestResult.txt
#./Stencil2D_E3 5 5 2 5 1 >> Stencil2DE3TestResult.txt
#./Stencil2D_E3 6 6 2 5 1 >> Stencil2DE3TestResult.txt
#./Stencil2D_E3 7 7 2 5 1 >> Stencil2DE3TestResult.txt
#./Stencil2D_E3 8 8 2 5 1 >> Stencil2DE3TestResult.txt
#./Stencil2D_E3 9 9 2 5 1 >> Stencil2DE3TestResult.txt
#./Stencil2D_E3 10 10 2 5 1 >> Stencil2DE3TestResult.txt
#./Stencil2D_E3 11 11 2 5 1 >> Stencil2DE3TestResult.txt
#./Stencil2D_E3 12 12 2 5 1 >> Stencil2DE3TestResult.txt
#./Stencil2D_E3 13 13 2 5 1 >> Stencil2DE3TestResult.txt
#./Stencil2D_E3 14 14 2 5 1 >> Stencil2DE3TestResult.txt
#./Stencil2D_E3 15 15 2 5 1 >> Stencil2DE3TestResult.txt
#./Stencil2D_E3 16 16 2 5 1 >> Stencil2DE3TestResult.txt
#./Stencil2D_E3 17 17 2 5 1 >> Stencil2DE3TestResult.txt
#./Stencil2D_E3 18 18 2 5 1 >> Stencil2DE3TestResult.txt
#./Stencil2D_E3 19 19 2 5 1 >> Stencil2DE3TestResult.txt
#./Stencil2D_E3 20 20 2 5 1 >> Stencil2DE3TestResult.txt
#./Stencil2D_E3 21 21 2 5 1 >> Stencil2DE3TestResult.txt
#./Stencil2D_E3 22 22 2 5 1 >> Stencil2DE3TestResult.txt
#./Stencil2D_E3 100 100 2 5 1 >> Stencil2DE3TestResult.txt
#./Stencil2D_E3 1000 1000 2 5 1 >> Stencil2DE3TestResult.txt
#./Stencil2D_E3 100 1000 2 5 1 >> Stencil2DE3TestResult.txt
#./Stencil2D_E3 1000 100 2 5 1 >> Stencil2DE3TestResult.txt
#
#
#./Stencil2D_E3 3 3 2 6 1 >> Stencil2DE3TestResult.txt
#./Stencil2D_E3 4 4 2 6 1 >> Stencil2DE3TestResult.txt
#./Stencil2D_E3 5 5 2 6 1 >> Stencil2DE3TestResult.txt
#./Stencil2D_E3 6 6 2 6 1 >> Stencil2DE3TestResult.txt
#./Stencil2D_E3 7 7 2 6 1 >> Stencil2DE3TestResult.txt
#./Stencil2D_E3 8 8 2 6 1 >> Stencil2DE3TestResult.txt
#./Stencil2D_E3 9 9 2 6 1 >> Stencil2DE3TestResult.txt
#./Stencil2D_E3 10 10 2 6 1 >> Stencil2DE3TestResult.txt
#./Stencil2D_E3 11 11 2 6 1 >> Stencil2DE3TestResult.txt
#./Stencil2D_E3 12 12 2 6 1 >> Stencil2DE3TestResult.txt
#./Stencil2D_E3 13 13 2 6 1 >> Stencil2DE3TestResult.txt
#./Stencil2D_E3 14 14 2 6 1 >> Stencil2DE3TestResult.txt
#./Stencil2D_E3 15 15 2 6 1 >> Stencil2DE3TestResult.txt
#./Stencil2D_E3 16 16 2 6 1 >> Stencil2DE3TestResult.txt
#./Stencil2D_E3 17 17 2 6 1 >> Stencil2DE3TestResult.txt
#./Stencil2D_E3 18 18 2 6 1 >> Stencil2DE3TestResult.txt
#./Stencil2D_E3 19 19 2 6 1 >> Stencil2DE3TestResult.txt
#./Stencil2D_E3 20 20 2 6 1 >> Stencil2DE3TestResult.txt
#./Stencil2D_E3 21 21 2 6 1 >> Stencil2DE3TestResult.txt
#./Stencil2D_E3 22 22 2 6 1 >> Stencil2DE3TestResult.txt
#./Stencil2D_E3 100 100 2 6 1 >> Stencil2DE3TestResult.txt
#./Stencil2D_E3 1000 1000 2 6 1 >> Stencil2DE3TestResult.txt
#./Stencil2D_E3 100 1000 2 6 1 >> Stencil2DE3TestResult.txt
#./Stencil2D_E3 1000 100 2 6 1 >> Stencil2DE3TestResult.txt
#
#
#./Stencil2D_E3 3 3 2 7 1 >> Stencil2DE3TestResult.txt
#./Stencil2D_E3 4 4 2 7 1 >> Stencil2DE3TestResult.txt
#./Stencil2D_E3 5 5 2 7 1 >> Stencil2DE3TestResult.txt
#./Stencil2D_E3 6 6 2 7 1 >> Stencil2DE3TestResult.txt
#./Stencil2D_E3 7 7 2 7 1 >> Stencil2DE3TestResult.txt
#./Stencil2D_E3 8 8 2 7 1 >> Stencil2DE3TestResult.txt
#./Stencil2D_E3 9 9 2 7 1 >> Stencil2DE3TestResult.txt
#./Stencil2D_E3 10 10 2 7 1 >> Stencil2DE3TestResult.txt
#./Stencil2D_E3 11 11 2 7 1 >> Stencil2DE3TestResult.txt
#./Stencil2D_E3 12 12 2 7 1 >> Stencil2DE3TestResult.txt
#./Stencil2D_E3 13 13 2 7 1 >> Stencil2DE3TestResult.txt
#./Stencil2D_E3 14 14 2 7 1 >> Stencil2DE3TestResult.txt
#./Stencil2D_E3 15 15 2 7 1 >> Stencil2DE3TestResult.txt
#./Stencil2D_E3 16 16 2 7 1 >> Stencil2DE3TestResult.txt
#./Stencil2D_E3 17 17 2 7 1 >> Stencil2DE3TestResult.txt
#./Stencil2D_E3 18 18 2 7 1 >> Stencil2DE3TestResult.txt
#./Stencil2D_E3 19 19 2 7 1 >> Stencil2DE3TestResult.txt
#./Stencil2D_E3 20 20 2 7 1 >> Stencil2DE3TestResult.txt
#./Stencil2D_E3 21 21 2 7 1 >> Stencil2DE3TestResult.txt
#./Stencil2D_E3 22 22 2 7 1 >> Stencil2DE3TestResult.txt
#./Stencil2D_E3 100 100 2 7 1 >> Stencil2DE3TestResult.txt
#./Stencil2D_E3 1000 1000 2 7 1 >> Stencil2DE3TestResult.txt
#./Stencil2D_E3 100 1000 2 7 1 >> Stencil2DE3TestResult.txt
#./Stencil2D_E3 1000 100 2 7 1 >> Stencil2DE3TestResult.txt
