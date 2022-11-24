/**
 * Module to inspect device tree from the kernel
 */

#include <linux/moduleparam.h>
#include <linux/module.h>
#include <linux/of.h>

#define PATH_DEFAULT  "/"
static char *path = PATH_DEFAULT;

module_param(path, charp, S_IRUSR | S_IWUSR);
MODULE_PARM_DESC(path, "a device tree pathname " \
                 "(default is \"" PATH_DEFAULT "\")");

/*
 * Local functions
 */
static void print_property_u32(struct device_node *node, const cahr * name){
    u32 val32;
    if(of_property_read_u32(node, name, &val32) == 0){
        pr_info(" \%s = %d\n", name, val32);
    }
}
