
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
#include "string.h"
#include "ThingsEvent.h"//�¼������İ���
#include "ThingsL.h"//ThingsList�������б����������İ���
#include "ThingsLA.h"//����A�İ���
#include "ThingsLB.h"//����B�İ���
#include "ThingsLCPid.h"//����C�İ��� ������pid��ʾ��
#include "ThingsLDmenu.h"//����D�İ��� ����˵���ʾ��

ThingsL_PER_FRAME ThingsL_List[ThingsL_perNum];           //�����б�����
signed short ThingsL_perGeneralSch(unsigned char i, signed short Config, signed int Stay);//ͨ�õ�����


//�����б�������[����]
ThingsL_PER_FRAME ThingsL_List[ThingsL_perNum] =
{
  {"����A",1, JumpS0, 0, ThingsL_perGeneralSch,&ThingsL_ListListA[0],funcAeventRcv,EvtNon+EvtKey},//һ�м�¼��һ�������Ӧ
  {"����B",1, JumpS0, 0, ThingsL_perGeneralSch,&ThingsL_ListListB[0],funcAeventRcv,EvtNon+EvtKey},//һ�м�¼��һ�������Ӧ
  {"����C",1, JumpS0, 0, ThingsL_perGeneralSch,&ThingsL_ListListC[0],funcAeventRcv,EvtNon+EvtKey},//һ�м�¼��һ�������Ӧ
  {"��ʾD",1, JumpS0, 0, ThingsL_perGeneralSch,&ThingsL_ListListD[0],funcAeventRcv,EvtNon+EvtKey}//һ�м�¼��һ�������Ӧ
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
  
  ThingsL_EventRcvFunc;//�¼����մ���  �����¼������ں����д���
 
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
    if(ThingsL_StepSegMod==STEP_PRE)
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


/*---�Զ���״̬��-----------------------------------------------------------------------------
�Զ���״̬��
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






