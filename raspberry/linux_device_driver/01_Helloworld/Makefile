obj-m := helloworld.o 
KERNEL_DIR ?= $(HOME)/linux_rpi3/linux
all:
	make -C /opt/b2qt/3.1.7/sysroots/cortexa7t2hf-neon-vfpv4-poky-linux-gnueabi/lib \
	ARCH=arm CROSS_COMPILE=arm-linux-gnueabihf- \
	M=$(PWD) modules
clean:
	make -C $(KERNEL_DIR) \
	ARCH=arm CROSS_COMPILE=arm-linux-gnueabihf- \
	M=$(PWD) clean
deploy:
	scp *.ko root@10.0.0.10:/home/pi