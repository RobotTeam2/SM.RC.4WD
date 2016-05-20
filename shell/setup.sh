#!/bin/bash
stty -F /dev/ttyUSB0 115200 \
-iuclc -ixany -imaxbel -iutf8 -opost -olcuc -ocrnl -onlcr \
-onocr -onlret -ofill -ofdel nl0 cr0 tab0 bs0 vt0 ff0 -isig \
-icanon -iexten -echo -echoe -echok -echonl -noflsh -xcase \
-tostop -echoprt -echoctl -echoke
#stty /dev/ttyUSB0

