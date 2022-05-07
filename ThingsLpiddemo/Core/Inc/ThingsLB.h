#ifndef __THINGSLB_H
#define __THINGSLB_H
#include "ThingsL.h"
 typedef struct bTings
{
  unsigned char para1;
  unsigned char para2;
} TINGS_B;
#define ListListBNum 3
extern TINGS_B tingsB_runData;//事情B的运行参数
extern LISTLIST_FRAME ThingsL_ListListB[ListListBNum]; //事情B中的步骤列表声明
#endif