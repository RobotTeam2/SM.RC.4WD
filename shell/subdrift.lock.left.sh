#!/bin/bash
echo "a.cmd.param:64.kvalhold" > /dev/ttyUSB0
#echo "b.cmd.param:0.kvalhold" > /dev/ttyUSB0
#echo "c.cmd.param:0.kvalhold" > /dev/ttyUSB0
#echo "d.cmd.param:0.kvalhold" > /dev/ttyUSB0

echo "a.cmd.hardstop" > /dev/ttyUSB0
#echo "b.cmd.hardstop" > /dev/ttyUSB0
#echo "c.cmd.hardstop" > /dev/ttyUSB0
#echo "d.cmd.hardstop" > /dev/ttyUSB0

echo "b.speed:40000" > /dev/ttyUSB0
echo "b.turn:fwd" > /dev/ttyUSB0
echo "c.speed:40000" > /dev/ttyUSB0
echo "c.turn:rev" > /dev/ttyUSB0
echo "d.speed:40000" > /dev/ttyUSB0
echo "d.turn:fwd" > /dev/ttyUSB0
echo "run" > /dev/ttyUSB0
