## 这是一个单片机C语言程序

1. 事件驱动的2级列表
2. 1级列表为大事情
3. 2级列表为各个细分的步骤
   
   ## 特征
4. 可以将流程化的事情放在列表中管理
5. 这样做的好处是比较直观
6. 这个代码主要用于裸机

### 单片机型号

1. STM32F401CCU6

### 打开方式

1. STM32CubeIDE Version: 1.9.0  工程文件:./tPen/.project
2. iar 9.10.2 工程文件:./tPen/EWARM/Project.eww
3. 电路 ./Pen电路.pdf

### 主要代码

```C
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
/*-----------------------事情List-----------------------------------------------*/

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

/*------------------------------步骤List 事情里面的步骤------------------------*/

typedef enum STEP{
    STEP_PRE = 1,//环节1第一次进这个步骤的处理运行一次
    STEP_POLL,//环节2间隔调用 
    STEP_JUM  //环节3判断的跳转
}STEPS;
typedef struct listsTaskFrame{

  const char * title;          //步骤的标题 在外部调用的时候可以查找匹配的字符串找出步骤列表中的序号 
  STEPS StepSegFlag;            //一个步骤分成3个环节  、  
  unsigned int internalCntMax;  //定时调用的超时时间单位毫秒
  unsigned short nextIndex;     //下一状态序号 默认的下一状态JumpIndexFun会具体判断
  void   (* JumpIndexFun)(unsigned short *);
}LISTLIST_FRAME;


```
