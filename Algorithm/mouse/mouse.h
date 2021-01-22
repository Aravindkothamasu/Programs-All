

#ifndef __MOUSE_H__
#define __MOUSE_H__



/*
 *  LINUX KERNEL HEADERS 
 *
 */

#include<linux/module.h>
#include<linux/init.h>
#include<linux/fs.h>
#include<linux/device.h>
#include<linux/uaccess.h>
#include<linux/string.h>
#include<linux/delay.h>
#include<linux/module.h>
#include<linux/string.h>
#include<linux/fs.h>
#include<asm/uaccess.h>
#include<asm/segment.h>



#define MICE_DEVICE_FILE    "/dev/input/mice"							    /// INPUT FILE ,where we need to read the mouse reading's
#define BUFF_SIZE	    30									    /// BUFFER LENGTH used in our Module.

												    /// Function Registering for USER SPACE APPLICATION calling Func.
static int driver_open(struct inode *,struct file *);
static int driver_release(struct inode *,struct file *);
static ssize_t driver_read(struct file *,char *, size_t,loff_t *);
static  ssize_t driver_write(struct file *,const char *,size_t,loff_t *);




struct file* file_open(const char*);
int file_read(struct file* file, unsigned long long , unsigned char*, unsigned int );	

#endif
