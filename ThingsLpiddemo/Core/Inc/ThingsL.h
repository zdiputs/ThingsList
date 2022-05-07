#ifndef __THINGSL_H
#define __THINGSL_H
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
#define ThingsL_perNum 4    //事情数
#define ListListANum 3 //事情里面的步骤数
#define ListListBNum 3 //事情里面的步骤数

//------------------------------步骤List 事情里面的步骤-------------------------------
typedef enum Jumptype
{
  JumpStay=-4,   //驻留     
  JumpLeft,     //向左跳转 步骤列表预设的第一个跳转项目
  JumpRight,    //向右跳转 步骤列表预设的第二个跳转项目
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
  signed int internalCntMax;   //一个步骤分成3个环节,步骤运行在哪个环节的状态
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
  signed int   ThingsL_TimeCnt; //毫秒计数
  //第一个参数传入Poll序号，第二个参数跳转状态 负数则不赋值进结构体 ，第三个参数驻留 如果过为ThingsL_PauseCaseCode则不赋值进结构体
  //列表中的这个位置函数 即可以放主循环轮询调用 也可以外部调用 控制内部跳转
  signed short (*ThingsL_Poll)(unsigned char, signed short, signed int);
  LISTLIST_FRAME *plistlist;//步骤指针、将一件事情指向一组步骤
  void * thingsrundata;//事情的运行参数的指针
} ThingsL_PER_FRAME;






#endif