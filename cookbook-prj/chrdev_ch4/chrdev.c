/* 
 * chrdev
 */

#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/fs.h>
#include <linux/uaccess.h>

#include "chrdev.h"

/*
 * Local variables
 */

static dev_t chrdev_devt;
static struct class *chrdev_class;

struct chrdev_device chrdev_array[MAX_DEVICES];

/*
 * Methods
 */
static ssize_t chrdev_read(struct file *filp,
                           char __user *buf,
                           size_t count,
                           loff_t *ppos){
    struct chrdev_device *chrdev = filp->private_data;
    int ret;

    dev_info(chrdev->dev,
             "should read %ld bytes (*ppos=%lld)\n",
             count,
             *ppos);
    /* check for end-of-buffer */
    if (*ppos + count >= BUF_LEN)
        count = BUF_LEN - *ppos;

    /* Return data to the user space */
    ret = copy_to_user(buf, chrdev->buf + *ppos, count);
    if(ret < 0)
        return -EFAULT;

    *ppos += count;
    dev_info(chrdev->dev, "return %ld bytes (*ppos=%lld)\n", count, *ppos);

    return count;
}

static ssize_t chrdev_write(struct file *filp,
                            const char __user *buf,
                            size_t count,
                            loff_t *ppos){
    struct chrdev_device *chrdev = filp->private_data;
    int ret;

    dev_info(chrdev->dev,
             "should write %ld bytes (*ppos=%lld)\n",
             count,
             *ppos);

    if(chrdev->read_only)
        return -EINVAL;

    /* check for end-of buffer */
    if (*ppos + count >= BUF_LEN)
        count = BUF_LEN - *ppos;

    /* Get data from the user space */
    ret = copy_from_user(chrdev->buf + *ppos, buf, count);
    if(ret < 0)
        return -EFAULT;

    *ppos += count;
    dev_info(chrdev->dev, "got %ld bytes (*ppos=%lld)\n", count, *ppos);

    return count;
}

static int chrdev_open(struct inode *inode,
                       struct file *filp){
    struct chrdev_device *chrdev =
        container_of(inode->i_cdev,
                     struct chrdev_device,
                     cdev);
    filp->private_data = chrdev;
    kobject_get(&chrdev->dev->kobj);

    dev_info(chrdev->dev,
             "chrdev (id=%d) opened\n",
             chrdev->id);

    return 0;
                                                
}
static int chrdev_release(struct inode *inode,
                          struct file *filp){
    struct chrdev_device *chrdev =
        container_of(inode->i_cdev,
                     struct chrdev_device,
                     cdev);
    kobject_put(&chrdev->dev->kobj);
    filp->private_data = NULL;

    dev_info(chrdev->dev, "chrdev (id=%d) released\n", chrdev->id);

    return 0;
}
static const struct file_operations chrdev_fops =
    {
     .owner =  THIS_MODULE,
     .read  =  chrdev_read,
     .write =  chrdev_write,
     .open  =  chrdev_open,
     .release = chrdev_release
    };

/*
 * Exported functions
 */
int chrdev_device_register(const char *label,
                           unsigned int id,
                           unsigned int read_only,
                           struct module *owner,
                           struct device *parent){
    struct chrdev_device *chrdev;
    dev_t devt;
    int ret;

    /* First check if we are allocating a valid device ... */
    if(id >= MAX_DEVICES){
        pr_err("invalid id %d\n", id);
        return -EINVAL;
    }
    chrdev = &chrdev_array[id];

    /* ... then check if we have not busy id */
    if(chrdev->busy){
        pr_err("id %id \n is busy", id);
        return -EBUSY;
    }

    /* create the device and initialize its data */
    cdev_init(&chrdev->cdev, &chrdev_fops);
    chrdev->cdev.owner = owner;

    devt = MKDEV(MAJOR(chrdev_devt), id);
    ret = cdev_add(&chrdev->cdev, devt, 1);

    if(ret){
        pr_err("failed to add char device %s at %d:%d\n",
               label,
               MAJOR(chrdev_devt),
               id);
        return ret;
    }

    chrdev->dev = device_create(chrdev_class,
                                parent,
                                devt,
                                chrdev,
                                "%s@%d",
                                label,
                                id);
    if(IS_ERR(chrdev->dev)){
        pr_err("unable to create device %s\n", label);
        ret = PTR_ERR(chrdev->dev);
        goto del_cdev;
    }
    dev_set_drvdata(chrdev->dev, chrdev);

    /* Init the chrdev data */
    chrdev->id = id;
    chrdev->read_only = read_only;
    chrdev->busy = 1;
    strncpy(chrdev->label, label, NAME_LEN);
    memset(chrdev->buf, 0, BUF_LEN);

    dev_info(chrdev->dev, "chrdev %s with id %d added\n", label, id);
    return 0;
 del_cdev:
    cdev_del(&chrdev->cdev);

    return ret;
}

EXPORT_SYMBOL(chrdev_device_register);

int chrdev_device_unregister(const char *label, unsigned int id){
    struct chrdev_device *chrdev;

    /* First check if we are deallocating a valid device ... */
    if(id >= MAX_DEVICES){
        pr_err("invalid id %d\n", id);
        return -EINVAL;
    }
    chrdev = &chrdev_array[id];

    /* ... then check if device is actually allocated */
    if(!chrdev->busy || strcmp(chrdev->label, label)){
        pr_err("id %d is not busy or label %s is not known\n",
               id,
               label);
        return -EINVAL;
    }

    /* Deinit the chrdev data */
    chrdev->id = 0;
    chrdev->busy = 0;

    dev_info(chrdev->dev,
             "chrdev %s with id %d removed",
             label, id);

    /* Dealocate the device */
    device_destroy(chrdev_class, chrdev->dev->devt);
    cdev_del(&chrdev->cdev);

    return 0;

}
EXPORT_SYMBOL(chrdev_device_unregister);

/*
 * Module stuff
 */


static int __init chrdev_init(void){
    int ret;

    /* Create the new class for the chrdev devices */
    chrdev_class = class_create(THIS_MODULE, "chrdev");
    if(!chrdev_class){
        pr_err("chrdev: failed to allocae class\n");
        return -ENOMEM;
    }

    /* Allocate a region for character devices */
    ret = alloc_chrdev_region(&chrdev_devt, 0, MAX_DEVICES, "chrdev");
    if(ret < 0){
        pr_err("failed to allocate char device region\n");
        goto remove_class;
    }

    pr_info("got major %d\n", MAJOR(chrdev_devt));
    return 0;

 remove_class:
    class_destroy(chrdev_class);

    return ret;
}

static void __exit chrdev_exit(void){
    unregister_chrdev_region(chrdev_devt, MAX_DEVICES);
    class_destroy(chrdev_class);
}

module_init(chrdev_init);
module_exit(chrdev_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Rodolfo Yango");
MODULE_DESCRIPTION("chrdev");

