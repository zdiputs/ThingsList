#include "ThingsLA.h"

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
  {"A����1", STEP_PREPOLL,STEP_0, 100, 1,0,funcStepA1Pre,funcStepA1Jue}, // A1�����¼��  һ�м�¼��һ�������Ӧ
  {"A����2", STEP_PREPOLL,STEP_0, 100, 2,0,funcStepA2Pre,funcStepA2Jue}, // A2�����¼��  һ�м�¼��һ�������Ӧ
  {"A����3", STEP_PREPOLL,STEP_0, 100, 0,0,funcStepA3Pre,funcStepA3Jue}  // A2�����¼��  һ�м�¼��һ�������Ӧ
};