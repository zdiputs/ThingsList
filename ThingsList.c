#include "main.h"
#include "string.h"
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
  Auth:���ǻ��      (z)diputs 
  http:iamrobot.top https://github.com/zdiputs
  https:stgui.com   https://gitee.com/diputs
********************************************************************************/
#define NotFind 0xffff
#define ThingsL_MainPollCode (-555)   //������[���������ThingsL_JumpOn��ThingsL_State��ThingsL_TimeCnt]
#define ThingsL_StopSwitchCode (-444) //��ͣswitch ��ת�ر�  ����������switch
#define ThingsL_PauseCaseCode (-333)  //��ͣcase ��ת�ر�  ͣ����case��  ֹͣ�������ת һֱ�ڲ���ѭ������
#define ThingsL_StaGoon (-222)      //��ָ��������״ֵ̬Ϊ����������ָ��������״ֵ̬���ڵ���0��   ��ת����
#define ThingsL_PollNum (ThingsL_List[i].ThingsL_JumpOn) 							//פ������ ���Ϊ�����Ͳ���ֵ
#define ThingsL_PollNumSelfSub     if(ThingsL_PollNum>0&&ThingsL_PollNum!=ThingsL_PauseCaseCode){ThingsL_PollNum--;}//ѭ�������Լ�  ����ͣcase������²����Լ�
#define ThingsL_JumpIsEn 			(ThingsL_PollNum <= 0 && ThingsL_PollNum != ThingsL_PauseCaseCode) //����0��ֵ���ܵ�����ת���򣬲�Ȼ����ѭ������
#define ThingsL_MState 				(ThingsL_List[i].ThingsL_State)                              //��ǰ�����״̬��ͬʱΪ�����б����ţ�
#define ThingsL_MTimeCnt 			(ThingsL_List[i].ThingsL_TimeCnt)                          //��ǰʱ��ĺ������
#define ThingsL_MTimeMax  			(ThingsL_List[i].plistlist[j].internalCntMax)        //��ʱ�ص��ĳ�ʱ��
#define ThingsL_StepSegMod    		(ThingsL_List[i].plistlist[j].StepSegMod)     		//����������ģʽ  ��һ��ֻ����Ԥ������ �ڶ���ֻ���ж�ʱ���� ������������Ԥ�����������ж�ʱ����
#define ThingsL_StepSegFlag    		(ThingsL_List[i].plistlist[j].StepSegFlag)     		//�����е�ǰ���ڱ�־
#define ThingsL_StepPreFunc    		(*ThingsL_List[i].plistlist[j].funStepPre)(ThingsL_List[i].thingsrundata)//Ԥ������
#define ThingsL_StepPollFunc   		((*ThingsL_List[i].plistlist[j].funStepJue)(ThingsL_List[i].thingsrundata))//��ʱ���û���
#define ThingsL_erRunSeqFun			(*ThingsL_List[i].ThingsL_Poll)
#define ThingsL_StepLeftNextIndex    (ThingsL_List[i].plistlist[j].nextleftIndex)   //��һ״̬����һ�㶨��Ϊ˳��ִ�е���� ������״̬��ֵ����ֵ
#define ThingsL_StepRightNextIndex    (ThingsL_List[i].plistlist[j].nextrightIndex) //��һ״̬����һ�㶨��Ϊ����ִ�е���� ������״̬��ֵ����ֵ
/******************************************************************************************************************************************
 * ���鲽���б�
  [����1Ԥ������]
  [����1��ʱ������]
     |ThingsL_StepLeftNextIndex=2����
     v
  [����2Ԥ������]<------|
  [����2��ʱ������]     |
     |                   |
     v                   |
  [����3Ԥ������]       |
  [����3��ʱ������]     |
     |                   |
     v                   |
  [����4Ԥ������]       |
  [����4��ʱ������]---->|ThingsL_StepRightNextIndex=2������������ʱ
     |
     v          
  [����5Ԥ������]  /___
  [����5��ʱ������]____|ѭ��ִ��ĳһ�������еĶ�ʱ�ص�������ʾ��פ����JumpStay
****************************************************************************************************************************************/
#define ThingsL_perNum 2    //������
#define ListListANum 3 //��������Ĳ�����
#define ListListBNum 3 //��������Ĳ�����

