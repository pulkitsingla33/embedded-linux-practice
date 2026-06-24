#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/fs.h>
#include <linux/cdev.h>
#include <linux/init.h>
#include <linux/uaccess.h>
#include <linux/device.h>
#include <linux/ioctl.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Pulkit");
MODULE_VERSION("0.4");

#define DEVICE_NAME "mychardev"
#define CLASS_NAME  "mychardev_class"
#define BUFFER_SIZE 256

#define SET_VALUE       _IOW('a', 1, int32_t *)
#define GET_VALUE       _IOR('a', 2, int32_t *)
#define CLEAR_BUFFER    _IO('a', 3)

static dev_t dev_num;
static struct cdev my_cdev;
static struct class *my_class = NULL;
static struct device *my_device = NULL;

static char device_buffer[BUFFER_SIZE];
static size_t buffer_data_size = 0;
static int stored_value = 0;

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

static ssize_t device_write(struct file *file, const char __user *buf, size_t count, loff_t *ppos)
{
    size_t to_copy;

    to_copy = (count > BUFFER_SIZE) ? (BUFFER_SIZE - 1) : count;
    memset(device_buffer, 0, BUFFER_SIZE);

    if(copy_from_user(device_buffer, buf, to_copy) != 0)
    {
        printk(KERN_ALERT "mychardev: Failed to copy data from user\n");
        return -EFAULT;
    }

    buffer_data_size = to_copy;
    printk(KERN_INFO "mychardev: Received %zu bytes from user\n", to_copy);

    return to_copy;
}

static ssize_t device_read(struct file *file, char __user *buf, size_t count, loff_t *ppos)
{
    if(*ppos >= buffer_data_size)   return 0;

    if(count > (buffer_data_size - *ppos))  count = buffer_data_size - *ppos;

    if(copy_to_user(buf, device_buffer + *ppos, count) != 0)
    {
        printk(KERN_ALERT "mychardev: Failed to copy data to user\n");
        return -EFAULT;
    }

    *ppos += count;

    printk(KERN_INFO "mychardev: Sent %zu bytes to user\n", count);
    return count;
}

static long device_ioctl(struct file *file, unsigned int cmd, unsigned long arg)
{
    int32_t value;

    switch(cmd)
    {
        case SET_VALUE:
            if(copy_from_user(&value, (int32_t __user *)arg, sizeof(value)) != 0)
            {
                return -EFAULT;
            }
            stored_value = value;
            printk(KERN_INFO "mychardev: IOCTL SET_VALUE called. Stored %d\n", stored_value);
            break;

        case GET_VALUE:
            if(copy_to_user((int32_t __user *)arg, &stored_value, sizeof(stored_value)) != 0)
            {
                return -EFAULT;
            }
            printk(KERN_INFO "mychardev: IOCTL GET_VALUE called. Sent %d\n", stored_value);
            break;

        case CLEAR_BUFFER:
            memset(device_buffer, 0, BUFFER_SIZE);
            buffer_data_size = 0;
            printk(KERN_INFO "mychardev: IOCTL CLEAR_BUFFER called\n");
            break;

        default:
            printk(KERN_WARNING "mychardev: Invalid IOCTL command received\n");
            return -EINVAL;
    }

    return 0;
}

static struct file_operations fops = {
    .owner = THIS_MODULE,
    .open = device_open,
    .release = device_release,
    .read = device_read,
    .write = device_write,
    .unlocked_ioctl = device_ioctl,
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

    my_class = class_create(CLASS_NAME);
    if(IS_ERR(my_class))
    {
        cdev_del(&my_cdev);
        unregister_chrdev_region(dev_num, 1);
        printk(KERN_ALERT "mychardev: Failed to create device class\n");
        return PTR_ERR(my_class);
    }

    my_device = device_create(my_class, NULL, dev_num, NULL, DEVICE_NAME);
    if(IS_ERR(my_device))
    {
        class_destroy(my_class);
        cdev_del(&my_cdev);
        unregister_chrdev_region(dev_num, 1);
        printk(KERN_ALERT "mychardev: Failed to create device file\n");
        return PTR_ERR(my_device);
    }

    printk(KERN_INFO "mychardev: Initialized dynamically\n");
    return 0;
}

static void __exit chardev_exit(void)
{
    device_destroy(my_class, dev_num);
    class_destroy(my_class);
    cdev_del(&my_cdev);
    unregister_chrdev_region(dev_num, 1);
    printk(KERN_INFO "mychardev: Cleaned up successfully\n");
}

module_init(chardev_init);
module_exit(chardev_exit);