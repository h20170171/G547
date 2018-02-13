#ifndef TIME_H
#define TIME_H
#include <linux/ioctl.h>
#define MAJOR_NUM 100
#define num 1
typedef struct
{
int val;
}args;
#define m args*
#define TIMER _IOW(MAJOR_NUM,num,m)

#endif


