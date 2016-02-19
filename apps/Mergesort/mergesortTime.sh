#!/bin/bash

./mergesortTime 2 15 2 1 33554432 2048 >> mergeTimeStatic.txt
./mergesortTime 2 15 2 1 33554432 4096 >> mergeTimeStatic.txt
./mergesortTime 2 15 2 1 33554432 16384 >> mergeTimeStatic.txt
./mergesortTime 2 15 2 1 33554432 32768 >> mergeTimeStatic.txt

./mergesortTime 2 15 3 2 33554432 2048 >> mergeTimeDynamic.txt
./mergesortTime 2 15 3 2 33554432 4096 >> mergeTimeDynamic.txt
./mergesortTime 2 15 3 2 33554432 16384 >> mergeTimeDynamic.txt
./mergesortTime 2 15 3 2 33554432 32768 >> mergeTimeDynamic.txt

./mergesortTime 2 15 3 3 33554432 2048 >> mergeTimeSteal.txt
./mergesortTime 2 15 3 3 33554432 4096 >> mergeTimeSteal.txt
./mergesortTime 2 15 3 3 33554432 16384 >> mergeTimeSteal.txt
./mergesortTime 2 15 3 3 33554432 32768 >> mergeTimeSteal.txt

