#ifndef __THINGSLCPID_H
#define __THINGSLCPID_H
#include "ThingsL.h"
#define ListListCNum 3
 typedef struct cTings
{
  unsigned char para1;
  unsigned char para2;
} TINGS_C;

extern TINGS_C tingsC_runData;//����C�����в���
extern LISTLIST_FRAME ThingsL_ListListC[ListListCNum];
#endif