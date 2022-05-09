
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
#include "main.h"
#include "string.h"
#include "ThingsEvent.h"//事件驱动的包含
#include "ThingsL.h"//ThingsList的事情列表和其调度器的包含
#include "ThingsLA.h"//事情A的包含
#include "ThingsLB.h"//事情B的包含
#include "ThingsLCPid.h"//事情C的包含 这里是pid的示例
#include "ThingsLDmenu.h"//事情D的包含 这里菜单的示例

ThingsL_PER_FRAME ThingsL_List[ThingsL_perNum];           //事情列表声明
signed short ThingsL_perGeneralSch(unsigned char i, signed short Config, signed int Stay);//通用调度器


//事情列表：是整件[大事]
ThingsL_PER_FRAME ThingsL_List[ThingsL_perNum] =
{
  {"事情A",1, JumpS0, 0, ThingsL_perGeneralSch,&ThingsL_ListListA[0],funcAeventRcv,EvtNon+EvtKey},//一行记录与一件事情对应
  {"事情B",1, JumpS0, 0, ThingsL_perGeneralSch,&ThingsL_ListListB[0],funcAeventRcv,EvtNon+EvtKey},//一行记录与一件事情对应
  {"控制C",1, JumpS0, 0, ThingsL_perGeneralSch,&ThingsL_ListListC[0],funcAeventRcv,EvtNon+EvtKey},//一行记录与一件事情对应
  {"显示D",1, JumpS0, 0, ThingsL_perGeneralSch,&ThingsL_ListListD[0],funcAeventRcv,EvtNon+EvtKey}//一行记录与一件事情对应
};

//外部调用
//这个函数是拿来给别的外部用的
#if 0//用法
SendThingsExtCode("事情A",1,ThingsL_PauseCaseCode);//停留在事情A的步骤1
SendThingsExtCode("事情A",1,2);               //停留在事情A的步骤1并驻留2次后继续步骤流转
SendThingsExtCode("事情A",1,2);               //停留在事情A的步骤1并驻留2次后继续步骤流转
SendThingsExtCode("事情A",ThingsL_StaGoon,ThingsL_StaGoon);//事情A 不指定事情的状态（步骤）继续步骤流转
SendThingsExtCode("事情A",1,ThingsL_StaGoon);//事情A 指定事情的状态（步骤）继续步骤流转
#endif
unsigned char SendThingsExtCode( char * pChar,signed short State,signed int Stay)
{
  unsigned short i;
  unsigned char findedflag=0;
  unsigned char str1[6];
  unsigned char str2[6];
  memcpy(str1,pChar,5);str1[5]=0;
  
  for(i=0;i<ThingsL_perNum;i++)
  {
    memcpy(str2,ThingsL_List[i].text,5);str2[5]=0;
    if(strcmp((char const *)str1,(char const *)str2)==0)
    {
      ThingsL_erRunSeqFun( i,State,Stay);//匹配就调用一次
      findedflag=1;
    }
    
  }
  return findedflag;//没有找到就返回零
}


