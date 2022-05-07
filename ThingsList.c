#include "main.h"
#include "string.h"
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
  Auth:火星火箭      (z)diputs 
  http:iamrobot.top https://github.com/zdiputs
  https:stgui.com   https://gitee.com/diputs
********************************************************************************/
#define NotFind 0xffff
#define ThingsL_MainPollCode (-555)   //主调用[不会操作到ThingsL_JumpOn、ThingsL_State、ThingsL_TimeCnt]
#define ThingsL_StopSwitchCode (-444) //暂停switch 跳转关闭  将不会运行switch
#define ThingsL_PauseCaseCode (-333)  //暂停case 跳转关闭  停留在case中  停止步骤的跳转 一直在步骤循环调用
#define ThingsL_StaGoon (-222)      //不指定继续（状态值为负数），或指定继续（状态值大于等于0）   跳转放行
#define ThingsL_PollNum (ThingsL_List[i].ThingsL_JumpOn) 							//驻留次数 如果为附属就不赋值
#define ThingsL_PollNumSelfSub     if(ThingsL_PollNum>0&&ThingsL_PollNum!=ThingsL_PauseCaseCode){ThingsL_PollNum--;}//循环次数自减  不暂停case的情况下才能自减
#define ThingsL_JumpIsEn 			(ThingsL_PollNum <= 0 && ThingsL_PollNum != ThingsL_PauseCaseCode) //减到0或负值才能单次跳转反向，不然就是循环次数
#define ThingsL_MState 				(ThingsL_List[i].ThingsL_State)                              //当前事情的状态（同时为步骤列表的序号）
#define ThingsL_MTimeCnt 			(ThingsL_List[i].ThingsL_TimeCnt)                          //当前时间的毫秒计数
#define ThingsL_MTimeMax  			(ThingsL_List[i].plistlist[j].internalCntMax)        //定时回调的超时数
#define ThingsL_StepSegMod    		(ThingsL_List[i].plistlist[j].StepSegMod)     		//步骤中三种模式  第一种只运行预处理函数 第二章只运行定时函数 第三种先运行预处理函数再运行定时函数
#define ThingsL_StepSegFlag    		(ThingsL_List[i].plistlist[j].StepSegFlag)     		//步骤中当前环节标志
#define ThingsL_StepPreFunc    		(*ThingsL_List[i].plistlist[j].funStepPre)(ThingsL_List[i].thingsrundata)//预处理环节
#define ThingsL_StepPollFunc   		((*ThingsL_List[i].plistlist[j].funStepJue)(ThingsL_List[i].thingsrundata))//定时调用环节
#define ThingsL_erRunSeqFun			(*ThingsL_List[i].ThingsL_Poll)
#define ThingsL_StepLeftNextIndex    (ThingsL_List[i].plistlist[j].nextleftIndex)   //下一状态左跳一般定义为顺序执行的序号 该事情状态赋值左跳值
#define ThingsL_StepRightNextIndex    (ThingsL_List[i].plistlist[j].nextrightIndex) //下一状态右跳一般定义为返回执行的序号 该事情状态赋值右跳值
/******************************************************************************************************************************************
 * 事情步骤列表
  [步骤1预处理环节]
  [步骤1定时处理环节]
     |ThingsL_StepLeftNextIndex=2左跳
     v
  [步骤2预处理环节]<------|
  [步骤2定时处理环节]     |
     |                   |
     v                   |
  [步骤3预处理环节]       |
  [步骤3定时处理环节]     |
     |                   |
     v                   |
  [步骤4预处理环节]       |
  [步骤4定时处理环节]---->|ThingsL_StepRightNextIndex=2右跳条件满足时
     |
     v          
  [步骤5预处理环节]  /___
  [步骤5定时处理环节]____|循环执行某一个步骤中的定时回调函数表示“驻留”JumpStay
****************************************************************************************************************************************/
#define ThingsL_perNum 2    //事情数
#define ListListANum 3 //事情里面的步骤数
#define ListListBNum 3 //事情里面的步骤数

