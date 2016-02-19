#!/bin/bash

#put the best base
base=2048;

./mergesortPower 2 15 2 1 33554432 $base >> mergePower.txt
./mergesortPower 2 15 3 2 33554432 $base >> mergePower.txt
./mergesortPower 2 15 3 3 33554432 $base >> mergePower.txt
