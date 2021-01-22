
/**********************************************************************************************/
/*****************		KERNEL DRIVER CODE FOR MOUSE		***********************/
/***********     READ DATA MOUSE DRIVER AND SEND IT USER SPACE APPLICATION     ****************/
/**********************************************************************************************/




#include"mouse.h"											    /// Creates the custom header file.

int major=0;												    /// Declare a variable to store moajor No.
mm_segment_t oldfs;											    ///  
    struct file *FileDes=0;


static int driver_open(struct inode *inod,struct file *fil)						    /// Open System Call Function Definition
{
    printk(KERN_ALERT "%s()  Open System Call get Called\n",__func__);		       			    /// Message to Convery User that open() called succesfully
    return 0;
}

static ssize_t driver_read(struct file *filp, char *uBuff,size_t len,loff_t *off)			    /// Read system call Definition Function
{
    char kBuff = 0;											    /// To Store data, what we read into the MICE file 
    int count=0;											    /// Variable decleration for to store how many bytes read from MICE file
    printk(KERN_ALERT "%s()  Read system Call gets Called from User Space \n",__func__);		    /// Prints the Entry Message in the Func when ever User calls read() 

    file_open(MICE_DEVICE_FILE);								    /// Open the file called MICE_DEVICE_FILE Internally calls flip_open().

    if(FileDes == NULL)											    /// When it unable able to open returns NULL
    {
        printk(KERN_ALERT "Can't Open FILE --> %s\n",MICE_DEVICE_FILE);					    /// Error Message
    }
    else												    /// If it Open's Success fully
    {	
        count = file_read(FileDes,0,&kBuff,sizeof(kBuff));						    /// Read from the file internally calls vfs_read ,
	printk("[0] %X\n",kBuff);
														    /// returns the no.of bytes are to be read in the File
//	uBuff[0] = 0;											    /// Making User Buffer as NULL.
	if(count == 0)											    /// If Unable to read in the file returns ZERO.
	    return 0;											    /// Return From Here.
	copy_to_user(uBuff,&kBuff,sizeof(kBuff));						    /// if success copy_to_user call.
    }
    return count;											    /// Return Count, to the caller's func.
}

static ssize_t driver_write(struct file *filp,const char *uBuff,size_t len,loff_t *off)			    /// Write system Func Definition Function.
{
    char kBuff[BUFF_SIZE]={0};
    int Bytes=0;

    printk(KERN_ALERT "%s() WRITE SYSTEM CALL CALLED\n",__func__);					    /// Write System Call Function.

    Bytes= copy_from_user(kBuff,uBuff,sizeof(kBuff));							    /// Copy to Kernel Buffer DATA recieved from 
    if(Bytes == 0)											    /// copy_from_user Func Returns 0 means SUCCESS ,else FAILURE.
    {
        printk(KERN_ALERT "%s() User sent Data %s ...",__func__,kBuff);					    /// Prints the data .  
	return strlen(kBuff);
    }
    return Bytes;											    /// Return From Func
}


static int driver_release(struct inode *inod,struct file *fil)						    /// close system call Function Definition.
{
    printk(KERN_ALERT "%s() Release Func Called\n",__func__);						    /// Prints the Message 
    return 0;
}   

struct file* file_open(const char* path)								    /// File Open Func for Opening the file to read mouse tracks.
{
//    struct file* filePtr = NULL;									    /// Declare a file Pointer to Open Character Special File to read Mice Data.
    int err = 0;

    oldfs = get_fs();											    /// This Func will return the Address limit of the Current Process
    set_fs(KERNEL_DS);											    /// Setting the Address Limit for Current Process will be as same as KERNEL_DS
													    ///	If not there can be some 

    FileDes = filp_open(path, 0 , 0);									    /// Open the file from which data to be read from Mice "/dev/input/mice"


    if(IS_ERR(FileDes))											    /// if becomes true ,when there is an error while Opening the File.
    {
	printk(KERN_ALERT"Unable to Open File : %s\n",path);						    /// Prints the error message for which 
        err = PTR_ERR(FileDes);										    /// Prints the error message or Cause for error.
	set_fs(oldfs);											    /// Setting the Old Address limit when as what we had previous
        return NULL;											    /// Return NULL from here.
    }
//    return filePtr;											    /// Returns the File Descriptor If flip_open SUCCESS
    return 0;
}

int file_read(struct file* file, unsigned long long offset, unsigned char* data, unsigned int size)	    /// Function That actually Reads the Data from the file < MICE_DEVICE_FILE >
{
    int ret = 0;											    /// Variable decleration for returning the bytes to be read.
//    mm_segment_t oldfs;
//    oldfs = get_fs();
//    set_fs(KERNEL_DS);

    ret = vfs_read(FileDes, data, size, &offset);								    /// Reading from the < MICE_DEVICE_FILE > Using the File Descriptor "file"

    filp_close(FileDes,NULL);										    /// After Reading from the file Close the file from Doing Operations.
    set_fs(oldfs);											    /// Setting the Old USER_DS Address Limit.
    return ret;												    /// Return No.of Bytes Read. if error 0 will return
}   


static struct file_operations fops =									    /// Passing Addresses of functions for user space applicaition Callling Func.
{
/*
 *  Generally we are declearing thati, which function should call when USER SPACE APPLICATION 
 *  do the some operations with Special file we are created.
 *  In our case Character special file : "/dev/MOUSE"
 */
    .read    = driver_read,										    /// Passing read() address as driver_read().
    .open    = driver_open,										    /// Passing open() address as driver_open().
    .write   = driver_write,										    /// Passing write() address as driver_write().
    .release = driver_release,										    /// Passing close() address as driver_release().
};


__init static int my_init(void)									       	    ///  Init the Driver Module.
{
    printk(KERN_ALERT "INIT MODULE");									    /// Print the Driver Module Init 
    major = register_chrdev(0,"MOUSE",&fops);								    /// Register the character device file Creation
												/*  
												 *	register_chrdev() --> Register the character Special File with as Arguments as
												 *      0 ---> ZERO secifies the what ever avaliable free major number right now ,that to be allocated.
												 *	"MOUSE" --->  Name of the File need to be created 
												 *	fops    --->  What ever we created structure previously created loading into the register_chrdev().
												 */

    if(major < 0)											    /// Returns the Greater than ZERO on SUCCESS.
        printk(KERN_ALERT "device registration failed .. \n");						    /// On Failure
    else												    /// ON Success
        printk(KERN_ALERT "device registered..  %d \n",major);
    return 0;												    /// Return From the Function.
}

__exit static void my_exit(void)									    /// Exit Function of the kernel module.
													    /// Called before when the module is removed from kernel spcae.
{
    printk(KERN_ALERT "MODULE EXIT\n");									    /// Prints in the log module_exit func has called.
    unregister_chrdev(major,"MOUSE");									    /// de-register the func what ever we have created in module_init ().
}

module_init(my_init);											    /// Passing the Function Address to the module_init func
module_exit(my_exit);											    /// Passing the Function Address to the module_exit func
MODULE_LICENSE("GPL");											    /// Registering with License as GPL ( GNU Public License )
MODULE_DESCRIPTION("DEVICE DRIVER for READING MICE DATA");						    /// Description of the module .
MODULE_AUTHOR("SHILPA");										    /// Author of the Module.
