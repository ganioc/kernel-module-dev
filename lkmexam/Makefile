obj-m += lkmexam.o

all:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) modules

clean:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) clean

test:
	# put - in fromnt of rmmod , to ignore an error if module not loaded,
	-sudo rmmod lkmexam
	# Clear the kernel log without echo
	sudo dmesg -C
	# Insert the module
	sudo insmod lkmexam.ko
	# Display the kernel log
	dmesg

