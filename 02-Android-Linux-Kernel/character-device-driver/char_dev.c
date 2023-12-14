/*
 * Copyright (C) 2023 Dung Tran Anh
 */

#include <linux/module.h>    // all kernel modules
#include <linux/kernel.h>    // KERN_INFO
#include <linux/errno.h>     // EFAULT
#include <linux/device.h>    // device register
#include <linux/fs.h>        // file_operations
#include <linux/types.h>     // size_t
#include <linux/uaccess.h>   // copy_from/to_user

/* DEVICE NAME */
#define DEVICE_NAME     "char_dev"   // The device will appear at /dev/char_dev
#define CLASS_NAME      "char_class"
#define DEVICE_DEBUG    "char_demo: "

/* Global variable */
static int majorNumber = 0;
static struct class*  char_class  = NULL;
static struct device* char_dev = NULL;

#define MAX_SIZE 1024
static char __buffer[MAX_SIZE] = {0};

/* Function declaration */
static int chr_module_init(void);
static void chr_module_exit(void);
static ssize_t my_read(struct file *filp, char *buf, size_t count, loff_t *f_pos);
static ssize_t my_write(struct file *filp, const char *buf, size_t count, loff_t *f_pos);

/* Device operations */
static struct file_operations __fops = 
{
    .owner  = THIS_MODULE,
    .read   = my_read,
    .write  = my_write,
};

static int chr_module_init(void){
    // Dynamically allocate a major number for the device
    majorNumber = register_chrdev(0, DEVICE_NAME, &__fops);
    if (majorNumber<0){
        printk(KERN_ERR DEVICE_DEBUG "Failed to register a major number\n");
        return majorNumber;
    }
    printk(KERN_INFO DEVICE_DEBUG "Registered with major number %d\n", majorNumber);

    // Register the device class
    char_class = class_create(THIS_MODULE, CLASS_NAME);
    if (IS_ERR(char_class)) // Check for error and clean up if there is
    {
        unregister_chrdev(majorNumber, DEVICE_NAME);
        printk(KERN_ERR DEVICE_DEBUG "Failed to register device class\n");
        return PTR_ERR(char_class); // Correct way to return an error on a pointer
    }
    printk(KERN_INFO DEVICE_DEBUG "Device class registered correctly\n");

    // Register the device driver
    char_dev = device_create(char_class, NULL, MKDEV(majorNumber, 0), NULL, DEVICE_NAME);
    if (IS_ERR(char_dev)) // Clean up if there is an error
    {
        class_destroy(char_class);
        unregister_chrdev(majorNumber, DEVICE_NAME);
        printk(KERN_ERR DEVICE_DEBUG "Failed to create the device\n");
        return PTR_ERR(char_dev);
    }

    // clear buffer
    memset(__buffer, 0, MAX_SIZE);
    printk(KERN_INFO DEVICE_DEBUG "Character Driver Init!!!!\n");
    return 0;
}

static void chr_module_exit(void){
    // remove the device
    device_destroy(char_class, MKDEV(majorNumber, 0)); 

    // unregister the device class
    class_unregister(char_class);

    // remove the device class 
    class_destroy(char_class);

    // unregister the major number
    unregister_chrdev(majorNumber, DEVICE_NAME);
    printk(KERN_INFO DEVICE_DEBUG "Character Driver Exit\n");
}

static ssize_t my_read(struct file *filp, char *buf, size_t count, loff_t *f_pos) {
    ssize_t remain = MAX_SIZE - *f_pos;
    ssize_t len = count > remain ? remain : count;

    printk(KERN_INFO DEVICE_DEBUG "Read from device, remain=%ld, *f_pos= %lld, count= %ld\n", remain, *f_pos, count);
    
    if(remain <= 0) 
        return 0;

    if (copy_to_user(buf, __buffer+*f_pos, len)) {
        printk(KERN_ERR DEVICE_DEBUG "Can not copy to user\n");
        return -EFAULT;
    }
    printk(KERN_INFO DEVICE_DEBUG "Read from device: %s\n", __buffer);

    *f_pos += len;
    return len;
}

static ssize_t my_write(struct file *filp, const char *buf, size_t count, loff_t *f_pos) {
    ssize_t remain = MAX_SIZE - *f_pos;
    ssize_t len = count > remain ? remain : count;

    printk(KERN_INFO DEVICE_DEBUG "Write to device, remain=%ld, *f_pos= %lld, count= %ld\n", remain, *f_pos, count);

    if(*f_pos == 0)
        memset(__buffer, 0, MAX_SIZE);

    if(remain <= 0)
        return count; // ignore all requested bytes

    if(copy_from_user(__buffer+*f_pos, buf, len)) {
        printk(KERN_ERR DEVICE_DEBUG "Can not copy from user\n");
        return -EFAULT;
    }
    printk(KERN_INFO DEVICE_DEBUG "Write to device: %s\n", __buffer);

    *f_pos += len;
    return len;
}

module_init(chr_module_init);
module_exit(chr_module_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("DUNGTA");
MODULE_DESCRIPTION("Character Driver Demo");