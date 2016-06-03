#!/bin/bash
echo "b.speed:10000" > /dev/ttyUSB0
echo "b.turn:fwd" > /dev/ttyUSB0

echo "a.cmd.softstop" > /dev/ttyUSB0

echo "c.speed:10000" > /dev/ttyUSB0
echo "c.turn:rev" > /dev/ttyUSB0
echo "d.speed:10000" > /dev/ttyUSB0
echo "d.turn:fwd" > /dev/ttyUSB0
echo "run" > /dev/ttyUSB0
