#!/bin/bash

echo "a.cmd.param:200.maxspeed" > /dev/ttyUSB0
echo "b.cmd.param:200.maxspeed" > /dev/ttyUSB0
echo "c.cmd.param:200.maxspeed" > /dev/ttyUSB0
echo "d.cmd.param:200.maxspeed" > /dev/ttyUSB0

echo "a.speed:30000" > /dev/ttyUSB0
echo "a.turn:fwd" > /dev/ttyUSB0
echo "b.speed:5000" > /dev/ttyUSB0
echo "b.turn:fwd" > /dev/ttyUSB0
echo "c.speed:30000" > /dev/ttyUSB0
echo "c.turn:fwd" > /dev/ttyUSB0
echo "d.speed:5000" > /dev/ttyUSB0
echo "d.turn:fwd" > /dev/ttyUSB0
echo "run" > /dev/ttyUSB0