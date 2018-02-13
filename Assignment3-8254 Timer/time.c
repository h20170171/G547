#include <linux/kernel.h>
#include <linux/module.h>
#include <asm/io.h>
#include <linux/fs.h>
#include <linux/delay.h>
#include <linux/signal.h>
#include<linux/init.h>
#include<linux/device.h>
#include<linux/version.h>
#include<linux/types.h>
#include<linux/cdev.h>
#include<linux/kdev_t.h>
#include<linux/ioctl.h>
#include<asm/uaccess.h>
#include "time.h"
#include<linux/ioctl.h>
#include <linux/unistd.h>
#define IRQ_NUM 0
/*timer registers*/
#define TIMERCONTROL 0x43
#define TIMERCOUNTER 0x40
#define TIMERMASK 0XFF
#define TIMERSCALE 1193180
#define TIMERSET 0X60
#define DEVICE_NAME "/dev/timer0"
#define MAJOR_NUM 100
#define MINOR_NUM 0
#define success 0
int i;
int deviceopen=0;
static dev_t dev;
static struct class *classcreate;
static struct cdev c_dev;
ssize_t dev_write(struct file *filp,const char *buff,size_t length,loff_t *offset)
{
printk(KERN_INFO "Device Write");
return success;
}
ssize_t dev_read(struct file *filp,char *buf,size_t length,loff_t *offset)
{
printk(KERN_INFO "Device reading...\n");
return 0;
}
int dev_open(struct inode *inodep,struct file *filep)
{
printk(KERN_INFO "You tried to open the module");
return success ;
}
int dev_release(struct inode *inodep,struct file *filep)
{
printk(KERN_INFO "You tried to open the module");
return success ;
}
/*Initialise timer */
void timerinit(void)
{
int ticontrol=0x60;
int ticounter=0x00;
outb(ticontrol,TIMERCONTROL);
outb(ticounter,TIMERCOUNTER);
}
/*Function to calculate delay of 1ms*/
int delay(int hz)
{
int countms=TIMERSCALE/hz;
outb(countms,TIMERCOUNTER);
outb((countms >>8)& TIMERMASK,TIMERCOUNTER);
return countms;
}
/*Function to send kernel to sleep*/
void delayfunc(void)
{
int count=delay(1000);
for(i=0;i<count;i++)
{
	printk(KERN_INFO "Kernel is sleepy..Babye!..\n");/*Alternatively 	  ssleep(int) can be implemented here to send kernel to sleep*/
}
}
/*For sending counter value to user space and sending kernel to sleep ioctl is used*/
long dev_ioctl(struct file *file,unsigned int ioctl_num,unsigned long ioctl_param)
{
int x=0;
args q;
int s=0;
switch(ioctl_num)
{
case TIMER:
	
        timerinit();
	delay(1000);
	outb(success,TIMERCONTROL);
	x=inb(TIMERCOUNTER);
        printk(KERN_INFO "the count value is %d \n",x);
	break;
}
q.val=x;
delayfunc();
if(raw_copy_to_user((args *)ioctl_param,&q,sizeof(args)))
	return -1;
return 0;
}
struct file_operations fops=
{
.owner=THIS_MODULE,
.read=dev_read,
.write=dev_write,
.open=dev_open,
.release=dev_release,
.unlocked_ioctl=dev_ioctl
};

int time_init(void)
{

printk(KERN_INFO "Initialising module...\n");
dev=MKDEV(MAJOR_NUM,MINOR_NUM);
printk(KERN_INFO "MAJOR NO=%d,MINOR NO=%d",MAJOR(dev),MINOR(dev));
//timerinit();
if((classcreate=class_create(THIS_MODULE,"chardriver"))==NULL)
{
	unregister_chrdev_region(dev,1);
	return -1;
}
if(device_create(classcreate,NULL,dev,NULL,DEVICE_NAME)==NULL)
{
class_destroy(classcreate);
unregister_chrdev_region(dev,1);
return -1;
}
cdev_init(&c_dev,&fops);
//delay(1000);
if(cdev_add(&c_dev,dev,1)==-1)
{
device_destroy(classcreate,dev);
class_destroy(classcreate);
unregister_chrdev_region(dev,1);
return -1;
}
return 0;
}
void time_exit(void)
{
cdev_del(&c_dev);
device_destroy(classcreate,dev);
class_destroy(classcreate);
unregister_chrdev_region(dev,1);
printk(KERN_INFO "Babye...\n");
}
module_init(time_init);
module_exit(time_exit);
MODULE_LICENSE("GPL");
MODULE_AUTHOR("HARSHITHA");


