
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/slab.h>
#include <linux/errno.h>
#include <linux/mutex.h>
#include <asm/uaccess.h>
#include <linux/usb.h>
#include "usblcd.h"
#include<linux/device.h>
#include<linux/version.h>
#include<linux/types.h>
#include<linux/cdev.h>
#include<linux/kdev_t.h>
#include<linux/fs.h>
#include<linux/ioctl.h>
#include<asm/uaccess.h>
#include <linux/string.h>
#include "ad.h"
#define DRIVER_VERSION "USBLCD Driver"
#define USBDEV_SHARED_VENDOR    0x16C0  /* VOTI */
#define USBDEV_SHARED_PRODUCT   0x05DC  /* Obdev's free shared PID */
#define USBLCD_MINOR		144
#define MAJOR_NO 100
#define MINOR_NO 3
#define BUF_LEN 80
static char Message[BUF_LEN];
static char *Message_Ptr;
static dev_t devno;
static struct class *class_cr;
static struct cdev c_dev;
int nBytes;
int v=0;
args q;
static DEFINE_MUTEX(openmutex);
static struct usb_device_id id_table [] = {
	{ .idVendor = 0x16c0, .match_flags = USB_DEVICE_ID_MATCH_VENDOR, },
	{ },
};
MODULE_DEVICE_TABLE (usb, id_table);
struct usb_lcd {
	struct usb_device *	udev;			/* init: probe_lcd */
	struct usb_interface *  interface;		
	unsigned char * control_in_buffer;		
	size_t	control_in_size;		
	__u8 control_in_endpointAddr;	
	__u8	control_out_endpointAddr;
	struct kref kref;
	//struct semaphore	limit_sem;				 * 

};
#define to_lcd_dev(d) container_of(d, struct usb_lcd, kref)
#define USB_LCD_CONCURRENT_WRITES	5
static struct usb_driver lcd_driver;
void lcd_delete(struct kref *kref)
{
	struct usb_lcd *dev = to_lcd_dev(kref);
	usb_put_dev(dev->udev);
	kfree (dev->control_in_buffer);
	kfree (dev);
}


static int lcd_open(struct inode *inode, struct file *file)
{
	try_module_get(THIS_MODULE);
        printk(KERN_INFO "Device open()\n");
	return 0;
}

int lcd_release(struct inode *inode, struct file *file)
{
	struct usb_lcd *dev;
module_put(THIS_MODULE);
	dev = (struct usb_lcd *)file->private_data;
	if (dev == NULL)
		return -ENODEV;
	usb_autopm_put_interface(dev->interface);
	kref_put(&dev->kref, lcd_delete);
	return 0;
}



   


  

