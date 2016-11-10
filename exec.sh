#!/bin/sh
execFile='./build/wdfLooper'
audioFile='./data/testLoop.wav'

if [ -f $execFile ]; then
    $execFile $audioFile
else
    echo "/build/wdfLooper does not exist - did you forget to build it?"
fi
