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

#ifndef _SCH51_H
#define _SCH51_H

#include "main.h"

#define SCH_MAX_TASKS   3		//最大任务数量，添加一个任务加1

typedef data struct 
{
   void (code * pTask)(void); 	//任务回调函数指针
   uint16 Delay;				//任务创建后延迟多久执行      
   uint16 Period;				//任务调用周期  
   uchar8 RunMe;				//任务就绪标志       
} sTask;

extern sTask SCH_tasks_G[SCH_MAX_TASKS];

uchar8 	SCH_Add_Task(void (code*) (void), const uint16, const uint16);	//添加任务函数  
void   	SCH_Delete_Task(const uchar8);									//删除任务函数
void  	SCH_Dispatch_Tasks(void);										//任务派发函数

#endif