ssize_t lcd_write(struct file *file,const char __user *puser,size_t length,loff_t *offset)
{	char buffer[256];
      int i;
    
   //struct usb_lcd *devs;
  struct usb_device *dev=NULL;
   //usb_dev_handle *handle;
   //devs = (struct usb_lcd *)file->private_data;
   //if (devs == NULL)
	//return -ENODEV;
  
   for(i=0;i<length && i<BUF_LEN;i++)
{
	get_user(Message[i],puser+i);
}
        Message_Ptr=Message;
	 if(strcmp(Message_Ptr,"LCD_CLEAR_DISP")==0){
	 q.val1=1;
	 printk(KERN_INFO "The message is %d\n",q.val1);}
	else if(strcmp(Message_Ptr,"LCD_CURSOR_HOME")==0){
	 q.val1=2;
	 printk(KERN_INFO "The message is %d\n",q.val1);}
       else if(strcmp(Message_Ptr,"LCD_ENTRY_DEC")==0){
	 q.val1=4;
	 printk(KERN_INFO "The message is %d\n",q.val1);}
	else if(strcmp(Message_Ptr,"LCD_ENTRY_DEC_SHIFT")==0){
	 q.val1=5;
	 printk(KERN_INFO "The message is %d\n",q.val1);}
	else if(strcmp(Message_Ptr,"LCD_ENTRY_INC_")==0){
	 q.val1=6;
	 printk(KERN_INFO "The message is %d\n",q.val1);}
       else if(strcmp(Message_Ptr,"LCD_ENTRY_INC_SHIFT")==0){
	 q.val1=7;
	 printk(KERN_INFO "The message is %d\n",q.val1);}
       else if(strcmp(Message_Ptr,"LCD_DISP_OFF")==0){
	 q.val1=8;
	 printk(KERN_INFO "The message is %d\n",q.val1);}
      else if(strcmp(Message_Ptr,"LCD_DISP_ON")==0){
	 q.val1=12;
	 printk(KERN_INFO "The message is %d\n",q.val1);}
	else if(strcmp(Message_Ptr,"LCD_DISP_ON_BLINK")==0){
	 q.val1=13;
	 printk(KERN_INFO "The message is %d\n",q.val1);}
    else if(strcmp(Message_Ptr,"LCD_DISP_ON_CURSOR")==0){
	 q.val1=14;
	 printk(KERN_INFO "The message is %d\n",q.val1);}
	else if(strcmp(Message_Ptr,"LCD_DISP_ON_CURSOR_BLINK")==0){
	 q.val1=15;
	 printk(KERN_INFO "The message is %d\n",q.val1);}
	else if(strcmp(Message_Ptr,"LCD_MOVE_CURSOR_LEFT")==0){
	 q.val1=16;
	 printk(KERN_INFO "The message is %d\n",q.val1);}
	else if(strcmp(Message_Ptr,"LCD_MOVE_CURSOR_RIGHT")==0){
	 q.val1=20;
	 printk(KERN_INFO "The message is %d\n",q.val1);}
else if(strcmp(Message_Ptr,"LCD_MOVE_DISP_LEFT")==0){
	 q.val1=24;
	 printk(KERN_INFO "The message is %d\n",q.val1);}
else if(strcmp(Message_Ptr,"LCD_MOVE_DISP_RIGHT")==0){
	 q.val1=28;
	 printk(KERN_INFO "The message is %d\n",q.val1);}
else if(strcmp(Message_Ptr,"LCD_FUNCTION_4BIT_1LINE")==0){
	 q.val1=32;
	 printk(KERN_INFO "The message is %d\n",q.val1);}
else if(strcmp(Message_Ptr," LCD_FUNCTION_4BIT_2LINES")==0){
	 q.val1=40;
	 printk(KERN_INFO "The message is %d\n",q.val1);}
else if(strcmp(Message_Ptr," LCD_FUNCTION_8BIT_1LINE")==0){
	 q.val1=48;
	 printk(KERN_INFO "The message is %d\n",q.val1);}
else if(strcmp(Message_Ptr," LCD_FUNCTION_8BIT_2LINES")==0){
	 q.val1=56;
	 printk(KERN_INFO "The message is %d\n",q.val1);}
else
{
q.val1=60;
}
return 0;

}
ssize_t lcd_read(struct file *file,char __user *buffer,size_t length,loff_t *offset)
{
	
printk(KERN_INFO "The value is %d\n",q.val1);
if(raw_copy_to_user(buffer,&q,sizeof(args)))
		return -1;
      
	

return 0;	
}



static long lcd_ioctl(struct file *file, unsigned int ioctl_num, unsigned long ioctl_param)
{
	 int i;
   char *temp;
   char ch;
args q;
   switch (ioctl_num)
   {
      printk(KERN_INFO "Inside IOCTL Function\n");
      case IOCTL_SET_MSG:
        temp=(char *)ioctl_param;
        get_user(ch,temp); 
        for(i=0;ch && i<BUF_LEN;i++,temp++)
	get_user(ch,temp);
        lcd_write(file,(char *)ioctl_param,i,0);
        break;
    


      }
  return 0;
}
static const struct file_operations lcd_fops = {
        .owner =        THIS_MODULE,
        .read =         lcd_read,
        .write =        lcd_write,
        .open =         lcd_open,
	.unlocked_ioctl = lcd_ioctl,
        .release =      lcd_release,
};

