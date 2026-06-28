#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/fs.h>
#include <linux/cdev.h>
#include <linux/init.h>
#include <linux/uaccess.h>
#include <linux/device.h>
#include <linux/ioctl.h>
#include <linux/mutex.h>
#include <linux/wait.h>
#include <linux/poll.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Pulkit");
MODULE_VERSION("0.9");

#define DEVICE_NAME "mychardev"
#define CLASS_NAME  "mychardev_class"
#define BUFFER_SIZE 1024

typedef struct
{
    uint64_t bytes_written;
    uint64_t bytes_read;
    uint64_t read_calls;
    uint64_t write_calls;
    uint64_t dropped_bytes;
} DriverStats;

typedef struct
{
    char buffer[BUFFER_SIZE];
    size_t head;
    size_t tail;
    size_t count;
} CircularBuffer;

#define SET_VALUE       _IOW('a', 1, int32_t *)
#define GET_VALUE       _IOR('a', 2, int32_t *)
#define CLEAR_BUFFER    _IO('a', 3)
#define GET_STATS       _IOR('a', 4, DriverStats)

static dev_t dev_num;
static struct cdev my_cdev;
static struct class *my_class = NULL;
static struct device *my_device = NULL;

static CircularBuffer cb;
static DriverStats stats = {0};
static int stored_value = 0;
static struct mutex my_mutex;

static DECLARE_WAIT_QUEUE_HEAD(read_queue);

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
    size_t space_left, to_copy, chunk1, chunk2;

    if(mutex_lock_interruptible(&my_mutex))
    {
        return -ERESTARTSYS;
    }

    stats.write_calls++;

    space_left = BUFFER_SIZE - cb.count;
    if(space_left == 0)
    {
        stats.dropped_bytes += count;
        mutex_unlock(&my_mutex);
        return -ENOSPC;
    }

    to_copy = (count > space_left) ? space_left : count;

    if(count > space_left)
    {
        stats.dropped_bytes += (count - space_left);
    }

    chunk1 = (to_copy > (BUFFER_SIZE - cb.head)) ? (BUFFER_SIZE - cb.head) : to_copy;
    chunk2 = to_copy - chunk1;

    if(copy_from_user(cb.buffer + cb.head, buf, chunk1) != 0)
    {
        mutex_unlock(&my_mutex);
        printk(KERN_ALERT "mychardev: Failed to copy data from user\n");
        return -EFAULT;
    }

    if(chunk2 > 0)
    {
        if(copy_from_user(cb.buffer, buf + chunk1, chunk2) != 0)
        {
            mutex_unlock(&my_mutex);
            printk(KERN_ALERT "mychardev: Failed to copy data from user\n");
            return -EFAULT;
        }
    }

    cb.head = (cb.head + to_copy) % BUFFER_SIZE;
    cb.count += to_copy;
    stats.bytes_written += to_copy;

    mutex_unlock(&my_mutex);

    wake_up_interruptible(&read_queue);
    printk(KERN_INFO "mychardev: Received %zu bytes from user\n", to_copy);

    return to_copy;
}

static ssize_t device_read(struct file *file, char __user *buf, size_t count, loff_t *ppos)
{
    size_t to_read, chunk1, chunk2;

    if(wait_event_interruptible(read_queue, cb.count > 0))
    {
        return -ERESTARTSYS;
    }

    if(mutex_lock_interruptible(&my_mutex))
    {
        return -ERESTARTSYS;
    }

    stats.read_calls++;

    to_read = (count > cb.count) ? cb.count : count;
    chunk1 = (to_read > (BUFFER_SIZE - cb.tail)) ? (BUFFER_SIZE - cb.tail) : to_read;
    chunk2 = to_read - chunk1;

    if(copy_to_user(buf, cb.buffer + cb.tail, chunk1) != 0)
    {
        mutex_unlock(&my_mutex);
        printk(KERN_ALERT "mychardev: Failed to copy data to user\n");
        return -EFAULT;
    }

    if(chunk2 > 0)
    {
        if(copy_to_user(buf + chunk1, cb.buffer, chunk2) != 0)
        {
            mutex_unlock(&my_mutex);
            printk(KERN_ALERT "mychardev: Failed to copy data to user\n");
            return -EFAULT;
        }
    }

    cb.tail = (cb.tail + to_read) % BUFFER_SIZE;
    cb.count -= to_read;
    stats.bytes_read += to_read;
    mutex_unlock(&my_mutex);
    printk(KERN_INFO "mychardev: Sent %zu bytes to user\n", to_read);
    return to_read;
}

static long device_ioctl(struct file *file, unsigned int cmd, unsigned long arg)
{
    int32_t value;
    long ret = 0;

    if(mutex_lock_interruptible(&my_mutex))
    {
        return -ERESTARTSYS;
    }

    printk(KERN_INFO "mychardev: Received IOCTL = %u | Expected GET_STATS = %lu\n", cmd, (unsigned long)GET_STATS);

    switch(cmd)
    {
        case SET_VALUE:
            if(copy_from_user(&value, (int32_t __user *)arg, sizeof(value)) != 0)
            {
                ret = -EFAULT;
                break;
            }
            stored_value = value;
            printk(KERN_INFO "mychardev: IOCTL SET_VALUE called. Stored %d\n", stored_value);
            break;

        case GET_VALUE:
            if(copy_to_user((int32_t __user *)arg, &stored_value, sizeof(stored_value)) != 0)
            {
                ret = -EFAULT;
                break;
            }
            printk(KERN_INFO "mychardev: IOCTL GET_VALUE called. Sent %d\n", stored_value);
            break;

        case CLEAR_BUFFER:
            memset(cb.buffer, 0, BUFFER_SIZE);
            cb.head = 0;
            cb.tail = 0;
            cb.count = 0;
            printk(KERN_INFO "mychardev: IOCTL CLEAR_BUFFER called\n");
            break;

        case GET_STATS:
            if(copy_to_user((DriverStats __user *)arg, &stats, sizeof(stats)) != 0)
            {
                ret = -EFAULT;
                break;
            }
            printk(KERN_INFO "mychardev: IOCTL GET_STATS called\n");
            break;

        default:
            printk(KERN_WARNING "mychardev: Invalid IOCTL command received\n");
            ret = -EINVAL;
    }

    mutex_unlock(&my_mutex);

    return ret;
}

static __poll_t device_poll(struct file *file, poll_table *wait)
{
    __poll_t mask = 0;
    poll_wait(file, &read_queue, wait);

    if(mutex_lock_interruptible(&my_mutex))
    {
        return 0;
    }

    if(cb.count > 0)
    {
        mask |= (POLLIN | POLLRDNORM);
    }

    mutex_unlock(&my_mutex);

    return mask;
}

static struct file_operations fops = {
    .owner = THIS_MODULE,
    .open = device_open,
    .release = device_release,
    .read = device_read,
    .write = device_write,
    .unlocked_ioctl = device_ioctl,
    .poll = device_poll,
};

static int __init chardev_init(void)
{
    int result;

    cb.head = 0;
    cb.tail = 0;
    cb.count = 0;
    memset(cb.buffer, 0, BUFFER_SIZE);

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

    mutex_init(&my_mutex);

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