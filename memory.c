#include <linux/uaccess.h>
#include <linux/slab.h>
#include "main.h"

// Assuming 1 page for now
// #define PAGE_SIZE 4096

static char *device_buffer = NULL;
static int bytes_written = 0;
static int current_byte = 0;

// Simple XOR cipher for encryption
void encrypt_decrypt(char *data, int data_len, uint32_t key) {
    int i;
    for(i = 0; i < data_len; ++i)
        data[i] ^= key;
}

int device_open(struct inode *inode, struct file *file) {
    // allocate buffer when device is opened
    device_buffer = kmalloc(PAGE_SIZE, GFP_KERNEL);

    if(!device_buffer)
        return -ENOMEM;  // Return if allocation failed

    memset(device_buffer, 0, PAGE_SIZE);  // Zero out the buffer
    bytes_written = 0;  // Reset bytes counter

    return 0;
}

int device_release(struct inode *inode, struct file *file) {
    kfree(device_buffer);  // free buffer when device is closed
    device_buffer = NULL;  // Avoid dangling pointer
    return 0;
}

ssize_t device_read(struct file *file, char *buffer, size_t len, loff_t *offset) {
    int bytes_to_read = min(len, (size_t)(bytes_written - current_byte));

    // Copy to user space
    if(copy_to_user(buffer, device_buffer + current_byte, bytes_to_read)) {
        return -EFAULT;
    }

    current_byte += bytes_to_read;

    if(current_byte >= bytes_written)  // We've reached EOF
        current_byte = 0;  // Reset back to the start of the buffer

    return bytes_to_read;
}

ssize_t device_write(struct file *file, const char *buffer, size_t len, loff_t *offset) {
    int bytes_to_write = min(len, (size_t)(PAGE_SIZE - bytes_written));

    // Copy from user space
    if(copy_from_user(device_buffer + bytes_written, buffer, bytes_to_write)) {
        return -EFAULT;
    }

    encrypt_decrypt(device_buffer + bytes_written, bytes_to_write, encryption_key);

    bytes_written += bytes_to_write;

    return bytes_to_write;
}
