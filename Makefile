PWD := $(shell pwd)
all:
	make -C service
	make -C MPU6050
install:
	sudo systemctl enable $(PWD)/mpu.service
	sudo systemctl enable $(PWD)/car.service
	
