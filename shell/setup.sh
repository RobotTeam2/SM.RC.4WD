#!/bin/bash
HOME=`dirname $0`/..
echo $HOME

stty -F /dev/ttyUSB0 115200 \
-iuclc -ixany -imaxbel -iutf8 -opost -olcuc -ocrnl -onlcr \
-onocr -onlret -ofill -ofdel nl0 cr0 tab0 bs0 vt0 ff0 -isig \
-icanon -iexten -echo -echoe -echok -echonl -noflsh -xcase \
-tostop -echoprt -echoctl -echoke
stty -F /dev/ttyUSB0 raw
stty -F /dev/ttyUSB0 -echo -echoe -echok
stty -F /dev/ttyUSB0
cat /dev/ttyUSB0 &
$HOME/MPU6050/mpu6050.service &
