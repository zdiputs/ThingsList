 /********************************************************************************
����һ����αOS������ ��������ﲢû��չʾ
********************************************************************************/
 typedef struct tag_ThingsTask
{
  unsigned char Type;//���� 0 ��ִ�еı�ʾ����ɾ��  1��ʱ���õ�Time��������ִ��1�� 2��ʱ�����Զ�ɾ�������
  unsigned int  Time;//��ʱ��������0 ����һ��
  unsigned char sFlag;//�ֶ�ִ��һ�� ��ʱδ��ʱ�ֶ�����ִ��һ�εı�־
  unsigned char State;  //��ǰ״̬
  void (*FUNC )(unsigned char,unsigned char );//��һ����������ѯ���õ�ʱ��������ţ��ڶ�����������ѯ���õ�ʱ�򴫵�ǰ״̬       
}ThingsTask;

#define THINGSTASKNUMMAX 20
#define I_LED0_TASK 0
#define I_LED1_TASK 1

//�������ģ��
ThingsTask ThingsT[THINGSTASKNUMMAX] = {0};

void RTOS_Task_Create(unsigned char  i,unsigned char  Type,unsigned int   Time, unsigned char  sFlag, unsigned char  State,void (*Func)(unsigned char,unsigned char ) )
{  
    ThingsT[i].Type = Type;//���� 0 ��ִ�еı�ʾ����ɾ��  1��ʱ���õ�Time��������ִ��1�� 2��ʱ�����Զ�ɾ�������
    ThingsT[i].Time = Time;//��ʱ��������0 ����һ��
    ThingsT[i].sFlag = sFlag;//�ֶ�ִ��һ�� ��ʱδ��ʱ�ֶ�����ִ��һ�εı�־
    ThingsT[i].State = State;//����������һ���switch(State) case ������������״̬��
    ThingsT[i].FUNC = Func;//��һ����������ѯ���õ�ʱ��������ţ��ڶ�����������ѯ���õ�ʱ�򴫵�ǰ״̬ 			
  
}
//ɾ��������
void RTOS_Task_None(unsigned char  i)
{
  ThingsT[i].Type = 0;			
}
//������Ⱥ���
void ThingsTOS(void)
{		
  unsigned int i = 0;
  for (i = 0; i < THINGSTASKNUMMAX; i++)
  {
    if(ThingsT[i].Type == 1)//���к󲻻��Զ�ɾ��
    {
      if(ThingsT[i].Time == 0 || (ThingsT[i].sFlag) != 0)//���ִ�����ʽһ���� ��ʱ���� ��һ���ź�sflag����
      {
        (ThingsT[i].FUNC)(i,ThingsT[i].State); 
      }
    }
    else if(ThingsT[i].Type == 2)//���к��Զ�ɾ��
    {
      if(ThingsT[i].Time == 0 || (ThingsT[i].sFlag) != 0)//���ִ�����ʽһ���� ��ʱ���� ��һ���ź�sflag����
      {
        (ThingsT[i].FUNC)(i,ThingsT[i].State); 
        RTOS_Task_None(i);//�Զ�ɾ��������� ��������´��������򲻻������е�
      }
    }
  }
}


//����ֵ�ĸ�ԭ �����ŵ�״̬��������
void ThingsTtimerset(unsigned char  i, unsigned int Time)
{
 ThingsT[i].Time = Time;
}


//����ֵ���Լ��ŵ����붨ʱ�ж���
void TimeCnt(void)
{
  unsigned int i;
  for (i = 0; i < THINGSTASKNUMMAX; i++)
  {
    if(ThingsT[i].Type == 0x01 &&  ThingsT[i].Time > 0x00)
    {
      ThingsT[i].Time--;
    }
  }
}

//���񣺻ص�����
void LED0_BLINK_Task(unsigned char i,unsigned char State)
{
   
  ThingsTtimerset(I_LED0_TASK,500);//�ظ��ĵ��õĻ���ԭʱ�����ֵ
  switch(State)//״̬��
  {
  case 0:ThingsT[i].State=1;break;
  case 1:ThingsT[i].State=0;break;
  }
}

//���񣺻ص����� 
void LED1_BLINK_Task(unsigned char i,unsigned char State)
{
   
  ThingsTtimerset(I_LED1_TASK,500);//�ظ��ĵ��õĻ���ԭʱ�����ֵ
  switch(State)//״̬��
  {
  case 0:ThingsT[i].State=1;break;
  case 1:ThingsT[i].State=0;break;
  }
}

//����������ʵ���Ǵ����ص�����
void CreateSomeTask(void)
{
  RTOS_Task_Create(I_LED0_TASK,1,500,0,0,LED0_BLINK_Task);
  RTOS_Task_Create(I_LED1_TASK,1,500,0,0,LED1_BLINK_Task);
}