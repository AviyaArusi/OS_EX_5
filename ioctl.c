#include <linux/uaccess.h>
#include "main.h"

#define IOCTL_SET_KEY _IOW('a', 0, uint32_t *)

long device_ioctl(struct file *file, unsigned int ioctl_num, unsigned long ioctl_param)
{
    uint32_t new_key;
    int err = 0;

    /* Check the type and number of the ioctl command */
    if (_IOC_TYPE(ioctl_num) != 'a') return -ENOTTY;
    if (_IOC_NR(ioctl_num) != 0) return -ENOTTY;

    /* Verify that the user space pointer is valid */
    if (!access_ok((void __user *)ioctl_param, sizeof(uint32_t)))
        return -EFAULT;

    /* Fetch the new key from user space */
    err = copy_from_user(&new_key, (uint32_t *)ioctl_param, sizeof(new_key));
    if (err != 0) {
        printk(KERN_WARNING "Failed to copy data from user space\n");
        return -EFAULT;
    }

    /* Update the encryption key */
    encryption_key = new_key;

    printk(KERN_INFO "Encryption key updated successfully\n");

    return 0;
}
