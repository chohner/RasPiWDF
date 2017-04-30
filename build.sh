#!/bin/sh
mkdir -p build

#./build-potis.sh
g++ -std=c++11 -O3 -Wall -Wno-unknown-pragmas ./src/wdfLooper.cpp ./src/PI/singlesample.cpp ./src/rt-wdf_lib/Libs/rt-wdf/rt-wdf.cpp ./src/rt-wdf_lib/Libs/rt-wdf/rt-wdf_nlModels.cpp ./src/rt-wdf_lib/Libs/rt-wdf/rt-wdf_nlSolvers.cpp -pthread -larmadillo -ljack -lsndfile -ljackcpp -o ./build/wdfLooper

