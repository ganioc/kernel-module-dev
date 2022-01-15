#include <linux/module.h>
#include <linux/slab.h>
#include <linux/init.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Yango");
MODULE_DESCRIPTION("A simple linux module");
MODULE_VERSION("0.0.1");


static int leak_func(void){
  char *p;
  char mark[] = "memory leak test";

  p = kmalloc(sizeof(mark), GFP_KERNEL);

  if(!p){
    printk("kmleak can't allocate memory\n");
    return -ENOMEM;
  }

  printk(KERN_INFO "pointer to the allocated memory:%p\n", p);

  kfree(p);

  return 0;
}

static int __init kmleak_init(void){
  leak_func();
  return 0;
}

static void __exit kmleak_exit(void){
  printk(KERN_INFO "Goodbye kmtest\n");
  return;
}

module_init(kmleak_init);
module_exit(kmleak_exit);

