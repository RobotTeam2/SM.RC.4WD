#!/bin/bash
stty -F /dev/ttyUSB0 9600
echo "a.s:10000" >/dev/ttyUSB0
echo "a.t:fwd" >/dev/ttyUSB0
echo "run" >/dev/ttyUSB0