//------------------------------����List ��������Ĳ���-------------------------------
typedef enum Jumptype
{
  JumpStay=-4,   //פ��     ���岽�軷�ں�������0ʱ
  JumpLeft,     //������ת ���岽�軷�ں�������1ʱ  
  JumpRight,    //������ת ���岽�軷�ں�������2ʱ ����һ������
  JumpOver,     //������ʱ���ں���
  JumpS0,
  JumpS1,
  JumpS2,
  JumpS3,
  JumpS4,
  JumpS5,
  JumpS6,
  JumpS7,
  JumpS8,
  JumpS9,
  JumpS10,
  JumpS11,
  JumpS12,
  JumpS13,
  JumpS14,
  JumpS15,
  JumpS16,
  JumpS17,
  JumpS18,
  JumpS19,
  JumpS20,
} JUMPTYPE;
typedef enum STEP//һ�����µĻ���ģʽ
{
  STEP_PRE = 0, //ֻ����Ԥ������
  STEP_POLL,    //ֻ���ж�ʱ�ص�����
  STEP_PREPOLL, //������ִ��Ԥ������ �ٳ�ʱ��ִ�ж�ʱ�ص�����
} STEPS;
typedef enum STEPSTATUS//һ�����µĻ���״̬
{
  STEP_0 = 0, //ֻ����Ԥ������
  STEP_1,    //ֻ���ж�ʱ�ص�����
  STEP_2,
} STEPSTA;
typedef struct listsTaskFrame//����
{
  const char *title;           //����ı��� ���ⲿ���õ�ʱ����Բ���ƥ����ַ����ҳ������б��е����
  STEPS  StepSegMod;           //���軷��Ԥ�������ģʽ ��һ��ֻ����Ԥ���������ڶ���ֻ���ж�ʱ������������������Ԥ�����������ж�ʱ���� 
  STEPSTA StepSegFlag;           //һ������ֳ�3������,�����������ĸ����ڵ�״̬
  unsigned int internalCntMax; //һ������ֳ�3������,�����������ĸ����ڵ�״̬
  unsigned short nextleftIndex;    //��һ״̬��� Ĭ�ϵ���һ״̬JumpIndexFun������ж�
  unsigned short nextrightIndex;    //��һ״̬��� Ĭ�ϵ���һ״̬JumpIndexFun������ж�
  JUMPTYPE (*funStepPre)(void *);//ÿ�������Ԥ������  ����JumpOverʱ��ζ��������ʱ����ֱ����������ת״̬����������ʱ��Ԥ����һ�º���ִ�ж�ʱ
  JUMPTYPE (*funStepJue)(void *);//ÿ��������˳�ѡ���� ͬʱ�Ƕ�ʱ�ص�  ����ֵJumpStayʱ��ζ��פ���ڶ�ʱ�����ж�ʱִ�� ͬʱ����״̬�е�פ�������Լ�1
  
} LISTLIST_FRAME;
//-----------------------����List-------------------------------------------------------------------
typedef struct ThingsL_perFrame//����
{
  char *text;              //һ��������ó�2������1��Ӣ��0��Ϊ��������  ������Ϊ���������  �ⲿ���ҷ���ָ��ʱ���õ�
  signed short ThingsL_JumpOn;  //פ������
  signed short ThingsL_State;   //һ����������ĵڼ���Сcase �������Ľ���״̬��0״̬����Ϊʲô�����ɵ�״̬
  unsigned int ThingsL_TimeCnt; //�������
  //��һ����������Poll��ţ��ڶ���������ת״̬ �����򲻸�ֵ���ṹ�� ������������פ�� �����ΪThingsL_PauseCaseCode�򲻸�ֵ���ṹ��
  //�б��е����λ�ú��� �����Է���ѭ����ѯ���� Ҳ�����ⲿ���� �����ڲ���ת
  signed short (*ThingsL_Poll)(unsigned char, signed short, signed int);
  LISTLIST_FRAME *plistlist;//����ָ�롢��һ������ָ��һ�鲽��
  void * thingsrundata;//��������в�����ָ��
} ThingsL_PER_FRAME;
signed short ThingsL_perTaskA(unsigned char i, signed short Config, signed int Stay);
signed short ThingsL_perTaskB(unsigned char i, signed short Config, signed int Stay);

