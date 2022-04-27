#include "main.h"
/********************************************************************************
����List                   SUPPER_FRAME
  ����List                 LISTLIST_FRAME
    ÿ���������滮3������   StepSegFlag
���磺
����A-----------------------����1    ����Pre   ����Poll
����B------|           |----����2
          |            |----����3
          |
          |---------------����1
          |---------------����2
          |---------------����3
          |---------------����4

-------------------------------------------------------------------------------
Ҳ������ô��
��������������i  �������沽��ĺ�����j
  ����A     ����1  ����2  ����3   ����4   ����4
  ����B     ����1  ����2  ����3   ����4
  ����C     ����1  ����2  ����3  
********************************************************************************/
//-----------------------����List-------------------------------------------------------------------

typedef struct SupperFrame{
  
  signed short    SupJumpOn;   //פ������                                    
  signed short   SupState;    //һ����������ĵڼ���Сcase �������Ľ���״̬��0״̬����Ϊʲô�����ɵ�״̬                                    
  unsigned int   SupTimeCnt;  //�������                                      
  char * text; //����µĸ��� �������ⲿ����ʱ�ַ���ƥ����ŵĲ���                                             
  //��һ����������Poll��ţ��ڶ���������ת״̬ �����򲻸�ֵ���ṹ�� ������������פ�� �����ΪSupPauseCaseCode�򲻸�ֵ���ṹ��
  //�б��е����λ�ú��� �����Է���ѭ����ѯ���� Ҳ�����ⲿ���� �����ڲ���ת
  signed short   (* SupPoll)(unsigned char,signed short,signed int );      
}SUPPER_FRAME;

#define NotFind  0xffff
#define SupMainPollCode         (-555)//������[���������SupJumpOn��SupState��SupTimeCnt]
#define SupStopSwitchCode       (-444)//��ͣswitch ��ת�ر�  ����������switch
#define SupPauseCaseCode        (-333)//��ͣcase ��ת�ر�  ͣ����case�� 
#define SupNoStaGoon            (-222)//��ָ������  ��ת���� 
#define SupYsStaGoon            (-111)//ָ������  ��ת���� 

#define SupPollNum          (sppuerList[i].SupJumpOn)//פ������ ���Ϊ�����Ͳ���ֵ
#define SupPollNumSelfSub   if(SupPollNum>0&&SupPollNum!=SupPauseCaseCode){SupPollNum--;}//ѭ�������Լ�  ����ͣcase������²����Լ�
#define SupJumpIsEn        (SupPollNum<=0&&SupPollNum!=SupPauseCaseCode)//����0��ֵ���ܵ�����ת���򣬲�Ȼ����ѭ������
#define SupMState         (sppuerList[i].SupState)  //��ǰ�����״̬
#define SupMTimeCnt       (sppuerList[i].SupTimeCnt)//��ǰʱ��ĺ������   

#define supperNum       2       //������
#define ListListANum    3       //��������Ĳ�����
#define ListListBNum    3       //��������Ĳ�����

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
  void   (* JumpIndexFun)(signed short i,signed short *);
}LISTLIST_FRAME;

signed short supperTaskA(unsigned char i,signed short Config,signed int Stay);
signed short supperTaskB(unsigned char i,signed short Config,signed int Stay);
 
void ListListA1GowhereJudgeFun(signed short i,signed short *j);
void ListListA2GowhereJudgeFun(signed short i,signed short *j);
void ListListA3GowhereJudgeFun(signed short i,signed short *j);
void ListListB1GowhereJudgeFun(signed short i,signed short *j);
void ListListB2GowhereJudgeFun(signed short i,signed short *j);
void ListListB3GowhereJudgeFun(signed short i,signed short *j);
SUPPER_FRAME sppuerList[supperNum];//�����б�����
LISTLIST_FRAME sppuerListListA[ListListANum];//����A�еĲ����б�����
LISTLIST_FRAME sppuerListListB[ListListBNum];//����B�еĲ����б��б�����
SUPPER_FRAME sppuerList[supperNum] = 
{
  {1,1,0,"����A",supperTaskA},     
  {1,1,0,"����B",supperTaskB}
 
};
//A������ ��3�м�¼�ֱ����������� 
LISTLIST_FRAME sppuerListListA[ListListANum]={
  {"A����1",0,100,1,ListListA1GowhereJudgeFun},//A1�����¼�� 
  {"A����2",0,100,2,ListListA2GowhereJudgeFun},//A2�����¼��
  {"A����3",0,100,0,ListListA3GowhereJudgeFun}//A2�����¼��

};
//A������ ��3�м�¼�ֱ����������� 
LISTLIST_FRAME sppuerListListB[ListListBNum]={
  {"B����1",0,100,1,ListListB1GowhereJudgeFun},//B1�����¼�� 
  {"B����2",0,100,2,ListListB2GowhereJudgeFun},//B2�����¼��
  {"B����3",0,100,0,ListListB3GowhereJudgeFun}//B3�����¼��

};
//----------------------------------------------------------------------------------
//---------------����-----------------------------------------------------------------------
//----------------------------------------------------------------------------------
//List�Ǵ�����ı��ȷִ����顣
//ListList�Ǵ�С��������ϸ�ֵĵĸ��ڵ㲽��ı�
 SUPPER_FRAME sppuerList[supperNum];

//ÿ���¼�ʱ���ֵ��++
//�ŵ������жϼ�����
void SupTimeCntFun(void)
{
  unsigned char i=0;
  for(i=0;i<supperNum;i++)
  {
    sppuerList[i].SupTimeCnt++;
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
    (*(sppuerList[i].SupPoll))(i,SupMainPollCode,SupMainPollCode);
  }
  
}


