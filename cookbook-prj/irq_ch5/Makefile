
KERNELDIR := /lib/modules/$(shell uname -r)/build

# ifndef KERNEL_DIR
# $(error KERNEL_DIR must be set in the command line)
# endif

# PWD := $(shell pwd)
# ARCH ?= arm64
# CROSS_COMPILE ?= aarch64-linux-gnu-

# This specifies the kernel module to be compiled
obj-m += dummy-irq.o

PWD :=$(shell pwd)

default:
	$(MAKE) -C $(KERNELDIR) M=$(PWD)
clean:
	rm -rf .tmp_versions Module.symvers *.mod.c *.o *.ko .*.cmd Module.markers modules.order
