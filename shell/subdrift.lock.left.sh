#!/bin/bash

echo "a.cmd.param:64.kvalrun" > /dev/ttyUSB0
echo "a.speed:30000" > /dev/ttyUSB0
echo "a.turn:fwd" > /dev/ttyUSB0

echo "b.cmd.param:64.kvalrun" > /dev/ttyUSB0
echo "b.speed:100" > /dev/ttyUSB0
echo "b.turn:fwd" > /dev/ttyUSB0
#echo "b.cmd.param:64.kvalhold" > /dev/ttyUSB0
#echo "b.cmd.hardstop" > /dev/ttyUSB0


echo "c.cmd.param:64.kvalrun" > /dev/ttyUSB0
echo "c.speed:30000" > /dev/ttyUSB0
echo "c.turn:fwd" > /dev/ttyUSB0

echo "d.cmd.param:64.kvalrun" > /dev/ttyUSB0
echo "d.speed:30000" > /dev/ttyUSB0
echo "d.turn:rev" > /dev/ttyUSB0
echo "run" > /dev/ttyUSB0
