CXX=g++
CXXFLAGS= -Wall -g -O2 -std=c++11
CXX_OPTS= -Wall -g -O2 -std=c++11

LDFLAGS := -pthread 
LDFLAGS += -lboost_iostreams
LDFLAGS += -lboost_system


INSTALL=install

PROG=mpu6050.service
TURN=turn.until

%.o: %.c                                                                         
	$(CXX) $(CXXFLAGS) $(CXX_OPTS) $< -o $@ 


all: $(PROG).o 
	$(CXX)  $(CXXFLAGS) -o $(PROG) \
		main.cpp \
                $(LDFLAGS) \
		MotionSensor/libMotionSensor.a \
		libs/libI2Cdev.a
	$(CXX)  $(CXXFLAGS) -o $(TURN) \
		$(LDFLAGS) turn.cpp 

$(PROG).o: MotionSensor/libMotionSensor.a libs/libI2Cdev.a

MotionSensor/libMotionSensor.a:
	$(MAKE) -C MotionSensor/ 

libs/libI2Cdev.a:
	$(MAKE) -C libs/I2Cdev

install1:
	$(INSTALL) -m 755 $(PROG) $(DESTDIR)/usr/local/bin/

clean:
	cd MotionSensor && $(MAKE) clean
	cd libs/I2Cdev && $(MAKE) clean
	rm -rf *.o *~ *.mod
	rm -rf $(PROG)
