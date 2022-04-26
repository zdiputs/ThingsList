#include "main.h"
/********************************************************************************
事情List                   SUPPER_FRAME
  步骤List                 LISTLIST_FRAME
    每个步骤里面划3个环节   StepSegFlag
比如：
事情A-----------------------步骤1    环节Pre   环节Poll   环节JUMP  
事情B------|           |----步骤2
          |            |----步骤3
          |
          |---------------步骤1
          |---------------步骤2
          |---------------步骤3
          |---------------步骤4
********************************************************************************/
//-----------------------事情List-------------------------------------------------------------------

typedef struct SupperFrame{
  signed char    SupJumpOn;                                          //大于零 跳转和毫秒计数的必要条件，小于等于零用来暂停用，定时器计数也清零
  signed short   SupState;                                          //一件事情里面的第几个小case 这件事情的进程状态、0状态定义为什么都不干的状态
  unsigned int   SupTimeCnt;                                      //毫秒计数 SupState改变瞬间清零
  char * text;                                                  //这件事的概述 不做具体的用处 可以看下
  signed short   (* SupPoll)(unsigned char,signed short );      //第一个参数传入Poll序号，
}SUPPER_FRAME;

#define SupMainPollCode         (-4)//主调用[不会操作到SupJumpOn、SupState、SupTimeCnt]
#define SupStopSwitchCode       (-3)//暂停 跳转关闭  将不会运行switch
#define SupPauseCaseCode        (-2)//暂停 跳转关闭  停留在case中 
#define SupNoStaGoon            (-1)//不指定继续  跳转放行

#define SupJumpEn       (sppuerList[i].SupJumpOn>0)//每个跳转受外部干预的跳转条件，如果需要受外部干预暂停的case且&&上这个条件
#define SupMState       (sppuerList[i].SupState)  //当前事情的状态
#define SupMTimeCnt      (sppuerList[i].SupTimeCnt)//当前时间的毫秒计数

#define supperNum       2       //事情数
#define ListListANum    3       //事情里面的步骤数
#define ListListBNum    3       //事情里面的步骤数

signed short SupPreSwitchCase(unsigned char i,signed short Config);

SUPPER_FRAME sppuerList[supperNum];//事先声明一下有这个列表  在下面定义



//------------------------------步骤List 事情里面的步骤-------------------------------

typedef enum STEP{
    STEP_PRE = 1,//环节1第一次进这个步骤的处理运行一次
    STEP_POLL,//环节2间隔调用 环节3
    STEP_JUM  //P环节3判断的跳转
}STEPS;
typedef struct listsTaskFrame{

  const char * title;          //步骤的标题 在外部调用的时候可以查找匹配的字符串找出步骤列表中的序号 
  STEPS StepSegFlag;            //一个步骤分成3个环节  、  
  unsigned int internalCntMax;  //定时调用的超时时间单位毫秒
  unsigned short nextIndex;     //下一状态序号 默认的下一状态JumpIndexFun会具体判断
  void   (* JumpIndexFun)(unsigned short *);
}LISTLIST_FRAME;

signed short supperTaskA(unsigned char i,signed short Config);
signed short supperTaskB(unsigned char i,signed short Config);


//----------------------------------------------------------------------------------
//---------------事情-----------------------------------------------------------------------
//----------------------------------------------------------------------------------
//List是大事情的表。先分大事情。
//ListList是大小事情里面细分的的各节点步骤的表。
 SUPPER_FRAME sppuerList[supperNum];
//设置状态的判断
signed short SupPreSwitchCase(unsigned char i,signed short Config)
{
  if(Config==SupMainPollCode)//主调用[不会操作到SupJumpOn、SupState、SupTimeCnt]
  {
    return Config;
  }
  if(Config==SupStopSwitchCode)//暂停 跳转关闭  将不会运行switch
  {
    sppuerList[i].SupJumpOn=0;
    return Config;
  }
  
  if(Config==SupPauseCaseCode)//暂停 跳转关闭  停留在case中 
  {
    sppuerList[i].SupJumpOn=0;
    return Config;
  }
  if(Config==SupNoStaGoon)//不指定继续  跳转放行
  {
    sppuerList[i].SupJumpOn=1;//所有跳转可以
    return Config;
  }
  if(Config>=0)//指定继续、跳转到0一般为什么都不做的空闲状态、
  {
    sppuerList[i].SupState=Config;
    sppuerList[i].SupJumpOn=1;
    return Config;
  }
  return Config;
}

