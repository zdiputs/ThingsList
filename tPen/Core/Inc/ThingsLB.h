#ifndef __THINGSLB_H
#define __THINGSLB_H
#include "ThingsL.h"
 typedef struct bTings
{
  unsigned char para1;
  unsigned char para2;
} TINGS_B;
#define ListListBNum 3
extern TINGS_B tingsB_runData;//����B�����в���
extern LISTLIST_FRAME ThingsL_ListListB[ListListBNum]; //����B�еĲ����б�����
#endif