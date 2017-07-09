/*------------------------------------------------------------------*-
   COPYRIGHT
   ---------
   This code is from the book:
   PATTERNS FOR TIME-TRIGGERED EMBEDDED SYSTEMS by Michael J. Pont
   [Pearson Education, 2001; ISBN: 0-201-33138-1]. 
   This code is copyright (c) 2001 by Michael J. Pont.
   See book for copyright details and other information.
   
   ������ο����鼮��ʱ�䴥��Ƕ��ʽϵͳ���ģʽ
-*------------------------------------------------------------------*/

#include "main.h"
#include "sch51.h"

sTask SCH_tasks_G[SCH_MAX_TASKS];

static void SCH_Go_To_Sleep(void);


void SCH_Dispatch_Tasks(void)
{
	uchar8 Index;

	for (Index = 0; Index < SCH_MAX_TASKS; Index++)		//�����������񣬲�ִ�о�������
	{
		if (SCH_tasks_G[Index].RunMe > 0) 
		{
			(*SCH_tasks_G[Index].pTask)();				//ִ������
			SCH_tasks_G[Index].RunMe -= 1;				//�������������־

			if (SCH_tasks_G[Index].Period == 0)			//����ǵ���������ִ�����ɾ������
			{
				SCH_Delete_Task(Index);
			}
		}
	}

   SCH_Go_To_Sleep();		//����͹�������ģʽ         
}


uchar8 SCH_Add_Task(void (code * pFunction)(), const uint16 DELAY, const uint16 PERIOD)    
{
	uchar8 Index = 0;

	while ((SCH_tasks_G[Index].pTask != 0) && (Index < SCH_MAX_TASKS))		//��������
	{
		Index++;
	}

	/*���������*/
	SCH_tasks_G[Index].pTask  = pFunction;
	SCH_tasks_G[Index].Delay  = DELAY;
	SCH_tasks_G[Index].Period = PERIOD;
	SCH_tasks_G[Index].RunMe  = 0;

	return Index;		//��������������
}


void SCH_Delete_Task(const uchar8 TASK_INDEX) 
{
	/*ɾ������*/
	SCH_tasks_G[TASK_INDEX].pTask   = 0x0000;
	SCH_tasks_G[TASK_INDEX].Delay   = 0;
	SCH_tasks_G[TASK_INDEX].Period  = 0;
	SCH_tasks_G[TASK_INDEX].RunMe   = 0;
}


void SCH_Go_To_Sleep()
{
	PCON |= 0x01;    //����˯��
}

