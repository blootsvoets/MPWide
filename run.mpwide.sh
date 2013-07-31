#!/bin/bash

export LD_LIBRARY_PATH="$LD_LIBRARY_PATH:."

TARGET=login03-prace.smuc.lrz.de
echo "MPWPingPong $TARGET 100 $1 <kiB>"

for ((I=1; $I < 1025; I=$I*2)); do
    sleep 10
    date "+$I kiB; %c"
    ./MPWPingPong $TARGET 100 $2 $I
done

echo "MPWPingPong $TARGET 10 $1 <kiB>"
for ((I=2048; $I < 1058576; I=$I*2)); do
    sleep 10
    date "+$I kiB; %c"
    ./MPWPingPong $TARGET 10 $1 $I
done

