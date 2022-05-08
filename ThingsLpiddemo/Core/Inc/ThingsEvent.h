#ifndef __THINGSEVENT_H
#define __THINGSEVENT_H

//-----------------------事件通知-------------------------------------------------------------------
#define ThingsLeventNumMax 20
typedef enum _eventype//事件的类型
{
  E_Key=0,
  E_A1,
  E_A2,
  E_A3,
  E_A4,
  E_A5,
} EVENTYPE;
typedef struct _eventList//事件的表
{
  EVENTYPE ev_type;
  unsigned char ev_len;
  void *ev_Data;          
} ThingsL_EVENT_List;

typedef struct _eventControl//步骤
{
  unsigned char cnt;//现存事件个数
} ThingsL_Event_Con;


signed char ThingsL_PutEvent(EVENTYPE etype,void *ev_Data,unsigned char ev_len);
signed char ThingsL_GetEvent(EVENTYPE etype);
signed char ThingsL_DetEvent(signed char id);
#endif