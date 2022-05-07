#include "ThingsLDTopic.h"
//这个事情【负责消息的流转 和 菜单的显示】
//现在还没做 准备做个消息留言板，发送方往留言板上塞消息、接收方从留言板上取消息并负责把消息删掉

//-----------------事情D的步骤预处理函数--------其返回值的如果为JumpOver则会使得步骤跳过定时回调函数-----------------------
JUMPTYPE funcStepD1Pre(void * ThingsL_perSteprun)
{
  extern void MenuCtrl(void);
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