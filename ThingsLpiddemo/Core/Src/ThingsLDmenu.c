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
#include "ThingsLDmenu.h"
//������顾�˵�����ʾ��


//-----------------����D�Ĳ���Ԥ������--------�䷵��ֵ�����ΪJumpOver���ʹ�ò���������ʱ�ص�����-----------------------
JUMPTYPE funcStepD1Pre(void * ThingsL_perSteprun)
{
  
   MenuCtrl();
  return JumpLeft;
}

//-----------------����D�Ĳ��趨ʱ���ú���------�䷵��ֵ���ΪJumpStay���ʹһֱ�����ʱ��ִ�ж�ʱ�ص�����----------------
JUMPTYPE funcStepD1Jue(void * ThingsL_perSteprun)
{
  return JumpLeft;
}

//������
//���軷��
//��ʱ�ص���ʱֵ
//Ԥ��JumpLeft(����״̬=�����б�����)
//Ԥ��JumpRight(����״̬=�����б�����)
//Ԥ�����ں���
//��ʱ�ص�����
LISTLIST_FRAME ThingsL_ListListD[ListListDNum] = {
  {"D����1", STEP_PRE,STEP_0, 0, JumpS0,JumpS0,funcStepD1Pre,funcStepD1Jue}, // B1�����¼��  һ�м�¼��һ�������Ӧ
};