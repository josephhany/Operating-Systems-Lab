#KBUILD_EXTRA_SYMBOLS := /home/vil/csce-3402-os-lab/Module.symvers

obj-m += cipher.o

all:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) modules

clean:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) clean
