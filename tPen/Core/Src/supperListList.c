#include "main.h"
/********************************************************************************
事情List                   SUPPER_FRAME
  步骤List                 LISTLIST_FRAME
    每个步骤里面划3个环节   StepSegFlag
比如：
事情A-----------------------步骤1    环节Pre   环节Poll
事情B------|           |----步骤2
          |            |----步骤3
          |
          |---------------步骤1
          |---------------步骤2
          |---------------步骤3
          |---------------步骤4

-------------------------------------------------------------------------------
也可以这么看
这里事情的序号是i  事情里面步骤的呼号是j
  事情A     步骤1  步骤2  步骤3   步骤4   步骤4
  事情B     步骤1  步骤2  步骤3   步骤4
  事情C     步骤1  步骤2  步骤3  
********************************************************************************/
//-----------------------事情List-------------------------------------------------------------------

typedef struct SupperFrame{
  
  signed short    SupJumpOn;   //驻留计数                                    
  signed short   SupState;    //一件事情里面的第几个小case 这件事情的进程状态、0状态定义为什么都不干的状态                                    
  unsigned int   SupTimeCnt;  //毫秒计数                                      
  char * text; //这件事的概述 拿来做外部命令时字符串匹配序号的查找                                             
  //第一个参数传入Poll序号，第二个参数跳转状态 负数则不赋值进结构体 ，第三个参数驻留 如果过为SupPauseCaseCode则不赋值进结构体
  //列表中的这个位置函数 即可以放主循环轮询调用 也可以外部调用 控制内部跳转
  signed short   (* SupPoll)(unsigned char,signed short,signed int );      
}SUPPER_FRAME;

#define NotFind  0xffff
#define SupMainPollCode         (-555)//主调用[不会操作到SupJumpOn、SupState、SupTimeCnt]
#define SupStopSwitchCode       (-444)//暂停switch 跳转关闭  将不会运行switch
#define SupPauseCaseCode        (-333)//暂停case 跳转关闭  停留在case中 
#define SupNoStaGoon            (-222)//不指定继续  跳转放行 
#define SupYsStaGoon            (-111)//指定继续  跳转放行 

#define SupPollNum          (sppuerList[i].SupJumpOn)//驻留次数 如果为附属就不赋值
#define SupPollNumSelfSub   if(SupPollNum>0&&SupPollNum!=SupPauseCaseCode){SupPollNum--;}//循环次数自减  不暂停case的情况下才能自减
#define SupJumpIsEn        (SupPollNum<=0&&SupPollNum!=SupPauseCaseCode)//减到0或负值才能单次跳转反向，不然就是循环次数
#define SupMState         (sppuerList[i].SupState)  //当前事情的状态
#define SupMTimeCnt       (sppuerList[i].SupTimeCnt)//当前时间的毫秒计数   

#define supperNum       2       //事情数
#define ListListANum    3       //事情里面的步骤数
#define ListListBNum    3       //事情里面的步骤数

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
  void   (* JumpIndexFun)(signed short i,signed short *);
}LISTLIST_FRAME;

signed short supperTaskA(unsigned char i,signed short Config,signed int Stay);
signed short supperTaskB(unsigned char i,signed short Config,signed int Stay);
 
void ListListA1GowhereJudgeFun(signed short i,signed short *j);
void ListListA2GowhereJudgeFun(signed short i,signed short *j);
void ListListA3GowhereJudgeFun(signed short i,signed short *j);
void ListListB1GowhereJudgeFun(signed short i,signed short *j);
void ListListB2GowhereJudgeFun(signed short i,signed short *j);
void ListListB3GowhereJudgeFun(signed short i,signed short *j);
SUPPER_FRAME sppuerList[supperNum];//事情列表声明
LISTLIST_FRAME sppuerListListA[ListListANum];//事情A中的步骤列表声明
LISTLIST_FRAME sppuerListListB[ListListBNum];//事情B中的步骤列表列表声明
SUPPER_FRAME sppuerList[supperNum] = 
{
  {1,1,0,"事情A",supperTaskA},     
  {1,1,0,"事情B",supperTaskB}
 
};
//A事情中 的3行记录分别是三个步骤 
LISTLIST_FRAME sppuerListListA[ListListANum]={
  {"A步骤1",0,100,1,ListListA1GowhereJudgeFun},//A1步骤记录体 
  {"A步骤2",0,100,2,ListListA2GowhereJudgeFun},//A2步骤记录体
  {"A步骤3",0,100,0,ListListA3GowhereJudgeFun}//A2步骤记录体

};
//A事情中 的3行记录分别是三个步骤 
LISTLIST_FRAME sppuerListListB[ListListBNum]={
  {"B步骤1",0,100,1,ListListB1GowhereJudgeFun},//B1步骤记录体 
  {"B步骤2",0,100,2,ListListB2GowhereJudgeFun},//B2步骤记录体
  {"B步骤3",0,100,0,ListListB3GowhereJudgeFun}//B3步骤记录体

};
//----------------------------------------------------------------------------------
//---------------事情-----------------------------------------------------------------------
//----------------------------------------------------------------------------------
//List是大事情的表。先分大事情。
//ListList是大小事情里面细分的的各节点步骤的表。
 SUPPER_FRAME sppuerList[supperNum];

//每个事件时间计值的++
//放到毫秒中断计数中
void SupTimeCntFun(void)
{
  unsigned char i=0;
  for(i=0;i<supperNum;i++)
  {
    sppuerList[i].SupTimeCnt++;
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
    (*(sppuerList[i].SupPoll))(i,SupMainPollCode,SupMainPollCode);
  }
  
}


