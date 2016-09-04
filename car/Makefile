SRC     := main.cpp
SRC     += ble_ws.entry.cpp
SRC     += mpu.entry.cpp
SRC     += car.entry.cpp

CFLAGS  := -std=c++14  -pthread 
LDFLAGS := -lboost_iostreams
LDFLAGS += -lboost_system
all:
	g++ $(CFLAGS) $(SRC) $(LDFLAGS) -o sm.rc.4wd.cmd
