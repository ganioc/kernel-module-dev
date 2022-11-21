
KERNELDIR := /lib/modules/$(shell uname -r)/build

obj-m := module_par.o

PWD :=$(shell pwd)

default:
	$(MAKE) -C $(KERNELDIR) M=$(PWD)
clean:
	rm -rf .tmp_versions Module.symvers *.mod.c *.o *.ko .*.cmd Module.markers modules.order

