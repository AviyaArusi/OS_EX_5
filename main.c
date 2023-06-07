#include <linux/module.h>
#include <linux/init.h>
#include <linux/fs.h>
#include <linux/semaphore.h>

#define DEVICE_NAME "encryptedmem"

static char message[1024] = {0};  // The message the device will give when asked
static int size_of_message = 0;   // The size of that message


static int major;
/*static*/ uint32_t encryption_key = 0; // Initial encryption key
module_param(encryption_key, uint, 0660); // Expose key as a module parameter

static struct semaphore mutex;

/* Device Open */
static int device_open(struct inode *inode, struct file *file)
{
    /* We could perform some hardware operations here, or initialize our device */

    /* Increment usage count */
    try_module_get(THIS_MODULE);

    return 0;
}

/* Device Release */
static int device_release(struct inode *inode, struct file *file)
{
    /* We could perform some cleanup operations here, or shutdown our device */

    /* Decrement usage count */
    module_put(THIS_MODULE);

    return 0;
}

/* Device Read */
static ssize_t device_read(struct file *file, char *buffer, size_t len, loff_t *offset)
{
    /* 'buffer' is in user space, not kernel, so we can't touch it directly. Instead, we have to use the 'copy_to_user' function */
    /* 'count' is the size of the user space buffer */
    /* If the user asks for more data than we provide, then just give them what we have. */
    /* Otherwise give them the requested amount. */

    int bytes_to_read = len < size_of_message ? len : size_of_message;

    /* 'copy_to_user' returns the number of bytes NOT copied. If it's not zero (i.e., if the operation was not successful), return a failure code. */
    if (copy_to_user(buffer, message, bytes_to_read) != 0)
        return -EFAULT;

    return bytes_to_read; /* Return the number of bytes sent to the user */
}

/* Device Write */
static ssize_t device_write(struct file *file, const char *buffer, size_t len, loff_t *offset)
{
    /* This is a read-only device. We aren't going to allow writes. */
    /* But if we did, we would have to use 'copy_from_user' to get data from the user space. */

    printk(KERN_ALERT "This operation isn't supported.\n");
    return -EINVAL; /* Failed */
}

/* Device IOCTL */
static long device_ioctl(struct file *file, unsigned int ioctl_num, unsigned long ioctl_param)
{
    /* This device doesn't support ioctl. */
    /* If we did, this is where we would parse the ioctl numbers and parameters,
     * performing whatever actions were appropriate. */

    printk(KERN_ALERT "This operation isn't supported.\n");
    return -EINVAL; /* Failed */
}

static struct file_operations fops = {
	.open = device_open,
	.release = device_release,
	.read = device_read,
	.write = device_write,
	.unlocked_ioctl = device_ioctl,
};

static int __init encryptedmem_init(void)
{
	major = register_chrdev(0, DEVICE_NAME, &fops);
	if (major < 0) {
		printk(KERN_ALERT "Failed to register char device\n");
		return major;
	}

	printk(KERN_INFO "Registered char device with major number %d\n", major);

	// Initialize semaphore
	sema_init(&mutex, 1);

	return 0;
}

static void __exit encryptedmem_exit(void)
{
	unregister_chrdev(major, DEVICE_NAME);
	printk(KERN_INFO "Unregistered char device\n");
}

module_init(encryptedmem_init);
module_exit(encryptedmem_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Your Name");
MODULE_DESCRIPTION("Encrypted Memory Kernel Module");
