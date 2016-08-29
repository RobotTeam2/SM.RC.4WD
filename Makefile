PWD := $(shell pwd)
all:
	make -C car
	make -C mpu
install:
	sudo systemctl enable $(PWD)/mpu.service
	sudo systemctl enable $(PWD)/car.service
	sudo systemctl enable $(PWD)/ble.service
	sudo systemctl enable $(PWD)/4wd.wifi.service
	
