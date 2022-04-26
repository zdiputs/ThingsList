# 这是一个单片机C语言程序

- 事件驱动的2级列表
- 1级列表为大事情
- 2级列表为各个细分的步骤

### 特征

1. 可以将流程化的事情放在列表中管理
2. 这样做的好处是比较直观
3. 这个代码主要用于裸机

### 单片机型号

- STM32F401CCU6

### 打开方式

1. STM32CubeIDE Version: 1.9.0
- 工程文件:./tPen/.project
2. iar 9.10.2
- 工程文件:./tPen/EWARM/Project.eww
3. 电路
- ./Pen电路.pdf
  
### 主要代码

```C
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


#define supperNum 2 //大轮询的个数

signed short SupPreSwitchCase(unsigned char i,signed short Config);

SUPPER_FRAME sppuerList[supperNum];//事先声明一下有这个列表  在下面定义


//------------------------------步骤List我叫他List的List------------------------------------------------------------


typedef struct listsTaskFrame{

  const char * title;

  unsigned char firstinflg;          //第一次进的标记 0为没有进过 要进上面的这个函数的 1表示已经进过了去下一个定时函数
  void (* fistinFun)(void *);        //第一次进这个状态的函数

  unsigned int internalCntMax;  //定时调用的超时时间单位毫秒
  void (* internFun)(void *);        //定时的函数

  unsigned short nextIndex;       //下一状态序号 默认的下一状态JumpIndexFun会具体判断
  void   (* JumpIndexFun)(unsigned short *);



}LISTLIST_FRAME;

//------------------------------记录体------------------------------------------------------------
//List是大事情的表。先分大事情。具体看supperList.h里面的注释
//ListList是大小事情里面细分的的各节点步骤的表。 具体看supperListList.h里面的注释
 SUPPER_FRAME sppuerList[supperNum] = 
{
  {1,1,0,"事情A",supperTaskA},     
  {1,1,0,"事情B",supperTaskB}

};

//A事情中 的3行记录分别是三个步骤 
LISTLIST_FRAME sppuerListListA[ListListANum]={
  {"初始化",0,ListListA1FirstInFun,100,ListListA1internalFun,1,ListListA1GowhereJudgeFun},//A1步骤记录体 
  {"去转动",0,ListListA2FirstInFun,100,ListListA1internalFun,2,ListListA2GowhereJudgeFun},//A2步骤记录体
  {"停止转",0,ListListA3FirstInFun,100,ListListA1internalFun,0,ListListA3GowhereJudgeFun}//A2步骤记录体

};

//A事情中 的3行记录分别是三个步骤 
LISTLIST_FRAME sppuerListListB[ListListBNum]={
  {"初始化",0,ListListB1FirstInFun,100,ListListB1internalFun,1,ListListB1GowhereJudgeFun},//B1步骤记录体 
  {"去转动",0,ListListB2FirstInFun,100,ListListB1internalFun,2,ListListB2GowhereJudgeFun},//B2步骤记录体
  {"停止转",0,ListListB3FirstInFun,100,ListListB1internalFun,0,ListListB3GowhereJudgeFun}//B2步骤记录体

};
```
