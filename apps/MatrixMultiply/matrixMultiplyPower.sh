#!/bin/bash

#put the best tile
tile=32;

./mmPower 2 15 2 1 33554432 $tile $tile >> mmPower.txt
./mmPower 2 15 3 2 33554432 $tile $tile >> mmPower.txt
./mmPower 2 15 3 3 33554432 $tile $tile >> mmPower.txt
