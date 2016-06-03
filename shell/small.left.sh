#!/bin/bash
echo "a.speed:10000" > /dev/ttyUSB0
echo "a.turn:fwd" > /dev/ttyUSB0

echo "b.cmd.softstop" > /dev/ttyUSB0

echo "c.speed:10000" > /dev/ttyUSB0
echo "c.turn:fwd" > /dev/ttyUSB0
echo "d.speed:10000" > /dev/ttyUSB0
echo "d.turn:rev" > /dev/ttyUSB0
echo "run" > /dev/ttyUSB0
