#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/fs.h>

static dev_t my_device_nbr;

static int __init hello_init(void)
{
    int retval;

    printk(KERN_INFO "Hello from my first driver\n");

    retval = alloc_chrdev_region(&my_device_nbr, 0, 1, "my_hello_dev");
    if(retval < 0)
    {
        printk(KERN_ERR "Failed to allocate major/minor numbers\n");
        return retval;
    }

    printk(KERN_INFO "Major Number: %d, Minor Number: %d\n", MAJOR(my_device_nbr), MINOR(my_device_nbr));

    return 0;
}

static void __exit hello_exit(void)
{
    unregister_chrdev_region(my_device_nbr, 1);

    printk(KERN_INFO "Driver unloaded\n");
}

module_init(hello_init);
module_exit(hello_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Pulkit");
MODULE_DESCRIPTION("A simple Hello World Linux Kernel Module");