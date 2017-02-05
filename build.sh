#!/bin/sh
mkdir -p build
g++ -std=c++11 -Wall ./src/wdfLooper.cpp ./src/PI/singlesample.cpp ./src/rt-wdf_lib/Libs/rt-wdf/rt-wdf.cpp ./src/rt-wdf_lib/Libs/rt-wdf/rt-wdf_nlModels.cpp ./src/rt-wdf_lib/Libs/rt-wdf/rt-wdf_nlSolvers.cpp -larmadillo -ljack -lsndfile -ljackcpp -o ./build/wdfLooper

