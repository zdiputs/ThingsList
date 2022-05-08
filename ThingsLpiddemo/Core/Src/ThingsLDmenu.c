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
#include "ThingsLDmenu.h"
//这个事情【菜单的显示】


//-----------------事情D的步骤预处理函数--------其返回值的如果为JumpOver则会使得步骤跳过定时回调函数-----------------------
JUMPTYPE funcStepD1Pre(void * ThingsL_perSteprun)
{
  
   MenuCtrl();
  return JumpLeft;
}

//-----------------事情D的步骤定时调用函数------其返回值如果为JumpStay则会使一直按间隔时间执行定时回调函数----------------
JUMPTYPE funcStepD1Jue(void * ThingsL_perSteprun)
{
  return JumpLeft;
}

//步骤名
//步骤环节
//定时回调超时值
//预设JumpLeft(事情状态=步骤列表的序号)
//预设JumpRight(事情状态=步骤列表的序号)
//预处理环节函数
//定时回调函数
LISTLIST_FRAME ThingsL_ListListD[ListListDNum] = {
  {"D步骤1", STEP_PRE,STEP_0, 0, JumpS0,JumpS0,funcStepD1Pre,funcStepD1Jue}, // B1步骤记录体  一行记录与一件步骤对应
};