ThingsL_PER_FRAME ThingsL_List[ThingsL_perNum];           //�����б�����
LISTLIST_FRAME ThingsL_ListListA[ListListANum]; //����A�еĲ����б�����
LISTLIST_FRAME ThingsL_ListListB[ListListBNum]; //����B�еĲ����б�����
signed short ThingsL_perGeneralSch(unsigned char i, signed short Config, signed int Stay);//ͨ�õ�����
typedef struct aTings
{
  unsigned char para1;
  unsigned char para2;
} TINGS_A;
TINGS_A tingsA_runData;//����A�����в���
//-----------------����A�Ĳ���Ԥ������--------�䷵��ֵ�����ΪJumpOver���ʹ�ò���������ʱ�ص�����------------------
JUMPTYPE funcStepA1Pre(void * ThingsL_perSteprun){return JumpLeft;}
JUMPTYPE funcStepA2Pre(void * ThingsL_perSteprun){return JumpLeft;}
JUMPTYPE funcStepA3Pre(void * ThingsL_perSteprun){return JumpLeft;}
//-----------------����A�Ĳ��趨ʱ���ú���------�䷵��ֵ���ΪJumpStay���ʹһֱ�����ʱ��ִ�ж�ʱ�ص�����-------------------
JUMPTYPE funcStepA1Jue(void * ThingsL_perSteprun){return JumpLeft;}
JUMPTYPE funcStepA2Jue(void * ThingsL_perSteprun){return JumpLeft;}
JUMPTYPE funcStepA3Jue(void * ThingsL_perSteprun){return JumpLeft;}

typedef struct bTings
{
  unsigned char para1;
  unsigned char para2;
} TINGS_B;
TINGS_B tingsB_runData;//����B�����в���
//-----------------����B�Ĳ���Ԥ������--------�䷵��ֵ�����ΪJumpOver���ʹ�ò���������ʱ�ص�����-----------------------
JUMPTYPE funcStepB1Pre(void * ThingsL_perSteprun){return JumpLeft;}
JUMPTYPE funcStepB2Pre(void * ThingsL_perSteprun){return JumpLeft; }
JUMPTYPE funcStepB3Pre(void * ThingsL_perSteprun){return JumpLeft;}
//-----------------����A�Ĳ��趨ʱ���ú���------�䷵��ֵ���ΪJumpStay���ʹһֱ�����ʱ��ִ�ж�ʱ�ص�����----------------
JUMPTYPE funcStepB1Jue(void * ThingsL_perSteprun){return JumpLeft;}
JUMPTYPE funcStepB2Jue(void * ThingsL_perSteprun){return JumpLeft;}
JUMPTYPE funcStepB3Jue(void * ThingsL_perSteprun){return JumpLeft;}
//�����б�������[����]
ThingsL_PER_FRAME ThingsL_List[ThingsL_perNum] =
{
  {"����A",1, JumpS0, 0, ThingsL_perGeneralSch,&ThingsL_ListListA[0],&tingsA_runData},//һ�м�¼��һ�������Ӧ
  {"����B",1, JumpS0, 0, ThingsL_perGeneralSch,&ThingsL_ListListB[0],&tingsB_runData}//һ�м�¼��һ�������Ӧ
};

// A������ ��3�м�¼�ֱ�����������
LISTLIST_FRAME ThingsL_ListListA[ListListANum] = {
  {"A����1", STEP_PREPOLL,STEP_0, 100, 1,0,funcStepA1Pre,funcStepA1Jue}, // A1�����¼��  һ�м�¼��һ�������Ӧ
  {"A����2", STEP_PREPOLL,STEP_0, 100, 2,0,funcStepA2Pre,funcStepA2Jue}, // A2�����¼��  һ�м�¼��һ�������Ӧ
  {"A����3", STEP_PREPOLL,STEP_0, 100, 0,0,funcStepA3Pre,funcStepA3Jue}  // A2�����¼��  һ�м�¼��һ�������Ӧ
};

