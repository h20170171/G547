#ifndef ADC0_H
#define ADC0_H
#include <linux/ioctl.h>
#define MAJOR_NUM 100
typedef struct
{
int msg1,msg2;
}args;
#define IOCTL_SET_MSG _IOW(MAJOR_NUM,1,args *)
#define IOCTL_GET_MSG _IOR(MAJOR_NUM,1,args *)
#endif