/************************************************************************************
通用调度器
可以把这个放到每个自定义的[事情任务函数]中 这样会自动执行对应的步骤列表
一般事情列表中的每件事情记录都放这个函数，让调度器自动执行对应的步骤列表
*************************************************************************************/
signed short ThingsL_perGeneralSch(unsigned char i, signed short Config, signed int Stay)
{
  //类似二维数组  步骤列表的序号用j来表示吧、事情列表的序号都用i表示哦
  //i 和 j这两个变量名称跟宏定义很多东西相关不要改掉
  signed short j; 
  JUMPTYPE stayleftright=JumpStay;
  
  ThingsL_EventRcvFunc;//事件接收处理  具体事件具体在函数中处理
 
  if (Stay != ThingsL_MainPollCode)//驻留
  {
    ThingsL_PollNum = Stay;
  }
  if (Config >= 0)//指定状态的条件
  {
    ThingsL_MState = Config;//指定状态
  }
  if (ThingsL_PollNum == ThingsL_StopSwitchCode)//当前事情序号i停止运转
  {
    return ThingsL_StopSwitchCode; //暂停switch 不需要进行进switch case了
  }
  j = ThingsL_MState;//获取步骤号  一件事情的状态号就是步骤列表的运行序号j
  
  //预处理 环节
  //步骤中的定义不是只运行
  if(ThingsL_StepSegMod!=STEP_POLL&&ThingsL_StepSegFlag==STEP_0)//不是只运行Poll函数   步骤环节标志还是初始值只运行一
  {
    ThingsL_MTimeCnt=0;
    ThingsL_StepSegFlag=STEP_1;
    stayleftright=ThingsL_StepPreFunc;//执行预处理函数并取得其返回值
    if(ThingsL_StepSegMod==STEP_PRE)
    {
      ThingsL_StepSegFlag=STEP_0;
    }
    if(stayleftright==JumpOver)//获取预处理函数的返回值
    {
      ThingsL_MState=ThingsL_StepLeftNextIndex;
      ThingsL_StepSegFlag = STEP_0;//使得定时函数也不会运行
    }
    if(stayleftright>=0)//函数返回>=0则直接按返回值跳转
    {
      ThingsL_MState=stayleftright;
      ThingsL_StepSegFlag = STEP_0;//使得定时函数也不会运行
      
    }
  }
  
  //定时处理环节
  //步骤中定义不是只运行预处理函数
  if(ThingsL_StepSegMod!=STEP_PRE&&ThingsL_StepSegFlag!=STEP_0)//不是只运行Pre 函数  运行过预处理环节
  {
    ThingsL_StepSegFlag=STEP_2;
    if(ThingsL_MTimeCnt>ThingsL_MTimeMax)
    {
      ThingsL_MTimeCnt=0;
      ThingsL_PollNumSelfSub;
      stayleftright=ThingsL_StepPollFunc;//执行定时回调函数
      if((stayleftright!=JumpStay)&&ThingsL_JumpIsEn) //非驻留住跳转到下一个步骤
      {
        if(stayleftright>=0)
        {
          ThingsL_StepSegFlag=STEP_0;//复位步骤环节标志
          ThingsL_MState=stayleftright;//函数返回值是正数的话直接把函数返回值当作序号进行调准
          return Config;
        }else{//函数返回值是负数的话则根据预设的序号进行跳转
          ThingsL_StepSegFlag=STEP_0;//复位步骤环节标志
          if(stayleftright==JumpLeft)//向左边跳转
          {
            ThingsL_MState=ThingsL_StepLeftNextIndex;//更到下一个步骤 事情的状态值改变
          }else//非左即右
          {
            ThingsL_MState=ThingsL_StepRightNextIndex;//更到下一个步骤 事情的状态值改变
          }
        }
      }
    }
  }
  
  return Config;
}


/*---自定义状态机-----------------------------------------------------------------------------
自定义状态机
如果不用[通用调度器]ThingsL_perGeneralSch(可以把类似这种函数放进去事情回调函数中)，
在这个函数的switch case中直接写流程,则会跳过步骤列表里的内容.
{"事情A",1, 1, 0, NoSchedulerPutitLikethis,&ThingsL_ListListA[0],&tingsA_runData},
--------------------------------------------------------------------------------------------*/
void NoSchedulerPutitLikethis(unsigned char i,signed short ConfigState,signed int Stay)
{
  if(Stay!=ThingsL_MainPollCode)
  {
    ThingsL_PollNum=Stay;
  }
  if(ConfigState>0)
  {
    ThingsL_MState=ConfigState;
  }
  
  switch(ThingsL_MState)
  {
  case 0:ThingsL_MState=1;break;
  case 1:ThingsL_MState=2;break;
  case 2:ThingsL_MState=3;break;
  case 3:ThingsL_MState=0;break;
  
  }
}


//每个事件时间计值的++
//放到毫秒中断计数中
void ThingsL_TimeCntFun(void)
{
  unsigned char i = 0;
  for (i = 0; i < ThingsL_perNum; i++)
  {
    ThingsL_MTimeCnt++;
  }
}
//流程控制循环体
//放到主循环当中
void ThingsL_erRunSequence(void)
{
  for (unsigned char i = 0; i < ThingsL_perNum; i++)
  {
    ThingsL_erRunSeqFun(i, ThingsL_MainPollCode, ThingsL_MainPollCode);
  }
}