// A������ ��3�м�¼�ֱ�����������
//������
//���軷��
//��ʱ�ص���ʱֵ
//
LISTLIST_FRAME ThingsL_ListListB[ListListBNum] = {
  {"B����1", STEP_PREPOLL,STEP_0, 100, 1,0,funcStepB1Pre,funcStepB1Jue}, // B1�����¼��  һ�м�¼��һ�������Ӧ
  {"B����2", STEP_PREPOLL,STEP_0, 100, 2,0,funcStepB2Pre,funcStepB2Jue}, // B2�����¼��  һ�м�¼��һ�������Ӧ
  {"B����3", STEP_PREPOLL,STEP_0, 100, 0,0,funcStepB3Pre,funcStepB3Jue}  // B3�����¼��  һ�м�¼��һ�������Ӧ

};


//�ⲿ����
//�������������������ⲿ�õ�
#if 0//�÷�
SendThingsExtCode("����A",1,ThingsL_PauseCaseCode);//ͣ��������A�Ĳ���1
SendThingsExtCode("����A",1,2);               //ͣ��������A�Ĳ���1��פ��2�κ����������ת
SendThingsExtCode("����A",1,2);               //ͣ��������A�Ĳ���1��פ��2�κ����������ת
SendThingsExtCode("����A",ThingsL_StaGoon,ThingsL_StaGoon);//����A ��ָ�������״̬�����裩����������ת
SendThingsExtCode("����A",1,ThingsL_StaGoon);//����A ָ�������״̬�����裩����������ת
#endif
unsigned char SendThingsExtCode( char * pChar,signed short State,signed int Stay)
{
  unsigned short i;
  unsigned char findedflag=0;
  unsigned char str1[6];
  unsigned char str2[6];
  memcpy(str1,pChar,5);str1[5]=0;
  
  for(i=0;i<ThingsL_perNum;i++)
  {
    memcpy(str2,ThingsL_List[i].text,5);str2[5]=0;
    if(strcmp((char const *)str1,(char const *)str2)==0)
    {
       ThingsL_erRunSeqFun( i,State,Stay);//ƥ��͵���һ��
       findedflag=1;
    }
   
  }
  return findedflag;//û���ҵ��ͷ�����
}

 
/************************************************************************************
ͨ�õ�����
���԰�����ŵ�ÿ���Զ����[����������]�� �������Զ�ִ�ж�Ӧ�Ĳ����б�
һ�������б��е�ÿ�������¼��������������õ������Զ�ִ�ж�Ӧ�Ĳ����б�
*************************************************************************************/
signed short ThingsL_perGeneralSch(unsigned char i, signed short Config, signed int Stay)
{
  //���ƶ�ά����  �����б�������j����ʾ�ɡ������б����Ŷ���i��ʾŶ
  //i �� j�������������Ƹ��궨��ܶණ����ز�Ҫ�ĵ�
  signed short j; 
  JUMPTYPE stayleftright=JumpStay;
  if (Stay != ThingsL_MainPollCode)//פ��
  {
    ThingsL_PollNum = Stay;
  }
  if (Config >= 0)//ָ��״̬������
  {
    ThingsL_MState = Config;//ָ��״̬
  }
  if (ThingsL_PollNum == ThingsL_StopSwitchCode)//��ǰ�������iֹͣ��ת
  {
    return ThingsL_StopSwitchCode; //��ͣswitch ����Ҫ���н�switch case��
  }
  j = ThingsL_MState;//��ȡ�����  һ�������״̬�ž��ǲ����б���������j
  
  //Ԥ���� ����
  //�����еĶ��岻��ֻ����
  if(ThingsL_StepSegMod!=STEP_POLL&&ThingsL_StepSegFlag==STEP_0)//����ֻ����Poll����   ���軷�ڱ�־���ǳ�ʼֵֻ����һ
  {
    ThingsL_MTimeCnt=0;
    ThingsL_StepSegFlag=STEP_1;
    stayleftright=ThingsL_StepPreFunc;//ִ��Ԥ��������ȡ���䷵��ֵ
    if(ThingsL_StepSegMod==STEP_PRE)//�����ֻ����Ԥ�������Ͱ����Flag�ָ���STEP_0
    {
      ThingsL_StepSegFlag=STEP_0;
    }
    if(stayleftright==JumpOver)//��ȡԤ�������ķ���ֵ
    {
      ThingsL_MState=ThingsL_StepLeftNextIndex;
      ThingsL_StepSegFlag = STEP_0;//ʹ�ö�ʱ����Ҳ��������
    }
    if(stayleftright>=0)//��������>=0��ֱ�Ӱ�����ֵ��ת
    {
      ThingsL_MState=stayleftright;
      ThingsL_StepSegFlag = STEP_0;//ʹ�ö�ʱ����Ҳ��������
      
    }
  }
  
  //��ʱ������
  //�����ж��岻��ֻ����Ԥ������
  if(ThingsL_StepSegMod!=STEP_PRE&&ThingsL_StepSegFlag!=STEP_0)//����ֻ����Pre ����  ���й�Ԥ������
  {
    ThingsL_StepSegFlag=STEP_2;
    if(ThingsL_MTimeCnt>ThingsL_MTimeMax)
    {
      ThingsL_MTimeCnt=0;
      ThingsL_PollNumSelfSub;
      stayleftright=ThingsL_StepPollFunc;//ִ�ж�ʱ�ص�����
      if((stayleftright!=JumpStay)&&ThingsL_JumpIsEn) //��פ��ס��ת����һ������
      {
        if(stayleftright>=0)
        {
          ThingsL_StepSegFlag=STEP_0;//��λ���軷�ڱ�־
          ThingsL_MState=stayleftright;//��������ֵ�������Ļ�ֱ�ӰѺ�������ֵ������Ž��е�׼
          return Config;
        }else{//��������ֵ�Ǹ����Ļ������Ԥ�����Ž�����ת
          ThingsL_StepSegFlag=STEP_0;//��λ���軷�ڱ�־
          if(stayleftright==JumpLeft)//�������ת
          {
            ThingsL_MState=ThingsL_StepLeftNextIndex;//������һ������ �����״ֵ̬�ı�
          }else//������
          {
            ThingsL_MState=ThingsL_StepRightNextIndex;//������һ������ �����״ֵ̬�ı�
          }
        }
      }
    }
  }
  
  return Config;
}


