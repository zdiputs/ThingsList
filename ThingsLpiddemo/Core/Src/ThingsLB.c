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
#include "ThingsLB.h"
//事情B示例
TINGS_B tingsB_runData;//事情B的运行参数

//-----------------事情B的步骤预处理函数--------其返回值的如果为JumpOver则会使得步骤跳过定时回调函数-----------------------
JUMPTYPE funcStepB1Pre(void * ThingsL_perSteprun){return JumpLeft;}
JUMPTYPE funcStepB2Pre(void * ThingsL_perSteprun){return JumpLeft; }
JUMPTYPE funcStepB3Pre(void * ThingsL_perSteprun){return JumpLeft;}

//-----------------事情B的步骤定时调用函数------其返回值如果为JumpStay则会使一直按间隔时间执行定时回调函数----------------
JUMPTYPE funcStepB1Jue(void * ThingsL_perSteprun){return JumpLeft;}
JUMPTYPE funcStepB2Jue(void * ThingsL_perSteprun){return JumpLeft;}
JUMPTYPE funcStepB3Jue(void * ThingsL_perSteprun){return JumpLeft;}


// A事情中 的3行记录分别是三个步骤
//步骤名
//步骤环节
//定时回调超时值
//预设JumpLeft(事情状态=步骤列表的序号)
//预设JumpRight(事情状态=步骤列表的序号)
//预处理环节函数
//定时回调函数
LISTLIST_FRAME ThingsL_ListListB[ListListBNum] = {
  {"B步骤1", STEP_PREPOLL,STEP_0, 100, JumpS1,JumpS0,funcStepB1Pre,funcStepB1Jue}, // B1步骤记录体  一行记录与一件步骤对应
  {"B步骤2", STEP_PREPOLL,STEP_0, 100, JumpS2,JumpS0,funcStepB2Pre,funcStepB2Jue}, // B2步骤记录体  一行记录与一件步骤对应
  {"B步骤3", STEP_PREPOLL,STEP_0, 100, JumpS0,JumpS0,funcStepB3Pre,funcStepB3Jue}  // B3步骤记录体  一行记录与一件步骤对应

};