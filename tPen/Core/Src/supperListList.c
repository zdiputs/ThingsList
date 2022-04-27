#include "main.h"
#include "string.h"
/********************************************************************************
����List                   SUPPER_FRAME
  ����List                 LISTLIST_FRAME
    ÿ���������滮3������   StepSegFlag
���磺
����A-----------------------����1    ����Pre   ����Poll
����B------|           |----����2    ����Pre   ����Poll
          |            |----����3    ����Pre   ����Poll
          |
          |---------------����1  ����Pre   ����Poll
          |---------------����2  ����Pre   ����Poll
          |---------------����3  ����Pre   ����Poll
          |---------------����4  ����Pre   ����Poll
-------------------------------------------------------------------------------
Ҳ������ô��
��������������i  �������沽��ĺ�����j
               j=0    j=1    j=2     j=3    j=4
  i=0����A     ����1  ����2  ����3   ����4   ����4
  i=1����B     ����1  ����2  ����3   ����4
  i=2����C     ����1  ����2  ����3
********************************************************************************/


#define NotFind 0xffff
#define SupMainPollCode (-555)   //������[���������SupJumpOn��SupState��SupTimeCnt]
#define SupStopSwitchCode (-444) //��ͣswitch ��ת�ر�  ����������switch
#define SupPauseCaseCode (-333)  //��ͣcase ��ת�ر�  ͣ����case��  ֹͣ�������ת һֱ�ڲ���ѭ������
#define SupStaGoon (-222)      //��ָ��������״ֵ̬Ϊ����������ָ��������״ֵ̬���ڵ���0��   ��ת����


#define SupPollNum (sppuerList[i].SupJumpOn) //פ������ ���Ϊ�����Ͳ���ֵ
#define SupPollNumSelfSub                               \
  if (SupPollNum > 0 && SupPollNum != SupPauseCaseCode) \
  {                                                     \
    SupPollNum--;                                       \
  }                                                                     //ѭ�������Լ�  ����ͣcase������²����Լ�
#define SupJumpIsEn (SupPollNum <= 0 && SupPollNum != SupPauseCaseCode) //����0��ֵ���ܵ�����ת���򣬲�Ȼ����ѭ������
#define SupMState (sppuerList[i].SupState)                              //��ǰ�����״̬
#define SupMTimeCnt (sppuerList[i].SupTimeCnt)                          //��ǰʱ��ĺ������
#define SupMTimeMax  (sppuerList[i].plistlist[j].internalCntMax)        //��ʱ�ص��ĳ�ʱ��

#define SupStepSegFlag    (sppuerList[i].plistlist[j].StepSegFlag)     //�����е���������
#define SupStepPreFunc    (*sppuerList[i].plistlist[j].funStepPre)(sppuerList[i].thingsrundata)
#define SupStepPollFunc   ((*sppuerList[i].plistlist[j].funStepJue)(sppuerList[i].thingsrundata)>0)
#define SupStepNextIndex  (sppuerList[i].plistlist[j].nextIndex)
#define supperNum 2    //������
#define ListListANum 3 //��������Ĳ�����
#define ListListBNum 3 //��������Ĳ�����

//------------------------------����List ��������Ĳ���-------------------------------
typedef enum STEP
{
  STEP_PRE = 0, //����1��һ�ν��������Ĵ�������һ��
  STEP_POLL,    //����2������� ����3
} STEPS;
typedef struct listsTaskFrame
{
  const char *title;           //����ı��� ���ⲿ���õ�ʱ����Բ���ƥ����ַ����ҳ������б��е����
  STEPS StepSegFlag;           //һ������ֳ�3������  ��
  unsigned int internalCntMax; //��ʱ���õĳ�ʱʱ�䵥λ����
  unsigned short nextIndex;    //��һ״̬��� Ĭ�ϵ���һ״̬JumpIndexFun������ж�
  signed short (*funStepPre)(void *);//ÿ�������Ԥ������ 
  signed short (*funStepJue)(void *);//ÿ��������˳�ѡ���� ͬʱ�Ƕ�ʱ�ص�
  
} LISTLIST_FRAME;
//-----------------------����List-------------------------------------------------------------------
typedef struct SupperFrame
{
  char *text;              //һ��������ó�2������1��Ӣ��0��Ϊ��������  ������Ϊ���������  �ⲿ���ҷ���ָ��ʱ���õ�
  signed short SupJumpOn;  //פ������
  signed short SupState;   //һ����������ĵڼ���Сcase �������Ľ���״̬��0״̬����Ϊʲô�����ɵ�״̬
  unsigned int SupTimeCnt; //�������
  //��һ����������Poll��ţ��ڶ���������ת״̬ �����򲻸�ֵ���ṹ�� ������������פ�� �����ΪSupPauseCaseCode�򲻸�ֵ���ṹ��
  //�б��е����λ�ú��� �����Է���ѭ����ѯ���� Ҳ�����ⲿ���� �����ڲ���ת
  signed short (*SupPoll)(unsigned char, signed short, signed int);
  LISTLIST_FRAME *plistlist;//����ָ��
  void * thingsrundata;//��������в�����ָ��
} SUPPER_FRAME;
signed short supperTaskA(unsigned char i, signed short Config, signed int Stay);
signed short supperTaskB(unsigned char i, signed short Config, signed int Stay);

