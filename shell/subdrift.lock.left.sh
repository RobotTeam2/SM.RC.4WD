#!/bin/bash
echo "a.cmd.param:64.kvalrun" > /dev/ttyUSB0
echo "b.cmd.param:64.kvalrun" > /dev/ttyUSB0
echo "c.cmd.param:64.kvalrun" > /dev/ttyUSB0
echo "d.cmd.param:64.kvalrun" > /dev/ttyUSB0


echo "a.speed:40000" > /dev/ttyUSB0
echo "a.turn:rev" > /dev/ttyUSB0
echo "b.speed:40000" > /dev/ttyUSB0
echo "b.turn:fwd" > /dev/ttyUSB0
echo "c.speed:40000" > /dev/ttyUSB0
echo "c.turn:rev" > /dev/ttyUSB0
echo "d.speed:40000" > /dev/ttyUSB0
echo "d.turn:fwd" > /dev/ttyUSB0
echo "run" > /dev/ttyUSB0
