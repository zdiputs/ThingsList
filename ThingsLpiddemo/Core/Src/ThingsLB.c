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
#include "ThingsLB.h"
//����Bʾ��
TINGS_B tingsB_runData;//����B�����в���

//-----------------����B�Ĳ���Ԥ������--------�䷵��ֵ�����ΪJumpOver���ʹ�ò���������ʱ�ص�����-----------------------
JUMPTYPE funcStepB1Pre(void * ThingsL_perSteprun){return JumpLeft;}
JUMPTYPE funcStepB2Pre(void * ThingsL_perSteprun){return JumpLeft; }
JUMPTYPE funcStepB3Pre(void * ThingsL_perSteprun){return JumpLeft;}

//-----------------����B�Ĳ��趨ʱ���ú���------�䷵��ֵ���ΪJumpStay���ʹһֱ�����ʱ��ִ�ж�ʱ�ص�����----------------
JUMPTYPE funcStepB1Jue(void * ThingsL_perSteprun){return JumpLeft;}
JUMPTYPE funcStepB2Jue(void * ThingsL_perSteprun){return JumpLeft;}
JUMPTYPE funcStepB3Jue(void * ThingsL_perSteprun){return JumpLeft;}


// A������ ��3�м�¼�ֱ�����������
//������
//���軷��
//��ʱ�ص���ʱֵ
//Ԥ��JumpLeft(����״̬=�����б�����)
//Ԥ��JumpRight(����״̬=�����б�����)
//Ԥ�����ں���
//��ʱ�ص�����
LISTLIST_FRAME ThingsL_ListListB[ListListBNum] = {
  {"B����1", STEP_PREPOLL,STEP_0, 100, JumpS1,JumpS0,funcStepB1Pre,funcStepB1Jue}, // B1�����¼��  һ�м�¼��һ�������Ӧ
  {"B����2", STEP_PREPOLL,STEP_0, 100, JumpS2,JumpS0,funcStepB2Pre,funcStepB2Jue}, // B2�����¼��  һ�м�¼��һ�������Ӧ
  {"B����3", STEP_PREPOLL,STEP_0, 100, JumpS0,JumpS0,funcStepB3Pre,funcStepB3Jue}  // B3�����¼��  һ�м�¼��һ�������Ӧ

};