/*
 * usb class driver info in order to get a minor number from the usb core,
 * and to have the device registered with the driver core
 */
static struct usb_class_driver lcd_class = {
        .name =         "USBasp",
        .fops =         &lcd_fops,
        .minor_base =   USBLCD_MINOR,
};

static int lcd_probe(struct usb_interface *interface, const struct usb_device_id *id)
{	printk(KERN_INFO "entering probe function");
	struct usb_lcd *dev = NULL;
	struct usb_host_interface *iface_desc;
	struct usb_endpoint_descriptor *endpoint;
	size_t buffer_size;
	int i;
	int retval = -ENOMEM;
	struct usb_dev_handle *handle=NULL;
 	
	printk(KERN_INFO "Inside char_driver_init function \n");
	devno=MKDEV(MAJOR_NO,MINOR_NO);
   
   printk(KERN_INFO "Major and Minor device numbers has been generated successfully.\n");
   printk(KERN_INFO "Major Device no. = %d, Minor Device no. = %d \n",MAJOR(devno),MINOR(devno));

   	if((class_cr=class_create(THIS_MODULE,"LCD_driver"))==NULL)
   	{
      	unregister_chrdev_region(devno,1);
      	return -1;  
   	}

   	if(device_create(class_cr,NULL,devno,NULL,"usblcd")==NULL)
   	{
       	class_destroy(class_cr);
      	unregister_chrdev_region(devno,1);
      	return -1;
   	}

   	cdev_init(&c_dev,&lcd_fops);
   	if(cdev_add(&c_dev,devno,1) == -1)
   	{
        device_destroy(class_cr,devno);
        class_destroy(class_cr);
        unregister_chrdev_region(devno,1);
        return -1;
   	}
	dev = kzalloc(sizeof(*dev), GFP_KERNEL);
	if (dev == NULL) {
		printk(KERN_INFO "Out of memory");
	}
	kref_init(&dev->kref);
	//sema_init(&dev->limit_sem, USB_LCD_CONCURRENT_WRITES);
	dev->udev = usb_get_dev(interface_to_usbdev(interface));
	dev->interface = interface;
	usb_set_intfdata(interface, dev);
	retval = usb_register_dev(interface, &lcd_class);
	if (retval) {
		printk(KERN_INFO "Not able to get a minor for this device.");
		usb_set_intfdata(interface, NULL);
		}
	return retval;
}

		
static void lcd_disconnect(struct usb_interface *interface)
{
	struct usb_lcd *dev;
        int minor = interface->minor;
	mutex_lock(&openmutex);
        dev = usb_get_intfdata(interface);
        usb_set_intfdata(interface, NULL);
	mutex_unlock(&openmutex);
        usb_deregister_dev(interface, &lcd_class);
 	kref_put(&dev->kref, lcd_delete);
	dev_info(&interface->dev, "USB LCD #%d now disconnected\n", MINOR_NO);
}

static struct usb_driver lcd_driver = {
	.name =		"lcd%d",
	.probe =	lcd_probe,
	.disconnect =	lcd_disconnect,
	//.suspend =	lcd_suspend,
	//.resume =	lcd_resume,
	.id_table =	id_table,
	//.supports_autosuspend = 1,
};

int usb_lcd_init(void)
{	printk(KERN_INFO "This is lcd project");
	int result;
	result = usb_register(&lcd_driver);
	if (result)
		printk(KERN_INFO "usb_register failed. Error number %d", 		result);
	
	return result;
}


void usb_lcd_exit(void)
{
	usb_deregister(&lcd_driver);
	cdev_del(&c_dev);
   	device_destroy(class_cr,devno);
   	class_destroy(class_cr);
   	unregister_chrdev_region(devno,1);
	printk(KERN_INFO "Char Driver unregistered successfully \n");
        printk(KERN_NOTICE "Leaving Kernel\n");
}

module_init(usb_lcd_init);
module_exit(usb_lcd_exit);

MODULE_AUTHOR("HARSHUPRI");
MODULE_DESCRIPTION("LCDDRIVER");
MODULE_LICENSE("GPL");








       
	
   


