
#ifndef _KEY_H_
#define	_KEY_H_

#include "main.h"

#define 	KEY_PIN			P3_4
#define		KEY_PRESSED		0		//按键按下的状态
#define 	DEBONCE_CNT		2		//按键消抖次数

typedef enum _KEY_STATE
{
	KEY_RELEASE = 0,
	KEY_PRESS,	
}keyState_e;

extern keyState_e keyState;

void Key_Init(void);
void Key_Update(void);

#endif