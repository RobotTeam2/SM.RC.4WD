#!/bin/bash
sudo apt-get install cmake libopencv-dev libusb-1.0-0-dev

rm -rf libuvc
# build libuvc
git clone https://github.com/ktossell/libuvc
cd libuvc
mkdir build
cd build
cmake ..
make && sudo make install

cd ../../
mkdir object
cd object
cmake ..
make

