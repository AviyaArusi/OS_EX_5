// #ifndef MAIN_H
// #define MAIN_H

#pragma once

#include <linux/module.h>
#include <linux/init.h>
#include <linux/fs.h>
#include <linux/semaphore.h>

// External declarations
extern uint32_t encryption_key;
extern struct semaphore mutex;

extern int device_open(struct inode *inode, struct file *file);
extern int device_release(struct inode *inode, struct file *file);
extern ssize_t device_read(struct file *file, char *buffer, size_t len, loff_t *offset);
extern ssize_t device_write(struct file *file, const char *buffer, size_t len, loff_t *offset);
extern long device_ioctl(struct file *file, unsigned int ioctl_num, unsigned long ioctl_param);

// #endif // MAIN_H


