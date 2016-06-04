#!/bin/bash
./drift.forward.sh
sleep 0.8
./drift.forward.sh
sleep 0.5

echo "a.cmd.volt:64.kvalrun" > /dev/ttyUSB0
echo "b.cmd.volt:64.kvalrun" > /dev/ttyUSB0
echo "c.cmd.volt:64.kvalrun" > /dev/ttyUSB0
echo "d.cmd.volt:64.kvalrun" > /dev/ttyUSB0
echo "a.speed:30000" > /dev/ttyUSB0
echo "a.turn:rev" > /dev/ttyUSB0
echo "c.speed:30000" > /dev/ttyUSB0
echo "c.turn:rev" > /dev/ttyUSB0
echo "run" > /dev/ttyUSB0

sleep 1
echo "a.cmd.volt:48.kvalrun" > /dev/ttyUSB0
echo "b.cmd.volt:48.kvalrun" > /dev/ttyUSB0
echo "c.cmd.volt:48.kvalrun" > /dev/ttyUSB0
echo "d.cmd.volt:48.kvalrun" > /dev/ttyUSB0
