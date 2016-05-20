#!/bin/bash
stty -F /dev/ttyUSB0 9600
echo "a.s:10000" >/dev/ttyUSB0
echo "a.t:fwd" >/dev/ttyUSB0
echo "b.s:10000" >/dev/ttyUSB0
echo "b.t:fwd" >/dev/ttyUSB0
echo "c.s:10000" >/dev/ttyUSB0
echo "c.t:fwd" >/dev/ttyUSB0
echo "d.s:10000" >/dev/ttyUSB0
echo "d.t:fwd" >/dev/ttyUSB0
echo "run" >/dev/ttyUSB0
