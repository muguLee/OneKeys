/*------------------------------------------------------------------*-
   COPYRIGHT
   ---------
   This code is from the book:
   PATTERNS FOR TIME-TRIGGERED EMBEDDED SYSTEMS by Michael J. Pont
   [Pearson Education, 2001; ISBN: 0-201-33138-1]. 
   This code is copyright (c) 2001 by Michael J. Pont.
   See book for copyright details and other information.
   
   本代码参考自书籍：时间触发嵌入式系统设计模式
-*------------------------------------------------------------------*/

#include "main.h"
#include "sch51.h"

sTask SCH_tasks_G[SCH_MAX_TASKS];

static void SCH_Go_To_Sleep(void);


void SCH_Dispatch_Tasks(void)
{
	uchar8 Index;

	for (Index = 0; Index < SCH_MAX_TASKS; Index++)		//遍历所有任务，并执行就绪任务
	{
		if (SCH_tasks_G[Index].RunMe > 0) 
		{
			(*SCH_tasks_G[Index].pTask)();				//执行任务
			SCH_tasks_G[Index].RunMe -= 1;				//重置任务就绪标志

			if (SCH_tasks_G[Index].Period == 0)			//如果是单次任务，则执行完后删除任务
			{
				SCH_Delete_Task(Index);
			}
		}
	}

   SCH_Go_To_Sleep();		//进入低功耗休眠模式         
}


uchar8 SCH_Add_Task(void (code * pFunction)(), const uint16 DELAY, const uint16 PERIOD)    
{
	uchar8 Index = 0;

	while ((SCH_tasks_G[Index].pTask != 0) && (Index < SCH_MAX_TASKS))		//任务索引
	{
		Index++;
	}

	/*添加新任务*/
	SCH_tasks_G[Index].pTask  = pFunction;
	SCH_tasks_G[Index].Delay  = DELAY;
	SCH_tasks_G[Index].Period = PERIOD;
	SCH_tasks_G[Index].RunMe  = 0;

	return Index;		//返回新任务索引
}


void SCH_Delete_Task(const uchar8 TASK_INDEX) 
{
	/*删除任务*/
	SCH_tasks_G[TASK_INDEX].pTask   = 0x0000;
	SCH_tasks_G[TASK_INDEX].Delay   = 0;
	SCH_tasks_G[TASK_INDEX].Period  = 0;
	SCH_tasks_G[TASK_INDEX].RunMe   = 0;
}


void SCH_Go_To_Sleep()
{
	PCON |= 0x01;    //进入睡眠
}

