/*********************************************************************************
Auth:���ǻ�� (z)diputs qq572981033 https://gitee.com/diputs/things-menu-list
********************************************************************************/
#include "ThingsL.h"
#include "ThingsEvent.h"


//�¼����飬�����¼���������ΪThingsLeventNumMax��20
//���в������¼�����ŵ�������鵱��
//�¼��Ĳ���������ThingsL_PutEvent�����������¼����ͣ��¼����ݣ��¼����ݳ��ȣ��¼�����������Լ�1��������������򷵻�-1
//�¼���ȡ�ã�����ThingsL_GetEvent�����������¼����ͣ���������ƥ����¼������ظ��¼��±꣬�޸������͵��¼��򷵻�-1
//�¼������ģ�����ThingsL_DetEvent�����������¼�������±꣬һ����Get���¼��� ��Ҫ������¼��Ӷ�����ɾ��, ��������ǰ��¼����ƽṹ���е��¼������Լ�����[id]-[cnt]֮����¼����鼯��ǰ��
ThingsL_EVENT_List thingsl_event_fifo[ThingsLeventNumMax];//�¼��Ķ����б�
ThingsL_Event_Con thingsl_event_control={//�¼����еĿ��Ʋ���ֻ��Ҫһ��������
  .cnt=0,
};

//etype   �¼�������
//ev_cmd  �¼���ָ��
//ev_Data �¼�������
//ev_len  �¼����ݵĳ���
//���أ��ɹ�д�뷵�ض�����ţ����ɹ����ظ�1
signed char ThingsL_PutEvent(unsigned int etype,unsigned short ev_cmd,unsigned char ev_len,void *ev_Data)
{
  if(thingsl_event_control.cnt<ThingsLeventNumMax)//����
  {
    thingsl_event_fifo[thingsl_event_control.cnt].ev_type=etype;//�¼�����
    thingsl_event_fifo[thingsl_event_control.cnt].ev_cmd=ev_cmd;//�¼�����
    thingsl_event_fifo[thingsl_event_control.cnt].ev_len=ev_len;//�¼������ݵĳ���
    thingsl_event_fifo[thingsl_event_control.cnt].ev_Data=ev_Data;//�¼�������
    thingsl_event_fifo[thingsl_event_control.cnt].ev_thingsgetmask=0;
    thingsl_event_control.cnt++;
    return thingsl_event_control.cnt;//�ִ��¼�����
  }
  return -1;
}
//etype ��Ҫ�������¼�����,�¼��Ľ��շ�������������β������¼������ͱ�ʾֻ��ȡ�ض����͵��¼�
//���أ��������ĵ�һ�������¼����͵������±꣬���ɹ����ظ�1
signed char ThingsL_GetEvent(unsigned int etype)
{
  unsigned char i=0;
  for(i=0;i<thingsl_event_control.cnt;i++)//�����¼����飬һ�������������±�
  {
    if(thingsl_event_fifo[i].ev_type==etype)
    {
      return i;
    }
  }
  return -1;
  
}

//id ��Ҫɾ�����¼� һ����Get���¼��� ��Ҫ������¼��Ӷ�����ɾ�� ��������ǰ��¼����ƽṹ���е��¼������Լ�����[id]-[cnt]֮����¼����鼯��ǰ��
//���أ��¼�������ɾ���򷵻��¼�����ֵ��δ������ɾ����
signed char ThingsL_DetEvent(signed char id)
{
  unsigned char i;
  if(id<thingsl_event_control.cnt&&
     id>=0&&                          //Ҫɾ�����¼����±귶Χ����
     thingsl_event_control.cnt>=1)    //�¼����������¼����
  {
    for(i=id;i<thingsl_event_control.cnt-1;i++)//�±�Ϊid���¼���ȡ���ˣ�[id]-[cnt]֮����¼����鼯��ǰ��
    {
      thingsl_event_fifo[i].ev_type=thingsl_event_fifo[i+1].ev_type;//�¼�����
      thingsl_event_fifo[i].ev_cmd=thingsl_event_fifo[i+1].ev_cmd;//�¼���cmd
      thingsl_event_fifo[i].ev_Data=thingsl_event_fifo[i+1].ev_Data;//�¼�������
      thingsl_event_fifo[i].ev_len=thingsl_event_fifo[i+1].ev_len;//�¼������ݳ���
    }
    thingsl_event_control.cnt--;//�¼�����  �������¼������ĵ���
    return thingsl_event_control.cnt;

  }else
  {
    return -1;
  }
}




