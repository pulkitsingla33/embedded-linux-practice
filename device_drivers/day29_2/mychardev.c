#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/fs.h>
#include <linux/cdev.h>
#include <linux/init.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Pulkit");

#define DEVICE_NAME "mychardev"

static dev_t dev_num;
static struct cdev my_cdev;

static int device_open(struct inode *inode, struct file *file)
{
    printk(KERN_INFO "mychardev: Device opened successfully\n");
    return 0;
}

static int device_release(struct inode *inode, struct file *file)
{
    printk(KERN_INFO "mychardev: Device closed successfully\n");
    return 0;
}

static struct file_operations fops = {
    .owner = THIS_MODULE,
    .open = device_open,
    .release = device_release,
};

static int __init chardev_init(void)
{
    int result;

    result = alloc_chrdev_region(&dev_num, 0, 1, DEVICE_NAME);
    if(result < 0)
    {
        printk(KERN_ALERT "mychardev: Failed to allocate major numer\n");
        return result;
    }

    cdev_init(&my_cdev, &fops);
    my_cdev.owner = THIS_MODULE;

    result = cdev_add(&my_cdev, dev_num, 1);
    if(result < 0)
    {
        unregister_chrdev_region(dev_num, 1);
        printk(KERN_ALERT "mychardev: Failed to add cdev\n");
        return result;
    }

    printk(KERN_INFO "Character device registered\n");
    printk(KERN_INFO "Major = %d\n", MAJOR(dev_num));
    printk(KERN_INFO "Minor = %d\n", MINOR(dev_num));

    return 0;
}

static void __exit chardev_exit(void)
{
    cdev_del(&my_cdev);
    unregister_chrdev_region(dev_num, 1);
    printk(KERN_INFO "Character device unregistered\n");
}

module_init(chardev_init);
module_exit(chardev_exit);