//------------------------------步骤List 事情里面的步骤-------------------------------
typedef enum Jumptype
{
  JumpStay=-4,   //驻留     具体步骤环节函数返回0时
  JumpLeft,     //向左跳转 具体步骤环节函数返回1时  
  JumpRight,    //向右跳转 具体步骤环节函数返回2时 另外一个方向
  JumpOver,     //跳过定时环节函数
  JumpS0,
  JumpS1,
  JumpS2,
  JumpS3,
  JumpS4,
  JumpS5,
  JumpS6,
  JumpS7,
  JumpS8,
  JumpS9,
  JumpS10,
  JumpS11,
  JumpS12,
  JumpS13,
  JumpS14,
  JumpS15,
  JumpS16,
  JumpS17,
  JumpS18,
  JumpS19,
  JumpS20,
} JUMPTYPE;
typedef enum STEP//一步骤下的环节模式
{
  STEP_PRE = 0, //只运行预处理环节
  STEP_POLL,    //只运行定时回调环节
  STEP_PREPOLL, //先立即执行预处理函数 再超时后执行定时回调函数
} STEPS;
typedef enum STEPSTATUS//一步骤下的环节状态
{
  STEP_0 = 0, //只运行预处理环节
  STEP_1,    //只运行定时回调环节
  STEP_2,
} STEPSTA;
typedef struct listsTaskFrame//步骤
{
  const char *title;           //步骤的标题 在外部调用的时候可以查找匹配的字符串找出步骤列表中的序号
  STEPS  StepSegMod;           //步骤环节预设的三种模式 第一种只运行预处理函数，第二种只运行定时函数，第三种先运行预处理函数再运行定时函数 
  STEPSTA StepSegFlag;           //一个步骤分成3个环节,步骤运行在哪个环节的状态
  unsigned int internalCntMax; //一个步骤分成3个环节,步骤运行在哪个环节的状态
  unsigned short nextleftIndex;    //下一状态序号 默认的下一状态JumpIndexFun会具体判断
  unsigned short nextrightIndex;    //下一状态序号 默认的下一状态JumpIndexFun会具体判断
  JUMPTYPE (*funStepPre)(void *);//每个步骤的预处理函数  返回JumpOver时意味着跳过定时函数直接运行左跳转状态，返回其他时按预处理一下后再执行定时
  JUMPTYPE (*funStepJue)(void *);//每个步骤的退出选择函数 同时是定时回调  返回值JumpStay时意味着驻留在定时函数中定时执行 同时事情状态中的驻留计数自减1
  
} LISTLIST_FRAME;
//-----------------------事情List-------------------------------------------------------------------
typedef struct ThingsL_perFrame//事情
{
  char *text;              //一般可以设置成2个中文1个英文0作为结束符号  这样作为事情的名称  外部查找发送指令时能用到
  signed short ThingsL_JumpOn;  //驻留计数
  signed short ThingsL_State;   //一件事情里面的第几个小case 这件事情的进程状态、0状态定义为什么都不干的状态
  unsigned int ThingsL_TimeCnt; //毫秒计数
  //第一个参数传入Poll序号，第二个参数跳转状态 负数则不赋值进结构体 ，第三个参数驻留 如果过为ThingsL_PauseCaseCode则不赋值进结构体
  //列表中的这个位置函数 即可以放主循环轮询调用 也可以外部调用 控制内部跳转
  signed short (*ThingsL_Poll)(unsigned char, signed short, signed int);
  LISTLIST_FRAME *plistlist;//步骤指针、将一件事情指向一组步骤
  void * thingsrundata;//事情的运行参数的指针
} ThingsL_PER_FRAME;
signed short ThingsL_perTaskA(unsigned char i, signed short Config, signed int Stay);
signed short ThingsL_perTaskB(unsigned char i, signed short Config, signed int Stay);

