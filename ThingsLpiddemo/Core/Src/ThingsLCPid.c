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
#include "ThingsLCPid.h"

TINGS_C tingsC_runData;//事情C的运行参数
typedef struct _pid{
    float SetTarget;   //定义设定值
    float CurrentValue;//定义实际值
    float err;//定义偏差值
    float err_last;//定义上一个偏差值
    float Kp,Ki,Kd;//定义比例、积分、微分系数
    float pidAdjust;//定义电压值（控制执行器的变量）
    float Sumerr; //定义积分值
}PIDPARA;

PIDPARA tpid;

void PID_init(){
 
    tpid.SetTarget=0.0;//设定
    tpid.CurrentValue=0.0;//当前量
    tpid.err=0.0;
    tpid.err_last=0.0;
    tpid.pidAdjust=0.0;//调整项目 转换成dac的电压或pwm的占空比
    tpid.Sumerr=0.0;//积分就是偏差的累加
    tpid.Kp=0.2;
    tpid.Ki=0.015;
    tpid.Kd=0.2;
 
}
// pid的过程：随着pidAdjust值的调整 偏差趋于0 目标值=实际值
float PID_realize(float set){
    tpid.err=set-tpid.CurrentValue;//偏差
    tpid.Sumerr+=tpid.err;//积分就是偏差的累加
    tpid.pidAdjust=tpid.Kp*tpid.err+                //偏差的比例系数
                 tpid.Ki*tpid.Sumerr+           //偏差积分的比例系数   积分：偏差的累加
                 tpid.Kd*(tpid.err-tpid.err_last); //偏差微分的比例系数  微分：这次偏差-上次偏差
    tpid.err_last=tpid.err;
    return tpid.pidAdjust;
}


//-----------------事情C的步骤预处理函数--------其返回值的如果为JumpOver则会使得步骤跳过定时回调函数------------------
JUMPTYPE funcStepC1Pre(void * ThingsL_perSteprun){return JumpLeft;}
JUMPTYPE funcStepC2Pre(void * ThingsL_perSteprun){return JumpLeft;}
JUMPTYPE funcStepC3Pre(void * ThingsL_perSteprun){return JumpLeft;}
//-----------------事情C的步骤定时调用函数------其返回值如果为JumpStay则会使一直按间隔时间执行定时回调函数-------------------
JUMPTYPE funcStepC1Jue(void * ThingsL_perSteprun)
{
  tpid.SetTarget=100;//当前值
  tpid.pidAdjust=PID_realize(tpid.SetTarget);
  return JumpLeft;
}
JUMPTYPE funcStepC2Jue(void * ThingsL_perSteprun){return JumpLeft;}
JUMPTYPE funcStepC3Jue(void * ThingsL_perSteprun){return JumpLeft;}
// C事情中 的3行记录分别是三个步骤
//步骤名
//步骤环节
//定时回调超时值
//预设JumpLeft(事情状态=步骤列表的序号)
//预设JumpRight(事情状态=步骤列表的序号)
//预处理环节函数
//定时回调函数
LISTLIST_FRAME ThingsL_ListListC[ListListCNum] = {
  {"C步骤1", STEP_PREPOLL,STEP_0, 100, JumpS1,JumpS0,funcStepC1Pre,funcStepC1Jue}, // C1步骤记录体  一行记录与一件步骤对应
  {"C步骤2", STEP_PREPOLL,STEP_0, 100, JumpS2,JumpS0,funcStepC2Pre,funcStepC2Jue}, // C2步骤记录体  一行记录与一件步骤对应
  {"C步骤3", STEP_PREPOLL,STEP_0, 100, JumpS0,JumpS0,funcStepC3Pre,funcStepC3Jue}  // C3步骤记录体  一行记录与一件步骤对应

};