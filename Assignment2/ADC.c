#include<linux/init.h>
#include<linux/module.h>
#include<linux/device.h>
#include<linux/kernel.h>
#include<linux/version.h>
#include<linux/types.h>
#include<linux/cdev.h>
#include<linux/kdev_t.h>
#include<linux/fs.h>
#include<linux/ioctl.h>
#include<asm/uaccess.h>
#include <linux/random.h>
#include "adc0.h"
#include<linux/ioctl.h>
#include <linux/unistd.h>
#define SUCCESS 0
#define DEVICE_NAME "ADC0"
int Device_open =0;
char Message;
static dev_t devno;
int genrandom(void);
int dev_open(struct inode *inodep,struct file *filep)
{
#ifdef DEBUG
	printk(KERN_INFO "device_open(%p)\n",file);
#endif
if(Device_open)
	return -EBUSY;
Device_open++;
printk(KERN_INFO "ADC0 Device has been opened %d time(s)\n",Device_open);
try_module_get(THIS_MODULE);
return SUCCESS;
}
int dev_release(struct inode *inode,struct file *file)
{
#ifdef DEBUG 
	printk(KERN_INFO "device_release(%p,%p)\n",inode,file);
#endif
Device_open--;
module_put(THIS_MODULE);
return SUCCESS;
}
ssize_t dev_read(struct file *filep,char __user *buffer,size_t length,loff_t *offset)
{
	args ret_val;
	int bytes_read=0;
	int value;
	printk(KERN_INFO "device_read\n");
        int adcop=genrandom();
        printk(KERN_INFO "the value is %d",adcop);
 switch(ret_val.msg1)
{
case 1:
      printk(KERN_INFO "ADC1 output is:",adcop);
	break;
case 2:
      printk(KERN_INFO"ADC2 output is:",adcop);
	break;	
case 3:
      printk(KERN_INFO"ADC3 output is:",adcop);
	break;
case 4:
      printk(KERN_INFO"ADC4 output is:",adcop);
	break;
case 5:
      printk(KERN_INFO"ADC5 output is:",adcop);
	break;
case 6:
      printk(KERN_INFO"ADC6 output is:",adcop);
	break;
case 7:
      printk(KERN_INFO"ADC1 output is:",adcop);
	break;
case 8:
      printk(KERN_INFO"ADC1 output is:",adcop);
	break;
default:
 printk(KERN_INFO "sorry..only 8 channels");
break;
}
ret_val.msg2=adcop;
return ret_val.msg2;
}


ssize_t dev_write(struct file *filep,const char __user *buffer,size_t length,loff_t *offset)
{
	int i=0;
	printk(KERN_INFO "dev_write(%p,%s,%d)",filep,buffer,length);
	return i;
}
int genrandom(void)
{
	int random;
	get_random_bytes(&random,2);
	random=random%1023;
	return random;
}
long dev_ioctl(struct file *file,unsigned int ioctl_num,unsigned long ioctl_param)
{
	args ret_val;
	int i;
	char *temp;
	char ch;
	int adcop;

switch (ioctl_num)
{
case IOCTL_SET_MSG:
temp=(char *)ioctl_param;
get_user(ch,temp);
dev_write(file,(char *)ioctl_param,0,0);
break;
case IOCTL_GET_MSG:
        printk(KERN_INFO "entered ioctl");
        raw_copy_from_user(&ret_val,(args *)ioctl_param,sizeof(args));
        dev_read(file,(char *)ioctl_param,99,0);
       /*put_user('\0',(char *)ioctl_param+i);*/
        raw_copy_to_user((args *)ioctl_param,&ret_val,sizeof(args));	
        break;
}
}
static struct file_operations fops=
{
	.owner=THIS_MODULE,
	.open=dev_open,
	.read=dev_read,
	.write=dev_write,
	.release=dev_release,
	.unlocked_ioctl=dev_ioctl
};

int ADC_init(void)
{
	int ret_val;
	printk(KERN_INFO "ADC0:Initializing ADC\n");
	ret_val=register_chrdev(MAJOR_NUM,DEVICE_NAME, &fops);
	devno=MKDEV(MAJOR_NUM,0);
	if(ret_val<0)
	{
	printk(KERN_ALERT "ADC0 failed to register a major number\n");
	return ret_val;
	}
	printk(KERN_INFO "ADC0 registered correctly with major number %d\n",MAJOR_NUM);
	return 0;
	}
void ADC_exit(void)
{
	unregister_chrdev(MAJOR_NUM , DEVICE_NAME);
	printk(KERN_INFO "ADC0 goodbye\n");
}
module_init(ADC_init);
module_exit(ADC_exit);


