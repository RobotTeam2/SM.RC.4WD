#!/bin/bash
./mini.volt.left.sh

echo "a.speed:1100" > /dev/ttyUSB0
echo "a.turn:fwd" > /dev/ttyUSB0
echo "b.speed:1000" > /dev/ttyUSB0
echo "b.turn:rev" > /dev/ttyUSB0
echo "c.speed:1100" > /dev/ttyUSB0
echo "c.turn:fwd" > /dev/ttyUSB0
echo "d.speed:1000" > /dev/ttyUSB0
echo "d.turn:rev" > /dev/ttyUSB0
echo "run" > /dev/ttyUSB0
sleep 0.2

echo "a.speed:22000" > /dev/ttyUSB0
echo "a.turn:fwd" > /dev/ttyUSB0
echo "b.speed:20000" > /dev/ttyUSB0
echo "b.turn:rev" > /dev/ttyUSB0
echo "c.speed:22000" > /dev/ttyUSB0
echo "c.turn:fwd" > /dev/ttyUSB0
echo "d.speed:20000" > /dev/ttyUSB0
echo "d.turn:rev" > /dev/ttyUSB0
echo "run" > /dev/ttyUSB0
sleep 0.2

echo "a.speed:44000" > /dev/ttyUSB0
echo "a.turn:fwd" > /dev/ttyUSB0
echo "b.speed:40000" > /dev/ttyUSB0
echo "b.turn:rev" > /dev/ttyUSB0
echo "c.speed:44000" > /dev/ttyUSB0
echo "c.turn:fwd" > /dev/ttyUSB0
echo "d.speed:40000" > /dev/ttyUSB0
echo "d.turn:rev" > /dev/ttyUSB0
echo "run" > /dev/ttyUSB0


