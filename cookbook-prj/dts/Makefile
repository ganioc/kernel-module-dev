
KERNELDIR := /lib/modules/$(shell uname -r)/build

obj-m := dt-data.o

PWD :=$(shell pwd)

default:
	$(MAKE) -C $(KERNELDIR) M=$(PWD)
clean:
	rm -rf .tmp_versions Module.symvers *.mod.c *.o *.ko .*.cmd Module.markers modules.order

#  mknod chrdev c 237 0
#  sudo mknod /dev/chrdev c 237 0
#
#
#


