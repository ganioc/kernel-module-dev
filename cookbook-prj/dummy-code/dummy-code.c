/**
 * Dummy code
 *
 */

#include <linux/module.h>

// #define pr_fmt(fmt) "%s:%s: " fmt,KBUILD_MODNAME,__func__


static int __init dummy_code_init(void){
    //printk(KERNEL_IFNO "dummy-code loaded\n");
    pr_info("dummy-code loaded\n");
    return 0;
}

static void __exit dummy_code_exit(void){
    //printk(KERNEL_IFNO "dummy-code unloaded\n");
    pr_info("dummy-code unloaded\n");
}

module_init(dummy_code_init);
module_exit(dummy_code_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Rodolfo Yang");
MODULE_DESCRIPTION("Dummy Code");