//事情A中的步骤跳转
//这函数已经放到SuperRunSequence中轮询调用
//同时这个函数也可以使用被外部临时调用 可以使其驻留或暂停等
signed short supperTaskA(unsigned char i,signed short Config,signed int Stay)
{
  signed short j;//类似二维数组  步骤列表的序号用j来表示吧、事情列表的序号都用i表示哦
  //[事情A]   步骤1  步骤2  步骤3   步骤4   步骤4
  //事情B     步骤1  步骤2  步骤3   步骤4
  //事情C     步骤1  步骤2  步骤3  
  if(Stay!=SupMainPollCode)
  {
    SupPollNum=Stay;
  }
  if(Config>0)
  {
    SupMState=Config;
  }
  if(SupPollNum==SupStopSwitchCode) 
  {
    return SupStopSwitchCode;//暂停switch 不需要进行进switch case了
  }
  j=SupMState;//事情的状态是步骤的第二轴序号
  //事情列表的状态作为下标找出步骤跳转函数  
  //事情列表的状态地址作为形参传入这个跳转函数中进行判断
  //每一个步骤都有跳转函数事先放在listlist中
  //因为固定为事情A这个i是确定的
  (*(sppuerListListA[j].JumpIndexFun))(i,(unsigned short *)&(SupMState));
  
  return Config;
}

//事情B中的步骤跳转
//这函数已经放到SuperRunSequence中轮询调用
//同时这个函数也可以使用被外部临时调用 可以使其驻留或暂停等
signed short supperTaskB(unsigned char i,signed short Config,signed int Stay)
{
  unsigned j;//类似二维数组  步骤列表的序号用j来表示吧、事情列表的序号都用i表示哦
  //事情A     步骤1  步骤2  步骤3   步骤4   步骤4
  //[事情B]   步骤1  步骤2  步骤3   步骤4
  //事情C     步骤1  步骤2  步骤3 
  if(Stay!=SupMainPollCode)
  {
    SupPollNum=Stay;
  }
  if(Config>0)
  {
    SupMState=Config;
  }
  if(SupPollNum==SupStopSwitchCode) 
  {
    return SupStopSwitchCode;//暂停switch 不需要进行进switch case了
  }
  j=SupMState;//事情的状态是步骤的第二轴序号
  //事情列表的状态作为下标找出步骤跳转函数  
  //事情列表的状态地址作为形参传入这个跳转函数中进行判断
  //每一个步骤都有跳转函数事先放在listlist中
  //因为固定为事情B这个i是确定的
  (*(sppuerListListB[j].JumpIndexFun))(i,(unsigned short *)&(SupMState));
  
  return Config;
}



//这里放具体的事情函数
//这里放2件事情吧 一件事情A 一件事情B
//----------------------------------------------------------------------
//------------------事情A---这里三个函数就是事先放到列表里的3个步骤- 
//----------------------------------------------------------------------
void *pNull;
//A事情 中的 A1步骤
//每个步骤概况成三个函数 第一个步骤是第一次进  第二个步骤间隔调用 第三个步骤 跳转的判断
void ListListA1GowhereJudgeFun(signed short i,signed short *j)
{
  signed short jj=*j;
  if(sppuerListListA[jj].StepSegFlag==STEP_PRE)//环节Pre
  {
    sppuerListListA[jj].StepSegFlag=STEP_POLL;
  }
  
  if(sppuerListListA[jj].StepSegFlag==STEP_POLL)//环节Poll
  {
    if(SupMTimeCnt>sppuerListListA[jj].internalCntMax)
    {
      SupMTimeCnt=0;
      SupPollNumSelfSub;
      if(SupJumpIsEn)//可以跳转非驻留
      {
        *j=sppuerListListA[jj].nextIndex;
        sppuerListListA[*j].StepSegFlag=STEP_PRE;//下一个步骤的环节的复位
      }
    } 
  }
  return;
}
//A大事情 中的A2步骤
//每个步骤概况成三个函数 第一个步骤是第一次进  第二个步骤间隔调用 第三个步骤 跳转的判断
void ListListA2GowhereJudgeFun(signed short i,signed short *j)
{
  return;
}

//A事情 中的 A3步骤  
//每个步骤概况成三个函数 第一个步骤是第一次进  第二个步骤间隔调用 第三个步骤 跳转的判断
void ListListA3GowhereJudgeFun(signed short i,signed short *j)
{
  return;
}

//----------------------------------------------------------------------
//------------------事情B-----这里三个函数就是事先放到列表里的3个步骤- 
//----------------------------------------------------------------------
//A事情 中的 A1步骤
//每个步骤概况成三个函数 第一个步骤是第一次进  第二个步骤间隔调用 第三个步骤 跳转的判断
void ListListB1GowhereJudgeFun(signed short i,signed short *j)
{
  return;
}

//A大事情 中的A2步骤
//每个步骤概况成三个函数 第一个步骤是第一次进  第二个步骤间隔调用 第三个步骤 跳转的判断
void ListListB2GowhereJudgeFun(signed short i,signed short *j)
{
  return;
}

//B事情 中的 A3步骤  
//每个步骤概况成三个函数 第一个步骤是第一次进  第二个步骤间隔调用 第三个步骤 跳转的判断
void ListListB3GowhereJudgeFun(signed short i,signed short *j)
{
  return;
}






