 /********************************************************************************
这是一个简单伪OS调度器 这个工程里并没有展示
********************************************************************************/
 typedef struct tag_ThingsTask
{
  unsigned char Type;//类型 0 不执行的表示任务被删除  1定时调用的Time被减到零执行1次 2定时到了自动删除任务的
  unsigned int  Time;//定时计数减到0 运行一次
  unsigned char sFlag;//手动执行一次 定时未到时手动开启执行一次的标志
  unsigned char State;  //当前状态
  void (*FUNC )(unsigned char,unsigned char );//第一个参数在轮询调用的时候传任务序号，第二个参数在轮询调用的时候传当前状态       
}ThingsTask;

#define THINGSTASKNUMMAX 20
#define I_LED0_TASK 0
#define I_LED1_TASK 1

//任务控制模块
ThingsTask ThingsT[THINGSTASKNUMMAX] = {0};

void RTOS_Task_Create(unsigned char  i,unsigned char  Type,unsigned int   Time, unsigned char  sFlag, unsigned char  State,void (*Func)(unsigned char,unsigned char ) )
{  
    ThingsT[i].Type = Type;//类型 0 不执行的表示任务被删除  1定时调用的Time被减到零执行1次 2定时到了自动删除任务的
    ThingsT[i].Time = Time;//定时计数减到0 运行一次
    ThingsT[i].sFlag = sFlag;//手动执行一次 定时未到时手动开启执行一次的标志
    ThingsT[i].State = State;//任务函数里面一般就switch(State) case 。。。这样的状态机
    ThingsT[i].FUNC = Func;//第一个参数在轮询调用的时候传任务序号，第二个参数在轮询调用的时候传当前状态 			
  
}
//删除任务函数
void RTOS_Task_None(unsigned char  i)
{
  ThingsT[i].Type = 0;			
}
//任务调度函数
void ThingsTOS(void)
{		
  unsigned int i = 0;
  for (i = 0; i < THINGSTASKNUMMAX; i++)
  {
    if(ThingsT[i].Type == 1)//运行后不会自动删除
    {
      if(ThingsT[i].Time == 0 || (ThingsT[i].sFlag) != 0)//两种触发方式一种是 定时到了 另一种信号sflag非零
      {
        (ThingsT[i].FUNC)(i,ThingsT[i].State); 
      }
    }
    else if(ThingsT[i].Type == 2)//运行后自动删除
    {
      if(ThingsT[i].Time == 0 || (ThingsT[i].sFlag) != 0)//两种触发方式一种是 定时到了 另一种信号sflag非零
      {
        (ThingsT[i].FUNC)(i,ThingsT[i].State); 
        RTOS_Task_None(i);//自动删除这个任务 如果不重新创建任务则不会再运行的
      }
    }
  }
}


//计数值的复原 把它放到状态机函数中
void ThingsTtimerset(unsigned char  i, unsigned int Time)
{
 ThingsT[i].Time = Time;
}


//计数值的自减放到毫秒定时中断终
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

//任务：回调函数
void LED0_BLINK_Task(unsigned char i,unsigned char State)
{
   
  ThingsTtimerset(I_LED0_TASK,500);//重复的调用的话复原时间计数值
  switch(State)//状态机
  {
  case 0:ThingsT[i].State=1;break;
  case 1:ThingsT[i].State=0;break;
  }
}

//任务：回调函数 
void LED1_BLINK_Task(unsigned char i,unsigned char State)
{
   
  ThingsTtimerset(I_LED1_TASK,500);//重复的调用的话复原时间计数值
  switch(State)//状态机
  {
  case 0:ThingsT[i].State=1;break;
  case 1:ThingsT[i].State=0;break;
  }
}

//创建任务其实就是创建回调函数
void CreateSomeTask(void)
{
  RTOS_Task_Create(I_LED0_TASK,1,500,0,0,LED0_BLINK_Task);
  RTOS_Task_Create(I_LED1_TASK,1,500,0,0,LED1_BLINK_Task);
}