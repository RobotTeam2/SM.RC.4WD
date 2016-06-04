#!/bin/bash
echo "a.cmd.param:128.maxspeed" > /dev/ttyUSB0
echo "b.cmd.param:128.maxspeed" > /dev/ttyUSB0
echo "c.cmd.param:128.maxspeed" > /dev/ttyUSB0
echo "d.cmd.param:128.maxspeed" > /dev/ttyUSB0


echo "a.speed:40000" > /dev/ttyUSB0
echo "a.turn:fwd" > /dev/ttyUSB0
echo "b.speed:40000" > /dev/ttyUSB0
echo "b.turn:fwd" > /dev/ttyUSB0
echo "c.speed:40000" > /dev/ttyUSB0
echo "c.turn:fwd" > /dev/ttyUSB0
echo "d.speed:40000" > /dev/ttyUSB0
echo "d.turn:fwd" > /dev/ttyUSB0

echo "a.cmd.param:0.kvaldec" > /dev/ttyUSB0
echo "b.cmd.param:0.kvaldec" > /dev/ttyUSB0
echo "c.cmd.param:0.kvaldec" > /dev/ttyUSB0
echo "d.cmd.param:0.kvaldec" > /dev/ttyUSB0

echo "run" > /dev/ttyUSB0

