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
#include "ThingsLA.h"
//����Aʾ��
TINGS_A tingsA_runData;//����A�����в���

//-----------------����A�Ĳ���Ԥ������--------�䷵��ֵ�����ΪJumpOver���ʹ�ò���������ʱ�ص�����------------------
JUMPTYPE funcStepA1Pre(void * ThingsL_perSteprun){return JumpLeft;}
JUMPTYPE funcStepA2Pre(void * ThingsL_perSteprun){return JumpLeft;}
JUMPTYPE funcStepA3Pre(void * ThingsL_perSteprun){return JumpLeft;}
//-----------------����A�Ĳ��趨ʱ���ú���------�䷵��ֵ���ΪJumpStay���ʹһֱ�����ʱ��ִ�ж�ʱ�ص�����-------------------
JUMPTYPE funcStepA1Jue(void * ThingsL_perSteprun){return JumpLeft;}
JUMPTYPE funcStepA2Jue(void * ThingsL_perSteprun){return JumpLeft;}
JUMPTYPE funcStepA3Jue(void * ThingsL_perSteprun){return JumpLeft;}
// A������ ��3�м�¼�ֱ�����������
//������
//���軷��
//��ʱ�ص���ʱֵ
//Ԥ��JumpLeft(����״̬=�����б�����)
//Ԥ��JumpRight(����״̬=�����б�����)
//Ԥ�����ں���
//��ʱ�ص�����
LISTLIST_FRAME ThingsL_ListListA[ListListANum] = {
  {"A����1", STEP_PREPOLL,STEP_0, 100, JumpS1,JumpS0,funcStepA1Pre,funcStepA1Jue}, // A1�����¼��  һ�м�¼��һ�������Ӧ
  {"A����2", STEP_PREPOLL,STEP_0, 100, JumpS2,JumpS0,funcStepA2Pre,funcStepA2Jue}, // A2�����¼��  һ�м�¼��һ�������Ӧ
  {"A����3", STEP_PREPOLL,STEP_0, 100, JumpS0,JumpS0,funcStepA3Pre,funcStepA3Jue}  // A2�����¼��  һ�м�¼��һ�������Ӧ
};