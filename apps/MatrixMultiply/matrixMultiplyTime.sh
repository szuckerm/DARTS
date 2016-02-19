#!/bin/bash

./mmTime 2 15 2 1 33554432 32 32 >> mmTimeStatic.txt
./mmTime 2 15 2 1 33554432 64 64 >> mmTimeStatic.txt
./mmTime 2 15 2 1 33554432 128 128 >> mmTimeStatic.txt
./mmTime 2 15 2 1 33554432 256 256 >> mmTimeStatic.txt

./mmTime 2 15 3 2 33554432 32 32 >> mmTimeDynamic.txt
./mmTime 2 15 3 2 33554432 64 64 >> mmTimeDynamic.txt
./mmTime 2 15 3 2 33554432 128 128 >> mmTimeDynamic.txt
./mmTime 2 15 3 2 33554432 256 256 >> mmTimeDynamic.txt

./mmTime 2 15 3 3 33554432 32 32 >> mmTimeSteal.txt
./mmTime 2 15 3 3 33554432 64 64 >> mmTimeSteal.txt
./mmTime 2 15 3 3 33554432 128 128 >> mmTimeSteal.txt
./mmTime 2 15 3 3 33554432 256 256 >> mmTimeSteal.txt

