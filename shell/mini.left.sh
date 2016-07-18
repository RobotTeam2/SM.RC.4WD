#!/bin/bash
./mini.volt.left.sh

echo "a.speed:1100" > /dev/ttyUSB0
echo "a.turn:fwd" > /dev/ttyUSB0
echo "b.speed:1000" > /dev/ttyUSB0
echo "b.turn:rev" > /dev/ttyUSB0
echo "c.speed:110" > /dev/ttyUSB0
echo "c.turn:fwd" > /dev/ttyUSB0
echo "d.speed:100" > /dev/ttyUSB0
echo "d.turn:rev" > /dev/ttyUSB0
echo "run" > /dev/ttyUSB0
sleep 0.4

echo "a.speed:2200" > /dev/ttyUSB0
echo "a.turn:fwd" > /dev/ttyUSB0
echo "b.speed:2000" > /dev/ttyUSB0
echo "b.turn:rev" > /dev/ttyUSB0
echo "c.speed:220" > /dev/ttyUSB0
echo "c.turn:fwd" > /dev/ttyUSB0
echo "d.speed:200" > /dev/ttyUSB0
echo "d.turn:rev" > /dev/ttyUSB0
echo "run" > /dev/ttyUSB0
sleep 0.2

echo "a.speed:4400" > /dev/ttyUSB0
echo "a.turn:fwd" > /dev/ttyUSB0
echo "b.speed:4000" > /dev/ttyUSB0
echo "b.turn:rev" > /dev/ttyUSB0
echo "c.speed:440" > /dev/ttyUSB0
echo "c.turn:fwd" > /dev/ttyUSB0
echo "d.speed:400" > /dev/ttyUSB0
echo "d.turn:rev" > /dev/ttyUSB0
echo "run" > /dev/ttyUSB0


