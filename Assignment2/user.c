#include "adc0.h"
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <sys/ioctl.h>
ioctl_set_msg(int file_desc,char *message)
{
int ret_val;
ret_val=ioctl(file_desc,IOCTL_SET_MSG,message);
if(ret_val<0)
{
	printf("ioctl_set_msg failed%d\n",ret_val);
	exit(-1);
}
}
ioctl_get_msg(int file_desc)
{
int ret_val;
char message;
ret_val=ioctl(file_desc,IOCTL_GET_MSG,message);
if(ret_val<0)
{
printf("ioctl_get_msg failed:%d\n",ret_val);
exit(-1);
}
printf("get_msg message:%s\n",message);
}
int main()
{
	args ret_val;	
	int file_desc;
	int msg;
        printf("enter the channel number");
        scanf("%d",&msg);
        char *DEVICE_NAME="/dev/ADC0";
	file_desc=open(DEVICE_NAME,0);
	if(file_desc<0)
        {
		printf("cant open device fail:%s\n",DEVICE_NAME);
		exit(-1);
	}
	ret_val.msg1=msg;
       if(ioctl(file_desc,IOCTL_GET_MSG,&ret_val)<0)
	{
	printf("failed to link ioctl");
	return -1;
	}
	printf("The ADC channel %d output is %d",msg,ret_val.msg2);
	return 0;
}


 
	
