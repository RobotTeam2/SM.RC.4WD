#!/bin/bash
./subdrift.forward.sh
sleep 8
./subdrift.forward.sh
sleep 0.5
./subdrift.lock.left.sh
sleep 0.5
#./subdrift.free.left.sh
#sleep 0.2
#./subdrift.lock.left.sh
#sleep 0.2
#./subdrift.free.left.sh
#sleep 0.2
#./subdrift.lock.left.sh
#sleep 0.2
#./subdrift.free.left.sh



sleep 1
./subdrift.stop.sh


