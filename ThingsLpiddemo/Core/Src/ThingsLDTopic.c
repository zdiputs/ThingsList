#include "ThingsLDTopic.h"
//������顾������Ϣ����ת �� �˵�����ʾ��
//���ڻ�û�� ׼��������Ϣ���԰壬���ͷ������԰�������Ϣ�����շ������԰���ȡ��Ϣ���������Ϣɾ��

//-----------------����D�Ĳ���Ԥ������--------�䷵��ֵ�����ΪJumpOver���ʹ�ò���������ʱ�ص�����-----------------------
JUMPTYPE funcStepD1Pre(void * ThingsL_perSteprun)
{
  extern void MenuCtrl(void);
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