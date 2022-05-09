#ifndef __THINGSEVENT_H
#define __THINGSEVENT_H

//-----------------------事件通知-------------------------------------------------------------------
#define ThingsLeventNumMax 20

#define EvtNon 0
#define EvtKey (1<<0)
#define EvtCom (1<<1)
#define EvtTy3 (1<<2)
#define EvtTy4 (1<<3)
#define EvtTy5 (1<<4)
typedef enum CUEVENT//一步骤下的环节状态
{
  NoneEvent     = -2,   //没找到事件
  EventFindTrigger,    //找到事件并触发
  EventFindNoTri,       //虽然找到但是无需触发
} EventT;
typedef struct _eventList//事件的结构体
{ 
  unsigned int ev_type;
  unsigned short ev_cmd;
  unsigned char ev_len;
  void *ev_Data;   
  unsigned int ev_thingsgetmask;//事件的事情掩码、支持最多32件事情的标记，反正同一件事情重复识别一个事件
} ThingsL_EVENT_List;

typedef struct _eventControl//步骤
{
  unsigned char cnt;//现存事件个数
} ThingsL_Event_Con;

extern ThingsL_EVENT_List thingsl_event_fifo[ThingsLeventNumMax+1];
EventT ThingsL_EventGetAndDel(unsigned int Evtype,unsigned char ThingsNum);
signed char ThingsL_PutEvent(unsigned int etype,unsigned short ev_cmd,unsigned char ev_len,void *ev_Data);
signed char ThingsL_GetEvent(unsigned int etype);
signed char ThingsL_DetEvent(signed char id);
#endif