signed short supperTaskA(unsigned char i,signed short Config);
signed short supperTaskB(unsigned char i,signed short Config);
SUPPER_FRAME sppuerList[supperNum] = 
{
  {1,1,0,"事情A",supperTaskA},     
  {1,1,0,"事情B",supperTaskB}
 
};

//每个事件时间计值的++
//放到毫秒中断计数中
void SupTimeCntFun(void)
{
  unsigned char i=0;
  for(i=0;i<supperNum;i++)
  {
    if(SupJumpEn)
    {
      sppuerList[i].SupTimeCnt++;
    }else
    {
      sppuerList[i].SupTimeCnt=0;
    }
  }
}
//流程控制循环体
//放到主循环当中
void SuperRunSequence(void)
{
  unsigned char i=0;
  for(i=0;i<supperNum;i++)
  {
    //i传入在List序号，
    //第二个参数传入-4 State不受影响  不会操作到SupJumpOn跳转开关
    (*(sppuerList[i].SupPoll))(i,SupMainPollCode);
  }
  
}




//这里放具体的事情函数
//这里放2件事情吧 一件事情A 一件事情B
//----------------------------------------------------------
//------------------事情A------------------------------------
//----------------------------------------------------------
void *pNull;
//A事情 中的 A1步骤
//每个步骤概况成三个函数 第一个步骤是第一次进  第二个步骤间隔调用 第三个步骤 跳转的判断

void ListListA1GowhereJudgeFun(unsigned short *pVar)
{
  return;
}
//A大事情 中的A2步骤
//每个步骤概况成三个函数 第一个步骤是第一次进  第二个步骤间隔调用 第三个步骤 跳转的判断


void ListListA2GowhereJudgeFun(unsigned short *pVar)
{
  return;
}

//A事情 中的 A3步骤  
//每个步骤概况成三个函数 第一个步骤是第一次进  第二个步骤间隔调用 第三个步骤 跳转的判断

void ListListA3GowhereJudgeFun(unsigned short *pVar)
{
  return;
}


//A事情中 的3行记录分别是三个步骤 
LISTLIST_FRAME sppuerListListA[ListListANum]={
  {"初始化",0,100,1,ListListA1GowhereJudgeFun},//A1步骤记录体 
  {"去转动",0,100,2,ListListA2GowhereJudgeFun},//A2步骤记录体
  {"停止转",0,100,0,ListListA3GowhereJudgeFun}//A2步骤记录体

};

signed short supperTaskA(unsigned char i,signed short Config)
{
  if(SupPreSwitchCase(i,Config)==SupStopSwitchCode)
  {
    return Config;
  }
 
  (*(sppuerListListA[SupMState].JumpIndexFun))((unsigned short *)&(SupMState));
  
  return Config;
}


//----------------------------------------------------------
//------------------事情B-----------------------------------
//----------------------------------------------------------

//A事情 中的 A1步骤
//每个步骤概况成三个函数 第一个步骤是第一次进  第二个步骤间隔调用 第三个步骤 跳转的判断
void ListListB1GowhereJudgeFun(unsigned short *pVar)
{
  return;
}

//A大事情 中的A2步骤
//每个步骤概况成三个函数 第一个步骤是第一次进  第二个步骤间隔调用 第三个步骤 跳转的判断
void ListListB2GowhereJudgeFun(unsigned short *pVar)
{
  return;
}

//B事情 中的 A3步骤  
//每个步骤概况成三个函数 第一个步骤是第一次进  第二个步骤间隔调用 第三个步骤 跳转的判断
void ListListB3GowhereJudgeFun(unsigned short *pVar)
{
  return;
}


//A事情中 的3行记录分别是三个步骤 
LISTLIST_FRAME sppuerListListB[ListListBNum]={
  {"初始化",0,100,1,ListListB1GowhereJudgeFun},//B1步骤记录体 
  {"去转动",0,100,2,ListListB2GowhereJudgeFun},//B2步骤记录体
  {"停止转",0,100,0,ListListB3GowhereJudgeFun}//B3步骤记录体

};
signed short supperTaskB(unsigned char i,signed short Config)
{
  if(SupPreSwitchCase(i,Config)==SupStopSwitchCode)return Config;
  
  (*(sppuerListListB[SupMState].JumpIndexFun))((unsigned short *)&(SupMState));
  
  return Config;
}


