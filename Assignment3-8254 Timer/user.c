#include "time.h"
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <sys/ioctl.h>

int main()
{
	args q;	
	int file_desc;
        char *DEVICE_NAME="/dev/timer0";
	file_desc=open(DEVICE_NAME,0);
	if(file_desc<0)
        {
		printf("cant open device fail:%s\n",DEVICE_NAME);
		exit(-1);
	}
	
       if(ioctl(file_desc,TIMER,&q)<0)
	{
	printf("failed to link ioctl");
	return -1;
	}
	printf("The timer output is %d",q.val);
	return 0;

}


 
	
