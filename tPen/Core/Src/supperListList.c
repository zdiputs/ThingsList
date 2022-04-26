#include "main.h"
/********************************************************************************
����List                   SUPPER_FRAME
  ����List                 LISTLIST_FRAME
    ÿ���������滮3������   StepSegFlag
���磺
����A-----------------------����1    ����Pre   ����Poll   ����JUMP  
����B------|           |----����2
          |            |----����3
          |
          |---------------����1
          |---------------����2
          |---------------����3
          |---------------����4
********************************************************************************/
//-----------------------����List-------------------------------------------------------------------

typedef struct SupperFrame{
  signed char    SupJumpOn;                                          //������ ��ת�ͺ�������ı�Ҫ������С�ڵ�����������ͣ�ã���ʱ������Ҳ����
  signed short   SupState;                                          //һ����������ĵڼ���Сcase �������Ľ���״̬��0״̬����Ϊʲô�����ɵ�״̬
  unsigned int   SupTimeCnt;                                      //������� SupState�ı�˲������
  char * text;                                                  //����µĸ��� ����������ô� ���Կ���
  signed short   (* SupPoll)(unsigned char,signed short );      //��һ����������Poll��ţ�
}SUPPER_FRAME;

#define SupMainPollCode         (-4)//������[���������SupJumpOn��SupState��SupTimeCnt]
#define SupStopSwitchCode       (-3)//��ͣ ��ת�ر�  ����������switch
#define SupPauseCaseCode        (-2)//��ͣ ��ת�ر�  ͣ����case�� 
#define SupNoStaGoon            (-1)//��ָ������  ��ת����

#define SupJumpEn       (sppuerList[i].SupJumpOn>0)//ÿ����ת���ⲿ��Ԥ����ת�����������Ҫ���ⲿ��Ԥ��ͣ��case��&&���������
#define SupMState       (sppuerList[i].SupState)  //��ǰ�����״̬
#define SupMTimeCnt      (sppuerList[i].SupTimeCnt)//��ǰʱ��ĺ������

#define supperNum       2       //������
#define ListListANum    3       //��������Ĳ�����
#define ListListBNum    3       //��������Ĳ�����

signed short SupPreSwitchCase(unsigned char i,signed short Config);

SUPPER_FRAME sppuerList[supperNum];//��������һ��������б�  �����涨��



//------------------------------����List ��������Ĳ���-------------------------------

typedef enum STEP{
    STEP_PRE = 1,//����1��һ�ν��������Ĵ�������һ��
    STEP_POLL,//����2������� ����3
    STEP_JUM  //P����3�жϵ���ת
}STEPS;
typedef struct listsTaskFrame{

  const char * title;          //����ı��� ���ⲿ���õ�ʱ����Բ���ƥ����ַ����ҳ������б��е���� 
  STEPS StepSegFlag;            //һ������ֳ�3������  ��  
  unsigned int internalCntMax;  //��ʱ���õĳ�ʱʱ�䵥λ����
  unsigned short nextIndex;     //��һ״̬��� Ĭ�ϵ���һ״̬JumpIndexFun������ж�
  void   (* JumpIndexFun)(unsigned short *);
}LISTLIST_FRAME;

signed short supperTaskA(unsigned char i,signed short Config);
signed short supperTaskB(unsigned char i,signed short Config);


//----------------------------------------------------------------------------------
//---------------����-----------------------------------------------------------------------
//----------------------------------------------------------------------------------
//List�Ǵ�����ı��ȷִ����顣
//ListList�Ǵ�С��������ϸ�ֵĵĸ��ڵ㲽��ı�
 SUPPER_FRAME sppuerList[supperNum];
//����״̬���ж�
signed short SupPreSwitchCase(unsigned char i,signed short Config)
{
  if(Config==SupMainPollCode)//������[���������SupJumpOn��SupState��SupTimeCnt]
  {
    return Config;
  }
  if(Config==SupStopSwitchCode)//��ͣ ��ת�ر�  ����������switch
  {
    sppuerList[i].SupJumpOn=0;
    return Config;
  }
  
  if(Config==SupPauseCaseCode)//��ͣ ��ת�ر�  ͣ����case�� 
  {
    sppuerList[i].SupJumpOn=0;
    return Config;
  }
  if(Config==SupNoStaGoon)//��ָ������  ��ת����
  {
    sppuerList[i].SupJumpOn=1;//������ת����
    return Config;
  }
  if(Config>=0)//ָ����������ת��0һ��Ϊʲô�������Ŀ���״̬��
  {
    sppuerList[i].SupState=Config;
    sppuerList[i].SupJumpOn=1;
    return Config;
  }
  return Config;
}

