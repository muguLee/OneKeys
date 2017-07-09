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

#ifndef _SCH51_H
#define _SCH51_H

#include "main.h"

#define SCH_MAX_TASKS   3		//����������������һ�������1

typedef data struct 
{
   void (code * pTask)(void); 	//����ص�����ָ��
   uint16 Delay;				//���񴴽����ӳٶ��ִ��      
   uint16 Period;				//�����������  
   uchar8 RunMe;				//���������־       
} sTask;

extern sTask SCH_tasks_G[SCH_MAX_TASKS];

uchar8 	SCH_Add_Task(void (code*) (void), const uint16, const uint16);	//���������  
void   	SCH_Delete_Task(const uchar8);									//ɾ��������
void  	SCH_Dispatch_Tasks(void);										//�����ɷ�����

#endif
