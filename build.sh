#!/bin/sh
mkdir -p build
g++ -std=c++11 ./src/wdfLooper.cpp ./src/PI/singlesample.cpp -ljack -lsndfile -ljackcpp -o ./build/wdfLooper
#g++ -std=c++11 ./src/test.cpp -ljack -lsndfile -ljackcpp -o ./build/test