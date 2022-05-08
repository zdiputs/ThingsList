/********************************************************************************
"path": "C:\\Program Files\\IAR Systems\\Embedded Workbench 9.0\\",
"path": "D:\\iar9.20\\",
����List                   ThingsL_PER_FRAME
����List                 LISTLIST_FRAME
ÿ���������滮3������   StepSegFlag
��������������i  �������沽��ĺ�����j
j=0    j=1    j=2     j=3    j=4
i=0����A     ����1  ����2  ����3   ����4   ����4
i=1����B     ����1  ����2  ����3   ����4
i=2����C     ����1  ����2  ����3
*********************************************************************************
Auth:���ǻ�� (z)diputs qq572981033 https://gitee.com/diputs/things-menu-list
********************************************************************************/

#include "main.h"
#include "ThingsLCPid.h"

TINGS_C tingsC_runData;//����C�����в���
typedef struct _pid{
    float SetTarget;   //�����趨ֵ
    float CurrentValue;//����ʵ��ֵ
    float err;//����ƫ��ֵ
    float err_last;//������һ��ƫ��ֵ
    float Kp,Ki,Kd;//������������֡�΢��ϵ��
    float pidAdjust;//�����ѹֵ������ִ�����ı�����
    float Sumerr; //�������ֵ
}PIDPARA;

PIDPARA tpid;

void PID_init(){
 
    tpid.SetTarget=0.0;//�趨
    tpid.CurrentValue=0.0;//��ǰ��
    tpid.err=0.0;
    tpid.err_last=0.0;
    tpid.pidAdjust=0.0;//������Ŀ ת����dac�ĵ�ѹ��pwm��ռ�ձ�
    tpid.Sumerr=0.0;//���־���ƫ����ۼ�
    tpid.Kp=0.2;
    tpid.Ki=0.015;
    tpid.Kd=0.2;
 
}
// pid�Ĺ��̣�����pidAdjustֵ�ĵ��� ƫ������0 Ŀ��ֵ=ʵ��ֵ
float PID_realize(float set){
    tpid.err=set-tpid.CurrentValue;//ƫ��
    tpid.Sumerr+=tpid.err;//���־���ƫ����ۼ�
    tpid.pidAdjust=tpid.Kp*tpid.err+                //ƫ��ı���ϵ��
                 tpid.Ki*tpid.Sumerr+           //ƫ����ֵı���ϵ��   ���֣�ƫ����ۼ�
                 tpid.Kd*(tpid.err-tpid.err_last); //ƫ��΢�ֵı���ϵ��  ΢�֣����ƫ��-�ϴ�ƫ��
    tpid.err_last=tpid.err;
    return tpid.pidAdjust;
}


//-----------------����C�Ĳ���Ԥ������--------�䷵��ֵ�����ΪJumpOver���ʹ�ò���������ʱ�ص�����------------------
JUMPTYPE funcStepC1Pre(void * ThingsL_perSteprun){return JumpLeft;}
JUMPTYPE funcStepC2Pre(void * ThingsL_perSteprun){return JumpLeft;}
JUMPTYPE funcStepC3Pre(void * ThingsL_perSteprun){return JumpLeft;}
//-----------------����C�Ĳ��趨ʱ���ú���------�䷵��ֵ���ΪJumpStay���ʹһֱ�����ʱ��ִ�ж�ʱ�ص�����-------------------
JUMPTYPE funcStepC1Jue(void * ThingsL_perSteprun)
{
  tpid.SetTarget=100;//��ǰֵ
  tpid.pidAdjust=PID_realize(tpid.SetTarget);
  return JumpLeft;
}
JUMPTYPE funcStepC2Jue(void * ThingsL_perSteprun){return JumpLeft;}
JUMPTYPE funcStepC3Jue(void * ThingsL_perSteprun){return JumpLeft;}
// C������ ��3�м�¼�ֱ�����������
//������
//���軷��
//��ʱ�ص���ʱֵ
//Ԥ��JumpLeft(����״̬=�����б�����)
//Ԥ��JumpRight(����״̬=�����б�����)
//Ԥ�����ں���
//��ʱ�ص�����
LISTLIST_FRAME ThingsL_ListListC[ListListCNum] = {
  {"C����1", STEP_PREPOLL,STEP_0, 100, JumpS1,JumpS0,funcStepC1Pre,funcStepC1Jue}, // C1�����¼��  һ�м�¼��һ�������Ӧ
  {"C����2", STEP_PREPOLL,STEP_0, 100, JumpS2,JumpS0,funcStepC2Pre,funcStepC2Jue}, // C2�����¼��  һ�м�¼��һ�������Ӧ
  {"C����3", STEP_PREPOLL,STEP_0, 100, JumpS0,JumpS0,funcStepC3Pre,funcStepC3Jue}  // C3�����¼��  һ�м�¼��һ�������Ӧ

};