ThingsL_PER_FRAME ThingsL_List[ThingsL_perNum];           //事情列表声明
LISTLIST_FRAME ThingsL_ListListA[ListListANum]; //事情A中的步骤列表声明
LISTLIST_FRAME ThingsL_ListListB[ListListBNum]; //事情B中的步骤列表声明
signed short ThingsL_perGeneralSch(unsigned char i, signed short Config, signed int Stay);//通用调度器
typedef struct aTings
{
  unsigned char para1;
  unsigned char para2;
} TINGS_A;
TINGS_A tingsA_runData;//事情A的运行参数
//-----------------事情A的步骤预处理函数--------其返回值的如果为JumpOver则会使得步骤跳过定时回调函数------------------
JUMPTYPE funcStepA1Pre(void * ThingsL_perSteprun){return JumpLeft;}
JUMPTYPE funcStepA2Pre(void * ThingsL_perSteprun){return JumpLeft;}
JUMPTYPE funcStepA3Pre(void * ThingsL_perSteprun){return JumpLeft;}
//-----------------事情A的步骤定时调用函数------其返回值如果为JumpStay则会使一直按间隔时间执行定时回调函数-------------------
JUMPTYPE funcStepA1Jue(void * ThingsL_perSteprun){return JumpLeft;}
JUMPTYPE funcStepA2Jue(void * ThingsL_perSteprun){return JumpLeft;}
JUMPTYPE funcStepA3Jue(void * ThingsL_perSteprun){return JumpLeft;}

typedef struct bTings
{
  unsigned char para1;
  unsigned char para2;
} TINGS_B;
TINGS_B tingsB_runData;//事情B的运行参数
//-----------------事情B的步骤预处理函数--------其返回值的如果为JumpOver则会使得步骤跳过定时回调函数-----------------------
JUMPTYPE funcStepB1Pre(void * ThingsL_perSteprun){return JumpLeft;}
JUMPTYPE funcStepB2Pre(void * ThingsL_perSteprun){return JumpLeft; }
JUMPTYPE funcStepB3Pre(void * ThingsL_perSteprun){return JumpLeft;}
//-----------------事情A的步骤定时调用函数------其返回值如果为JumpStay则会使一直按间隔时间执行定时回调函数----------------
JUMPTYPE funcStepB1Jue(void * ThingsL_perSteprun){return JumpLeft;}
JUMPTYPE funcStepB2Jue(void * ThingsL_perSteprun){return JumpLeft;}
JUMPTYPE funcStepB3Jue(void * ThingsL_perSteprun){return JumpLeft;}
//事情列表：是整件[大事]
ThingsL_PER_FRAME ThingsL_List[ThingsL_perNum] =
{
  {"事情A",1, JumpS0, 0, ThingsL_perGeneralSch,&ThingsL_ListListA[0],&tingsA_runData},//一行记录与一件事情对应
  {"事情B",1, JumpS0, 0, ThingsL_perGeneralSch,&ThingsL_ListListB[0],&tingsB_runData}//一行记录与一件事情对应
};

// A事情中 的3行记录分别是三个步骤
LISTLIST_FRAME ThingsL_ListListA[ListListANum] = {
  {"A步骤1", STEP_PREPOLL,STEP_0, 100, 1,0,funcStepA1Pre,funcStepA1Jue}, // A1步骤记录体  一行记录与一件步骤对应
  {"A步骤2", STEP_PREPOLL,STEP_0, 100, 2,0,funcStepA2Pre,funcStepA2Jue}, // A2步骤记录体  一行记录与一件步骤对应
  {"A步骤3", STEP_PREPOLL,STEP_0, 100, 0,0,funcStepA3Pre,funcStepA3Jue}  // A2步骤记录体  一行记录与一件步骤对应
};

// A事情中 的3行记录分别是三个步骤
//步骤名
//步骤环节
//定时回调超时值
//
LISTLIST_FRAME ThingsL_ListListB[ListListBNum] = {
  {"B步骤1", STEP_PREPOLL,STEP_0, 100, 1,0,funcStepB1Pre,funcStepB1Jue}, // B1步骤记录体  一行记录与一件步骤对应
  {"B步骤2", STEP_PREPOLL,STEP_0, 100, 2,0,funcStepB2Pre,funcStepB2Jue}, // B2步骤记录体  一行记录与一件步骤对应
  {"B步骤3", STEP_PREPOLL,STEP_0, 100, 0,0,funcStepB3Pre,funcStepB3Jue}  // B3步骤记录体  一行记录与一件步骤对应

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
    if(ThingsL_StepSegMod==STEP_PRE)//如果是只运行预处理函数就把这个Flag恢复成STEP_0
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


/*---自定义调度器-----------------------------------------------------------------------------
自定义调度器
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