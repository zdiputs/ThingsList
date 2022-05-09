#ifndef __THINGSEVENT_H
#define __THINGSEVENT_H

//-----------------------�¼�֪ͨ-------------------------------------------------------------------
#define ThingsLeventNumMax 20

#define EvtNon 0
#define EvtKey (1<<0)
#define EvtCom (1<<1)
#define EvtTy3 (1<<2)
#define EvtTy4 (1<<3)
#define EvtTy5 (1<<4)

typedef struct _eventList//�¼��ı�
{
  unsigned int ev_type;
  unsigned short ev_cmd;
  unsigned char ev_len;
  void *ev_Data;          
} ThingsL_EVENT_List;

typedef struct _eventControl//����
{
  unsigned char cnt;//�ִ��¼�����
} ThingsL_Event_Con;


signed char ThingsL_PutEvent(unsigned int etype,unsigned short ev_cmd,unsigned char ev_len,void *ev_Data);
signed char ThingsL_GetEvent(unsigned int etype);
signed char ThingsL_DetEvent(signed char id);
#endif