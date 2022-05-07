#ifndef __THINGSLA_H
#define __THINGSLA_H
#include "ThingsL.h"
 typedef struct aTings
{
  unsigned char para1;
  unsigned char para2;
} TINGS_A;
#define ListListANum 3
extern TINGS_A tingsA_runData;//事情A的运行参数
extern LISTLIST_FRAME ThingsL_ListListA[ListListANum]; //事情A中的步骤列表声明
#endif