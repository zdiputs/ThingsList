/********************************************************************************
"path": "C:\\Program Files\\IAR Systems\\Embedded Workbench 9.0\\",
"path": "D:\\iar9.20\\",
事情List                   ThingsL_PER_FRAME
步骤List                 LISTLIST_FRAME
每个步骤里面划3个环节   StepSegFlag
这里事情的序号是i  事情里面步骤的呼号是j
j=0    j=1    j=2     j=3    j=4
i=0事情A     步骤1  步骤2  步骤3   步骤4   步骤4
i=1事情B     步骤1  步骤2  步骤3   步骤4
i=2事情C     步骤1  步骤2  步骤3
*********************************************************************************
Auth:火星火箭 (z)diputs qq572981033 https://gitee.com/diputs/things-menu-list
********************************************************************************/
#include "ThingsLA.h"
#include "ThingsEvent.h"
//事情A示例
TINGS_A tingsA_runData;//事情A的运行参数


JUMPTYPE  funcAeventRcv(void * supperSteprun)//事件处理函数
{
  signed char ei=-1;
  signed char detflag=0;
  
  ei=ThingsL_GetEvent(EvtCom);//事件数组列队中可能存储着不同类型的事件 但是对于一件事情可能就只关心特定几个类型的事件
  if(ei>=0)//得到事件序号
  { 
    if((thingsl_event_fifo[ei].ev_thingsgetmask&0x00000001)==0)//这件事情从来没有被这件事抓到
    {
      //这里放事件的处理
      //这里放事件的处理
      //这里放事件的处理
      //这里放事件的处理
      thingsl_event_fifo[ei].ev_cmd=0;//事件类型
      thingsl_event_fifo[ei].ev_len=0;//事件的数据的长度
      thingsl_event_fifo[ei].ev_Data=0;//事件的数据
    }
    thingsl_event_fifo[ei].ev_thingsgetmask|=0x00000001;//这件事情已经被a事情得到过一次
    
    //这个事件其他事情是否想要得到 并且已经得到
    for(unsigned char i=0;i<ThingsL_perNum;i++)//遍历其他事情
    {
      if( (((ThingsL_List[i].eventmask)&EvtCom)!=0) &&//这件事也想得到这类事件
         (((thingsl_event_fifo[ei].ev_thingsgetmask)&(0x00000001<<i))==0)
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
  
  ei=-1;
  return JumpLeft;
}


//-----------------事情A的步骤预处理函数--------其返回值的如果为JumpOver则会使得步骤跳过定时回调函数------------------
JUMPTYPE funcStepA1Pre(void * ThingsL_perSteprun){return JumpLeft;}
JUMPTYPE funcStepA2Pre(void * ThingsL_perSteprun){return JumpLeft;}
JUMPTYPE funcStepA3Pre(void * ThingsL_perSteprun){return JumpLeft;}
//-----------------事情A的步骤定时调用函数------其返回值如果为JumpStay则会使一直按间隔时间执行定时回调函数-------------------
JUMPTYPE funcStepA1Jue(void * ThingsL_perSteprun){return JumpLeft;}
JUMPTYPE funcStepA2Jue(void * ThingsL_perSteprun){return JumpLeft;}
JUMPTYPE funcStepA3Jue(void * ThingsL_perSteprun){return JumpLeft;}
// A事情中 的3行记录分别是三个步骤
//步骤名
//步骤环节
//定时回调超时值
//预设JumpLeft(事情状态=步骤列表的序号)
//预设JumpRight(事情状态=步骤列表的序号)
//预处理环节函数
//定时回调函数
LISTLIST_FRAME ThingsL_ListListA[ListListANum] = {
  {"A步骤1", STEP_PREPOLL,STEP_0, 100, JumpS1,JumpS0,funcStepA1Pre,funcStepA1Jue}, // A1步骤记录体  一行记录与一件步骤对应
  {"A步骤2", STEP_PREPOLL,STEP_0, 100, JumpS2,JumpS0,funcStepA2Pre,funcStepA2Jue}, // A2步骤记录体  一行记录与一件步骤对应
  {"A步骤3", STEP_PREPOLL,STEP_0, 100, JumpS0,JumpS0,funcStepA3Pre,funcStepA3Jue}  // A2步骤记录体  一行记录与一件步骤对应
};