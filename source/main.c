

#include "main.h"
#include "sch51.h"
#include "Key.h"
#include "WS2812.h"
#include "Beep.h"



void main()
{
	//��������ʼ��
	SCH_Init();

	//�����ʼ��
	Key_Init();
	WS2812_Init();
	Beep_Init();	
	
	//�������
	SCH_Add_Task(Key_Update,	0,	4 );
	SCH_Add_Task(WS2812_Update,	1,	30);
	SCH_Add_Task(Beep_Update,	3,	2 );

	//��ʼ����
	SCH_Start();

	while(1)
	{
		SCH_Dispatch_Tasks();
	}
}



void SCH_Init(void)
{
	uchar8 i;
	uint16 timeBase = T1MS;

	for (i = 0; i < SCH_MAX_TASKS; i++) 
	{
		SCH_Delete_Task(i);
	}

	AUXR |= 0x04;
	T2L = timeBase;
	T2H = timeBase >> 8;
	AUXR|= 0x10;
	IE2 |= 0x04;
}

void SCH_Start(void) 
{
	EA = 1;
}

void SCH_Update(void) interrupt 12
{
	uchar8  i;
	
	for (i = 0; i < SCH_MAX_TASKS; i++)			//������������
	{
		if (SCH_tasks_G[i].pTask)
		{
			if (SCH_tasks_G[i].Delay == 0)		//������ʱʱ�䵽
			{
				SCH_tasks_G[i].RunMe = 1;		//�����������б�־
				if (SCH_tasks_G[i].Period)		//�������¿�ʼ��ʱ
				{
					SCH_tasks_G[i].Delay = SCH_tasks_G[i].Period;
				}
			}
			else
			{ 
				SCH_tasks_G[i].Delay -= 1;		//����ʱ��δ����������ʱ��1
			}
		}         
	}
}