SUPPER_FRAME sppuerList[supperNum];           //�����б�����
LISTLIST_FRAME sppuerListListA[ListListANum]; //����A�еĲ����б�����
LISTLIST_FRAME sppuerListListB[ListListBNum]; //����B�еĲ����б�����


//-----------------����A�Ĳ��躯��-------------------------------
//-----------------Ϊ������ض����ܿ��������Щ�����������Ӧ�ĺ������� 
//-----------------����A�Ĳ��躯��-------------------------------

#if 1
signed short funcStepA1Pre(void * supperSteprun)
{
  return 1;
}
signed short funcStepA2Pre(void * supperSteprun)
{
  return 1;  
}
signed short funcStepA3Pre(void * supperSteprun)
{
  return 1;  
}

signed short funcStepA1Jue(void * supperSteprun)
{
  return 1;  
}
signed short funcStepA2Jue(void * supperSteprun)
{
  return 1;  
}
signed short funcStepA3Jue(void * supperSteprun)
{
  return 1;  
}
#endif
//-----------------����B�Ĳ��躯��-------------------------------
//-----------------Ϊ������ض����ܿ��������Щ�����������Ӧ�ĺ������� 
//-----------------����B�Ĳ��躯��-------------------------------
#if 1
signed short funcStepB1Pre(void * supperSteprun)
{
  return 1;
}
signed short funcStepB2Pre(void * supperSteprun)
{
  return 1; 
}
signed short funcStepB3Pre(void * supperSteprun)
{
  return 1;
}

signed short funcStepB1Jue(void * supperSteprun)
{
  return 1;
}
signed short funcStepB2Jue(void * supperSteprun)
{
  return 1;
}
signed short funcStepB3Jue(void * supperSteprun)
{
  return 1;
}
#endif

typedef struct aTings
{
  unsigned char para1;
  unsigned char para2;
} TINGS_A;

typedef struct bTings
{
  unsigned char para1;
  unsigned char para2;
} TINGS_B;

TINGS_A tingsA_runData;//����A�����в���
TINGS_B tingsB_runData;//����B�����в���
SUPPER_FRAME sppuerList[supperNum] =
{
  {"����A",1, 1, 0, supperTaskA,&sppuerListListA[0],&tingsA_runData},
  {"����B",1, 1, 0, supperTaskB,&sppuerListListB[0],&tingsB_runData}
};
// A������ ��3�м�¼�ֱ�����������
LISTLIST_FRAME sppuerListListA[ListListANum] = {
  {"A����1", STEP_PRE, 100, 1,funcStepA1Pre,funcStepA1Jue}, // A1�����¼��
  {"A����2", STEP_PRE, 100, 2,funcStepA2Pre,funcStepA2Jue}, // A2�����¼��
  {"A����3", STEP_PRE, 100, 0,funcStepA3Pre,funcStepA3Jue}  // A2�����¼��
};

// A������ ��3�м�¼�ֱ�����������
LISTLIST_FRAME sppuerListListB[ListListBNum] = {
  {"B����1", STEP_PRE, 100, 1,funcStepB1Pre,funcStepB1Jue}, // B1�����¼��
  {"B����2", STEP_PRE, 100, 2,funcStepB2Pre,funcStepB2Jue}, // B2�����¼��
  {"B����3", STEP_PRE, 100, 0,funcStepB3Pre,funcStepB3Jue}  // B3�����¼��

};


