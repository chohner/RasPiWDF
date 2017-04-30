#!/bin/sh

g++ -std=c++11 -Wall ./src/potis/main.cpp ./src/potis/potis.cpp -lpthread -o ./build/potis
