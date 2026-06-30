#include <linux/module.h>
#include <linux/init.h>
#include <linux/fs.h>
#include <linux/cdev.h>
#include <linux/uaccess.h>
#include <linux/mutex.h>
#include <linux/wait.h>
#include <linux/device.h>
#include <linux/slab.h>
#include <linux/kthread.h>
#include <linux/delay.h>
#include <linux/random.h>
#include <linux/jiffies.h>
#include <linux/timekeeping.h>
#include <linux/time.h>

#include "tempsensor_ioctl.h"

#define DRIVER_NAME "tempsensor"
#define CLASS_NAME "tempsensor_class"
#define BUFFER_SIZE 256

struct tempsensor_dev
{
    struct cdev cdev;
    char buffer[BUFFER_SIZE];
    size_t data_len;
    bool data_ready;
    struct mutex lock;

    wait_queue_head_t wait_queue;
    struct task_struct *thread;

    unsigned int sampling_interval;
    wait_queue_head_t thread_wait;

    SensorStats stats;
};

static dev_t dev_num;
static struct class *tempsensor_class = NULL;
static struct tempsensor_dev *ts_device = NULL;

static int tempsensor_thread(void *data)
{
    struct tempsensor_dev *dev = (struct tempsensor_dev *)data;
    u32 temp, humidity, pressure;
    unsigned int current_interval;

    struct timespec64 ts;
    struct tm tm;

    pr_info("%s: Sensor thread started\n", DRIVER_NAME);

    while(!kthread_should_stop())
    {
        temp = 20 + (get_random_u32() % 15);
        humidity = 50 + (get_random_u32() % 30);
        pressure = 1000 + (get_random_u32() % 20);

        ktime_get_real_ts64(&ts);
        time64_to_tm(ts.tv_sec, 0, &tm);

        mutex_lock(&dev->lock);
        
        dev->data_len = snprintf(dev->buffer, BUFFER_SIZE, "Timestamp: %ld-%02d-%02d %02d:%02d:%02d UTC\nTemp: %u\n Humidity: %u\n Pressure: %u\n",1900+tm.tm_year, tm.tm_mon+1, tm.tm_mday, tm.tm_hour, tm.tm_min, tm.tm_sec, temp, humidity, pressure);
        dev->data_ready = true;

        dev->stats.samples_generated++;
        dev->stats.wakeups++;

        current_interval = dev->sampling_interval;
        mutex_unlock(&dev->lock);

        wake_up_interruptible(&dev->wait_queue);

        wait_event_interruptible_timeout(dev->thread_wait, kthread_should_stop(), msecs_to_jiffies(current_interval));
    }

    return 0;
}

static int tempsensor_open(struct inode *inode, struct file *file)
{
    struct tempsensor_dev *dev;

    dev = container_of(inode->i_cdev, struct tempsensor_dev, cdev);
    file->private_data = dev;

    pr_info("%s: Device opened\n", DRIVER_NAME);
    return 0;
}

static ssize_t tempsensor_read(struct file *file, char __user *user_buf, size_t count, loff_t *f_pos)
{
    struct tempsensor_dev *dev = file->private_data;
    size_t bytes_to_copy;
    int ret;

    if(!dev->data_ready)
    {
        mutex_lock(&dev->lock);
        dev->stats.blocked_reads++;
        mutex_unlock(&dev->lock);
    }

    ret = wait_event_interruptible(dev->wait_queue, dev->data_ready);
    if(ret!= 0)
    {
        return -ERESTARTSYS;
    }

    if(mutex_lock_interruptible(&dev->lock))
    {
        return -ERESTARTSYS;
    }

    bytes_to_copy = min(count, dev->data_len);
    if(copy_to_user(user_buf, dev->buffer, bytes_to_copy))
    {
        mutex_unlock(&dev->lock);
        return -EFAULT;
    }

    dev->data_ready = false;
    dev->stats.read_operations++;

    pr_info("%s: Read operation called\n", DRIVER_NAME);

    mutex_unlock(&dev->lock);
    return bytes_to_copy;
}

static ssize_t tempsensor_write(struct file *file, const char __user *user_buf, size_t count, loff_t *f_pos)
{
    struct tempsensor_dev *dev = file->private_data;

    if(mutex_lock_interruptible(&dev->lock))
    {
        return -ERESTARTSYS;
    }

    pr_info("%s: Write operation called\n", DRIVER_NAME);

    mutex_unlock(&dev->lock);
    return count;
}