signed short SupperGeneralSch(unsigned char i, signed short Config, signed int Stay);//ͨ�õ�����
//����������:�������ֻҪ���ָ�����ͬ���� ��������ݿ��Բ�ͬ�������������һ��
//�⺯���Ѿ��ŵ�SuperRunSequence����ѯ����
//ͬʱ�������Ҳ����ʹ�ñ��ⲿ��ʱ���� ����ʹ����������Ĳ���פ������ͣ��
//�����Զ�������������� ���������Բ�һ�� ������ʽ�ͺ������������Ҫһģһ����
signed short supperTaskA(unsigned char i, signed short Config, signed int Stay){SupperGeneralSch(i,Config,Stay);return Config;}
signed short supperTaskB(unsigned char i, signed short Config, signed int Stay){SupperGeneralSch(i,Config,Stay);return Config;}
SUPPER_FRAME sppuerList[supperNum];
//ÿ���¼�ʱ���ֵ��++
//�ŵ������жϼ�����
void SupTimeCntFun(void)
{
  unsigned char i = 0;
  for (i = 0; i < supperNum; i++)
  {
    sppuerList[i].SupTimeCnt++;
  }
}
//���̿���ѭ����
//�ŵ���ѭ������
void SuperRunSequence(void)
{
  unsigned char i = 0;
  for (i = 0; i < supperNum; i++)
  {
    // i������List��ţ�
    //�ڶ�����������-4 State����Ӱ��  ���������SupJumpOn��ת����
    (*(sppuerList[i].SupPoll))(i, SupMainPollCode, SupMainPollCode);
  }
}


//ͨ�õ����� 
//������ŵ�ÿ���Զ����[����������]��
signed short SupperGeneralSch(unsigned char i, signed short Config, signed int Stay)
{
  //���ƶ�ά����  �����б�������j����ʾ�ɡ������б����Ŷ���i��ʾŶ
  //i �� j�������������Ƹ��궨��ܶණ����ز�Ҫ�ĵ�
  signed short j; 

  if (Stay != SupMainPollCode)//פ��
  {
    SupPollNum = Stay;
  }
  if (Config >= 0)//ָ��״̬������
  {
    SupMState = Config;//ָ��״̬
  }
  if (SupPollNum == SupStopSwitchCode)//��ǰ�������iֹͣ��ת
  {
    return SupStopSwitchCode; //��ͣswitch ����Ҫ���н�switch case��
  }
  j = SupMState;//��ȡ����� 

  if(SupStepSegFlag==STEP_PRE)//Ԥ������
  {
    SupStepPreFunc;
    SupStepSegFlag = STEP_POLL;
  }

  if(SupStepSegFlag==STEP_POLL)//��ʱ�ص�����
  {
    if(SupMTimeCnt>SupMTimeMax)
    {
      SupMTimeCnt=0;
      SupPollNumSelfSub;
      if(SupStepPollFunc&&SupJumpIsEn)//ִ�лص����� ��ת����һ������ ͬ���ж���ת���еı�־
      {
          SupMState=SupStepNextIndex;//������һ������ �����״ֵ̬�ı�
      }
    }
  }
  
  return Config;
}

//�ⲿ���� 
//�������������������ⲿ�õ� 
#if 0//�÷�
SendThingsExtCode("����A",1,SupPauseCaseCode);//ͣ��������A�Ĳ���1
SendThingsExtCode("����A",1,2);               //ͣ��������A�Ĳ���1��פ��2�κ����������ת
SendThingsExtCode("����A",1,2);               //ͣ��������A�Ĳ���1��פ��2�κ����������ת
SendThingsExtCode("����A",SupStaGoon,SupStaGoon);//����A ��ָ�������״̬�����裩����������ת
SendThingsExtCode("����A",1,SupStaGoon);//����A ָ�������״̬�����裩����������ת

#endif
unsigned char SendThingsExtCode( char * pChar,signed short State,signed int Stay)
{
  unsigned short i;
  unsigned char findedflag=0;
  unsigned char str1[6];
  unsigned char str2[6];
  memcpy(str1,pChar,5);str1[5]=0;
  
  for(i=0;i<supperNum;i++)
  {
    memcpy(str2,sppuerList[i].text,5);str2[5]=0;
    if(strcmp((char const *)str1,(char const *)str2)==0)
    {
       (*sppuerList[i].SupPoll)( i,State,Stay);//ƥ��͵���һ��
       findedflag=1;
    }
   
  }
  return findedflag;//û���ҵ��ͷ�����
}

 
 