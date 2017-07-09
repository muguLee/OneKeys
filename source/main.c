

#include "main.h"
#include "sch51.h"
#include "Key.h"
#include "WS2812.h"
#include "Beep.h"



void main()
{
	//任务管理初始化
	SCH_Init();

	//任务初始化
	Key_Init();
	WS2812_Init();
	Beep_Init();	
	
	//添加任务
	SCH_Add_Task(Key_Update,	0,	4 );
	SCH_Add_Task(WS2812_Update,	1,	30);
	SCH_Add_Task(Beep_Update,	3,	2 );

	//开始任务
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
	
	for (i = 0; i < SCH_MAX_TASKS; i++)			//遍历所有任务
	{
		if (SCH_tasks_G[i].pTask)
		{
			if (SCH_tasks_G[i].Delay == 0)		//任务延时时间到
			{
				SCH_tasks_G[i].RunMe = 1;		//设置任务运行标志
				if (SCH_tasks_G[i].Period)		//任务重新开始计时
				{
					SCH_tasks_G[i].Delay = SCH_tasks_G[i].Period;
				}
			}
			else
			{ 
				SCH_tasks_G[i].Delay -= 1;		//任务时间未到，任务延时减1
			}
		}         
	}
}