//����A�еĲ�����ת
//�⺯���Ѿ��ŵ�SuperRunSequence����ѯ����
//ͬʱ�������Ҳ����ʹ�ñ��ⲿ��ʱ���� ����ʹ��פ������ͣ��
signed short supperTaskA(unsigned char i,signed short Config,signed int Stay)
{
  signed short j;//���ƶ�ά����  �����б�������j����ʾ�ɡ������б����Ŷ���i��ʾŶ
  //[����A]   ����1  ����2  ����3   ����4   ����4
  //����B     ����1  ����2  ����3   ����4
  //����C     ����1  ����2  ����3  
  if(Stay!=SupMainPollCode)
  {
    SupPollNum=Stay;
  }
  if(Config>0)
  {
    SupMState=Config;
  }
  if(SupPollNum==SupStopSwitchCode) 
  {
    return SupStopSwitchCode;//��ͣswitch ����Ҫ���н�switch case��
  }
  j=SupMState;//�����״̬�ǲ���ĵڶ������
  //�����б��״̬��Ϊ�±��ҳ�������ת����  
  //�����б��״̬��ַ��Ϊ�βδ��������ת�����н����ж�
  //ÿһ�����趼����ת�������ȷ���listlist��
  //��Ϊ�̶�Ϊ����A���i��ȷ����
  (*(sppuerListListA[j].JumpIndexFun))(i,(unsigned short *)&(SupMState));
  
  return Config;
}

//����B�еĲ�����ת
//�⺯���Ѿ��ŵ�SuperRunSequence����ѯ����
//ͬʱ�������Ҳ����ʹ�ñ��ⲿ��ʱ���� ����ʹ��פ������ͣ��
signed short supperTaskB(unsigned char i,signed short Config,signed int Stay)
{
  unsigned j;//���ƶ�ά����  �����б�������j����ʾ�ɡ������б����Ŷ���i��ʾŶ
  //����A     ����1  ����2  ����3   ����4   ����4
  //[����B]   ����1  ����2  ����3   ����4
  //����C     ����1  ����2  ����3 
  if(Stay!=SupMainPollCode)
  {
    SupPollNum=Stay;
  }
  if(Config>0)
  {
    SupMState=Config;
  }
  if(SupPollNum==SupStopSwitchCode) 
  {
    return SupStopSwitchCode;//��ͣswitch ����Ҫ���н�switch case��
  }
  j=SupMState;//�����״̬�ǲ���ĵڶ������
  //�����б��״̬��Ϊ�±��ҳ�������ת����  
  //�����б��״̬��ַ��Ϊ�βδ��������ת�����н����ж�
  //ÿһ�����趼����ת�������ȷ���listlist��
  //��Ϊ�̶�Ϊ����B���i��ȷ����
  (*(sppuerListListB[j].JumpIndexFun))(i,(unsigned short *)&(SupMState));
  
  return Config;
}



//����ž�������麯��
//�����2������� һ������A һ������B
//----------------------------------------------------------------------
//------------------����A---�������������������ȷŵ��б����3������- 
//----------------------------------------------------------------------
void *pNull;
//A���� �е� A1����
//ÿ������ſ����������� ��һ�������ǵ�һ�ν�  �ڶ������������� ���������� ��ת���ж�
void ListListA1GowhereJudgeFun(signed short i,signed short *j)
{
  signed short jj=*j;
  if(sppuerListListA[jj].StepSegFlag==STEP_PRE)//����Pre
  {
    sppuerListListA[jj].StepSegFlag=STEP_POLL;
  }
  
  if(sppuerListListA[jj].StepSegFlag==STEP_POLL)//����Poll
  {
    if(SupMTimeCnt>sppuerListListA[jj].internalCntMax)
    {
      SupMTimeCnt=0;
      SupPollNumSelfSub;
      if(SupJumpIsEn)//������ת��פ��
      {
        *j=sppuerListListA[jj].nextIndex;
        sppuerListListA[*j].StepSegFlag=STEP_PRE;//��һ������Ļ��ڵĸ�λ
      }
    } 
  }
  return;
}
//A������ �е�A2����
//ÿ������ſ����������� ��һ�������ǵ�һ�ν�  �ڶ������������� ���������� ��ת���ж�
void ListListA2GowhereJudgeFun(signed short i,signed short *j)
{
  return;
}

//A���� �е� A3����  
//ÿ������ſ����������� ��һ�������ǵ�һ�ν�  �ڶ������������� ���������� ��ת���ж�
void ListListA3GowhereJudgeFun(signed short i,signed short *j)
{
  return;
}

//----------------------------------------------------------------------
//------------------����B-----�������������������ȷŵ��б����3������- 
//----------------------------------------------------------------------
//A���� �е� A1����
//ÿ������ſ����������� ��һ�������ǵ�һ�ν�  �ڶ������������� ���������� ��ת���ж�
void ListListB1GowhereJudgeFun(signed short i,signed short *j)
{
  return;
}

//A������ �е�A2����
//ÿ������ſ����������� ��һ�������ǵ�һ�ν�  �ڶ������������� ���������� ��ת���ж�
void ListListB2GowhereJudgeFun(signed short i,signed short *j)
{
  return;
}

//B���� �е� A3����  
//ÿ������ſ����������� ��һ�������ǵ�һ�ν�  �ڶ������������� ���������� ��ת���ж�
void ListListB3GowhereJudgeFun(signed short i,signed short *j)
{
  return;
}






