#!/bin/bash
./mini.volt.left.sh
echo "a.speed:40000" > /dev/ttyUSB0
echo "a.turn:rev" > /dev/ttyUSB0
echo "b.speed:40000" > /dev/ttyUSB0
echo "b.turn:fwd" > /dev/ttyUSB0
echo "c.speed:4000" > /dev/ttyUSB0
echo "c.turn:rev" > /dev/ttyUSB0
echo "d.speed:4000" > /dev/ttyUSB0
echo "d.turn:fwd" > /dev/ttyUSB0
echo "run" > /dev/ttyUSB0

HOME=`dirname $0`/..
$HOME/MPU6050/turn.until $*
echo "stop" > /dev/ttyUSB0
