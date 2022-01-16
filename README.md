## kernel module
### kmtest
a simple module example

### more interesting example
Applications use an API to communicate with kernel space memory. Most common way is to create device file.

lkmexam.ko

```shell
dmesg
[121123.558136] lkm_example module loaded with device major number 508

$ file /dev/lkmexam
/dev/lkmexam: character special (508/0)
# create a device

$ ls -l /dev/lkmexam                 
  crw-r--r-- 1 root root 508, 0 1月  16 12:21 /dev/lkmexam


```