static long tempsensor_ioctl(struct file *file, unsigned int cmd, unsigned long arg)
{
    struct tempsensor_dev *dev = file->private_data;
    unsigned int interval;
    SensorStats current_stats;

    switch(cmd)
    {
        case TEMPSENSOR_SET_INTERVAL:
            if(copy_from_user(&interval, (unsigned int __user *)arg, sizeof(unsigned int)))
            {
                return -EFAULT;
            }

            if(interval < 100 || interval > 5000)
            {
                pr_err("%s: Invalid sampling interval: %u ms. Must be between 100 and 5000 ms.\n", DRIVER_NAME, interval);
                return -EINVAL;
            }

            if(mutex_lock_interruptible(&dev->lock))
            {
                return -ERESTARTSYS;
            }
            dev->sampling_interval = interval;
            mutex_unlock(&dev->lock);

            wake_up_interruptible(&dev->thread_wait);

            pr_info("%s: Sampling interval set to %u ms\n", DRIVER_NAME, interval);
            break;

        case TEMPSENSOR_GET_STATS:
            if(mutex_lock_interruptible(&dev->lock))
            {
                return -ERESTARTSYS;
            }
            current_stats = dev->stats;
            mutex_unlock(&dev->lock);

            if(copy_to_user((SensorStats __user *)arg, &current_stats, sizeof(SensorStats)))
            {
                return -EFAULT;
            }
            pr_info("%s: Stats retrieved\n", DRIVER_NAME);
            break;

        case TEMPSENSOR_RESET_STATS:
            if(mutex_lock_interruptible(&dev->lock))
            {
                return -ERESTARTSYS;
            }
            memset(&dev->stats, 0, sizeof(SensorStats));
            mutex_unlock(&dev->lock);
            pr_info("%s: Statistics reset to zero\n", DRIVER_NAME);
            break;

        default:
            pr_err("%s: Invalid ioctl command: %u\n", DRIVER_NAME, cmd);
            return -EINVAL;
    }

    return 0;
}

static int tempsensor_release(struct inode *inode, struct file *file)
{
    pr_info("%s: Device closed\n", DRIVER_NAME);
    return 0;
}

static const struct file_operations tempsensor_fops = {
    .owner = THIS_MODULE,
    .open = tempsensor_open,
    .read = tempsensor_read,
    .write = tempsensor_write,
    .unlocked_ioctl = tempsensor_ioctl,
    .release = tempsensor_release,
};

static int __init tempsensor_init(void)
{
    int ret;
    struct device *device_node;

    pr_info("%s: Initializing Driver\n", DRIVER_NAME);

    ret = alloc_chrdev_region(&dev_num, 0, 1, DRIVER_NAME);
    if(ret < 0)
    {
        pr_err("%s: Failed to allocate character device region\n", DRIVER_NAME);
        return ret;
    }

    tempsensor_class = class_create(CLASS_NAME);
    if(IS_ERR(tempsensor_class))
    {
        pr_err("%s Failed to create class\n", DRIVER_NAME);
        unregister_chrdev_region(dev_num, 1);
        return PTR_ERR(tempsensor_class);
    }

    ts_device = kzalloc(sizeof(struct tempsensor_dev), GFP_KERNEL);
    if(!ts_device)
    {
        pr_err("%s: Failed to allocate memory for device structure\n", DRIVER_NAME);
        class_destroy(tempsensor_class);
        unregister_chrdev_region(dev_num, 1);
        return -ENOMEM;
    }

    mutex_init(&ts_device->lock);
    init_waitqueue_head(&ts_device->wait_queue);
    init_waitqueue_head(&ts_device->thread_wait);
    ts_device->sampling_interval = 1000; // Default sampling interval in milliseconds
    ts_device->data_ready = false;
    
    cdev_init(&ts_device->cdev, &tempsensor_fops);
    ts_device->cdev.owner = THIS_MODULE;

    ret = cdev_add(&ts_device->cdev, dev_num, 1);
    if(ret < 0)
    {
        pr_err("%s: Failed to add cdev\n", DRIVER_NAME);
        kfree(ts_device);
        class_destroy(tempsensor_class);
        unregister_chrdev_region(dev_num, 1);
        return ret;
    }

    device_node = device_create(tempsensor_class, NULL, dev_num, NULL, DRIVER_NAME);
    if(IS_ERR(device_node))
    {
        pr_err("%s: Failed to create device\n", DRIVER_NAME);
        cdev_del(&ts_device->cdev);
        kfree(ts_device);
        class_destroy(tempsensor_class);
        unregister_chrdev_region(dev_num, 1);
        return PTR_ERR(device_node);
    }

    ts_device->thread = kthread_run(tempsensor_thread, ts_device, "%s_thread", DRIVER_NAME);
    if(IS_ERR(ts_device->thread))
    {
        pr_err("%s: Failed to create kernel thread\n", DRIVER_NAME);
        ret = PTR_ERR(ts_device->thread);
        device_destroy(tempsensor_class, dev_num);
        cdev_del(&ts_device->cdev);
        kfree(ts_device);
        class_destroy(tempsensor_class);
        unregister_chrdev_region(dev_num, 1);
        return ret;
    }

    pr_info("%s: Driver initialized successfully. Major number: %d, Minor number: %d\n", DRIVER_NAME, MAJOR(dev_num), MINOR(dev_num));
    return 0;
}

static void __exit tempsensor_exit(void)
{
    if(ts_device->thread)
    {
        kthread_stop(ts_device->thread);
    }

    device_destroy(tempsensor_class, dev_num);
    cdev_del(&ts_device->cdev);

    kfree(ts_device);

    class_destroy(tempsensor_class);
    unregister_chrdev_region(dev_num, 1);

    pr_info("%s: Driver exited successfully\n", DRIVER_NAME);
}

module_init(tempsensor_init);
module_exit(tempsensor_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Pulkit");
MODULE_DESCRIPTION("Virtual Temperature Sensor Driver Skeleton");
MODULE_VERSION("1.0");