signed short supperTaskA(unsigned char i,signed short Config);
signed short supperTaskB(unsigned char i,signed short Config);
SUPPER_FRAME sppuerList[supperNum] = 
{
  {1,1,0,"����A",supperTaskA},     
  {1,1,0,"����B",supperTaskB}
 
};

//ÿ���¼�ʱ���ֵ��++
//�ŵ������жϼ�����
void SupTimeCntFun(void)
{
  unsigned char i=0;
  for(i=0;i<supperNum;i++)
  {
    if(SupJumpEn)
    {
      sppuerList[i].SupTimeCnt++;
    }else
    {
      sppuerList[i].SupTimeCnt=0;
    }
  }
}
//���̿���ѭ����
//�ŵ���ѭ������
void SuperRunSequence(void)
{
  unsigned char i=0;
  for(i=0;i<supperNum;i++)
  {
    //i������List��ţ�
    //�ڶ�����������-4 State����Ӱ��  ���������SupJumpOn��ת����
    (*(sppuerList[i].SupPoll))(i,SupMainPollCode);
  }
  
}




//����ž�������麯��
//�����2������� һ������A һ������B
//----------------------------------------------------------
//------------------����A------------------------------------
//----------------------------------------------------------
void *pNull;
//A���� �е� A1����
//ÿ������ſ����������� ��һ�������ǵ�һ�ν�  �ڶ������������� ���������� ��ת���ж�

void ListListA1GowhereJudgeFun(unsigned short *pVar)
{
  return;
}
//A������ �е�A2����
//ÿ������ſ����������� ��һ�������ǵ�һ�ν�  �ڶ������������� ���������� ��ת���ж�


void ListListA2GowhereJudgeFun(unsigned short *pVar)
{
  return;
}

//A���� �е� A3����  
//ÿ������ſ����������� ��һ�������ǵ�һ�ν�  �ڶ������������� ���������� ��ת���ж�

void ListListA3GowhereJudgeFun(unsigned short *pVar)
{
  return;
}


//A������ ��3�м�¼�ֱ����������� 
LISTLIST_FRAME sppuerListListA[ListListANum]={
  {"��ʼ��",0,100,1,ListListA1GowhereJudgeFun},//A1�����¼�� 
  {"ȥת��",0,100,2,ListListA2GowhereJudgeFun},//A2�����¼��
  {"ֹͣת",0,100,0,ListListA3GowhereJudgeFun}//A2�����¼��

};

signed short supperTaskA(unsigned char i,signed short Config)
{
  if(SupPreSwitchCase(i,Config)==SupStopSwitchCode)
  {
    return Config;
  }
 
  (*(sppuerListListA[SupMState].JumpIndexFun))((unsigned short *)&(SupMState));
  
  return Config;
}


//----------------------------------------------------------
//------------------����B-----------------------------------
//----------------------------------------------------------

//A���� �е� A1����
//ÿ������ſ����������� ��һ�������ǵ�һ�ν�  �ڶ������������� ���������� ��ת���ж�
void ListListB1GowhereJudgeFun(unsigned short *pVar)
{
  return;
}

//A������ �е�A2����
//ÿ������ſ����������� ��һ�������ǵ�һ�ν�  �ڶ������������� ���������� ��ת���ж�
void ListListB2GowhereJudgeFun(unsigned short *pVar)
{
  return;
}

//B���� �е� A3����  
//ÿ������ſ����������� ��һ�������ǵ�һ�ν�  �ڶ������������� ���������� ��ת���ж�
void ListListB3GowhereJudgeFun(unsigned short *pVar)
{
  return;
}


//A������ ��3�м�¼�ֱ����������� 
LISTLIST_FRAME sppuerListListB[ListListBNum]={
  {"��ʼ��",0,100,1,ListListB1GowhereJudgeFun},//B1�����¼�� 
  {"ȥת��",0,100,2,ListListB2GowhereJudgeFun},//B2�����¼��
  {"ֹͣת",0,100,0,ListListB3GowhereJudgeFun}//B3�����¼��

};
signed short supperTaskB(unsigned char i,signed short Config)
{
  if(SupPreSwitchCase(i,Config)==SupStopSwitchCode)return Config;
  
  (*(sppuerListListB[SupMState].JumpIndexFun))((unsigned short *)&(SupMState));
  
  return Config;
}


