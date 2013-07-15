#!/bin/bash

export LD_LIBRARY_PATH="$LD_LIBRARY_PATH:."

TARGET=login02.sm-gw.lrz.de
echo "MPWPingPong $TARGET $1 <kiB>"

for ((I=1; $I < 67000; I=$I*2)); do
	sleep 10
        date "+$I kiB; %c"
        ./MPWPingPong $TARGET $1 $I
done