/*---�Զ��������-----------------------------------------------------------------------------
�Զ��������
�������[ͨ�õ�����]ThingsL_perGeneralSch(���԰��������ֺ����Ž�ȥ����ص�������)��
�����������switch case��ֱ��д����,������������б��������.
{"����A",1, 1, 0, NoSchedulerPutitLikethis,&ThingsL_ListListA[0],&tingsA_runData},
--------------------------------------------------------------------------------------------*/
void NoSchedulerPutitLikethis(unsigned char i,signed short ConfigState,signed int Stay)
{
  if(Stay!=ThingsL_MainPollCode)
  {
    ThingsL_PollNum=Stay;
  }
  if(ConfigState>0)
  {
    ThingsL_MState=ConfigState;
  }
  
  switch(ThingsL_MState)
  {
	  case 0:ThingsL_MState=1;break;
	  case 1:ThingsL_MState=2;break;
	  case 2:ThingsL_MState=3;break;
	  case 3:ThingsL_MState=0;break;

  }
}


//ÿ���¼�ʱ���ֵ��++
//�ŵ������жϼ�����
void ThingsL_TimeCntFun(void)
{
  unsigned char i = 0;
  for (i = 0; i < ThingsL_perNum; i++)
  {
    ThingsL_MTimeCnt++;
  }
}
//���̿���ѭ����
//�ŵ���ѭ������
void ThingsL_erRunSequence(void)
{
  for (unsigned char i = 0; i < ThingsL_perNum; i++)
  {
    ThingsL_erRunSeqFun(i, ThingsL_MainPollCode, ThingsL_MainPollCode);
  }
}