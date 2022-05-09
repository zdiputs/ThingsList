/*********************************************************************************
Auth:火星火箭 (z)diputs qq572981033 https://gitee.com/diputs/things-menu-list
********************************************************************************/
#include "ThingsL.h"
#include "ThingsEvent.h"


//事件数组，这里事件数组的深度为ThingsLeventNumMax：20
//所有产生的事件都会放到这个数组当中
//事件的产生：利用ThingsL_PutEvent函数，传入事件类型，事件数据，事件数据长度，事件产生后计数自加1，超出数组深度则返回-1
//事件的取得：利用ThingsL_GetEvent函数，传入事件类型，如有类型匹配的事件，返回该事件下标，无复合类型的事件则返回-1
//事件的消耗：利用ThingsL_DetEvent函数，传入事件数组的下标，一般在Get到事件后 需要把这个事件从队列中删除, 这里仅仅是把事件控制结构体中的事件计数自减并将[id]-[cnt]之间的事件数组集体前移
//事件：事情间通讯的机制、跟外界的通讯协议类似，可以看做是内部事情间的通讯协议。
ThingsL_EVENT_List thingsl_event_fifo[ThingsLeventNumMax+1];//事件的队列
 
ThingsL_Event_Con thingsl_event_control={//事件队列的控制参数只需要一个计数器
  .cnt=0,
};

//etype   事件的类型
//ev_cmd  事件的指令
//ev_Data 事件的数据
//ev_len  事件数据的长度
//返回：成功写入返回队列序号，不成功返回负1
signed char ThingsL_PutEvent(unsigned int etype,unsigned short ev_cmd,unsigned char ev_len,void *ev_Data)
{
  if(thingsl_event_control.cnt<ThingsLeventNumMax)//不满
  {
    thingsl_event_fifo[thingsl_event_control.cnt].ev_type=etype;//事件类型
    thingsl_event_fifo[thingsl_event_control.cnt].ev_cmd=ev_cmd;//事件类型
    thingsl_event_fifo[thingsl_event_control.cnt].ev_len=ev_len;//事件的数据的长度
    thingsl_event_fifo[thingsl_event_control.cnt].ev_Data=ev_Data;//事件的数据
    thingsl_event_fifo[thingsl_event_control.cnt].ev_thingsgetmask=0;
    thingsl_event_control.cnt++;
    return thingsl_event_control.cnt;//现存事件个数
  }
  return -1;
}
//etype 需要检索的事件类型,事件的接收方调用这个函数形参输入事件的类型表示只读取特定类型的事件
//返回：检索到的第一个复合事件类型的数组下标，不成功返回负1
signed char ThingsL_GetEvent(unsigned int etype)
{
  unsigned char i=0;
  for(i=0;i<thingsl_event_control.cnt;i++)//检索事件数组，一旦检索到返回下标
  {
    if(thingsl_event_fifo[i].ev_type==etype)
    {
      return i;
    }
  }
  return -1;
  
}

//id 需要删除的事件 一般在Get到事件后 需要把这个事件从队列中删除 这里仅仅是把事件控制结构体中的事件计数自减并将[id]-[cnt]之间的事件数组集体前移
//返回：事件正常被删除则返回事件计数值，未被正常删除则
signed char ThingsL_DetEvent(signed char id)
{
  unsigned char i;
  if(id<thingsl_event_control.cnt&&
     id>=0&&                          //要删除的事件的下标范围正常
     thingsl_event_control.cnt>=1)    //事件数组中有事件存放
  {
    for(i=id;i<thingsl_event_control.cnt-1;i++)//下标为id的事件被取走了，[id]-[cnt]之间的事件数组集体前移
    {
      thingsl_event_fifo[i].ev_type             =       thingsl_event_fifo[i+1].ev_type;//事件类型
      thingsl_event_fifo[i].ev_cmd              =       thingsl_event_fifo[i+1].ev_cmd;//事件的cmd
      thingsl_event_fifo[i].ev_Data             =       thingsl_event_fifo[i+1].ev_Data;//事件的数据
      thingsl_event_fifo[i].ev_len              =       thingsl_event_fifo[i+1].ev_len;//事件的数据长度
      thingsl_event_fifo[i].ev_thingsgetmask    =       thingsl_event_fifo[i+1].ev_thingsgetmask;
    }
    thingsl_event_control.cnt--;//事件计数  这样算事件被消耗掉了
    return thingsl_event_control.cnt;

  }else
  {
    return -1;
  }
}

//遍历事件队列，待所有关联事情获取过改事件后删除这个事件 并将队列前移
//遍历事件队列，待所有关联事情获取过改事件后删除这个事件 并将队列前移
EventT ThingsL_EventGetAndDel(unsigned int Evtype,unsigned char ThingsNum)
{
  signed char ei=-1;
  signed char detflag=0;
  EventT evRtFlg=NoneEvent;

  ei=ThingsL_GetEvent(Evtype);//得到队列里首个类型匹配的序号
  
  if(ei>=0)//得到事件序号
  { 
    thingsl_event_fifo[ThingsLeventNumMax].ev_type         = thingsl_event_fifo[ei].ev_type;//事件的类型
    thingsl_event_fifo[ThingsLeventNumMax].ev_cmd          = thingsl_event_fifo[ei].ev_cmd;//事件命令
    thingsl_event_fifo[ThingsLeventNumMax].ev_Data         = thingsl_event_fifo[ei].ev_Data;//事件的数据
    thingsl_event_fifo[ThingsLeventNumMax].ev_len          = thingsl_event_fifo[ei].ev_len;//事件的数据长度
    thingsl_event_fifo[ThingsLeventNumMax].ev_thingsgetmask= thingsl_event_fifo[ei].ev_thingsgetmask;//事件类型
    evRtFlg=EventFindNoTri;
    if((thingsl_event_fifo[ei].ev_thingsgetmask&(0x00000001<<ThingsNum))==0)//这件事情从来没有被这件事抓到
    {
      evRtFlg=EventFindTrigger;//得到事件、并触发
    }
    
    thingsl_event_fifo[ei].ev_thingsgetmask|=(0x00000001<<ThingsNum);//这个时间已经被这
    //这个事件其他事情是否想要得到 并且已经得到
    for(unsigned char i=0;i<MAXTHINGNUM;i++)//遍历其他事情
    {
      if( (((ThingsL_List[i].eventmask)&Evtype)!=0) &&//这件事也想得到这类事件
          (((thingsl_event_fifo[ei].ev_thingsgetmask)&(0x00000001<<i))==0)&&
           ThingsNum!=i
           )//其他事情想要得到这个事件 但是 还没有被得到  
      {
        detflag=1;
      }
    }
    if(detflag==0)
    {
      ThingsL_DetEvent(ei);//等所有想得到这类事件的事情都得到后再进行删除
      
    }
  }
  
  return evRtFlg;
}





