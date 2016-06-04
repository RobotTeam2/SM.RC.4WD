#!/bin/bash
echo "a.speed:60000" > /dev/ttyUSB0
echo "a.turn:fwd" > /dev/ttyUSB0
echo "b.speed:60000" > /dev/ttyUSB0
echo "b.turn:fwd" > /dev/ttyUSB0
echo "c.speed:60000" > /dev/ttyUSB0
echo "c.turn:fwd" > /dev/ttyUSB0
echo "d.speed:60000" > /dev/ttyUSB0
echo "d.turn:fwd" > /dev/ttyUSB0

echo "a.cmd.volt:0.kvaldec" > /dev/ttyUSB0
echo "b.cmd.volt:0.kvaldec" > /dev/ttyUSB0
echo "c.cmd.volt:0.kvaldec" > /dev/ttyUSB0
echo "d.cmd.volt:0.kvaldec" > /dev/ttyUSB0

echo "run" > /dev/ttyUSB0

