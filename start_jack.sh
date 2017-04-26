#!/bin/bash

DEVICE=hw:Device

JACKOPTIONS="--realtime"
ALSAOPTIONS="-n2"

RATE=44100
BLOCKSIZE=1024

jackd $JACKOPTIONS -d alsa -r$RATE -p$BLOCKSIZE -d$DEVICE $ALSAOPTIONS &
