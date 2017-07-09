
#include "WS2812.h"
#include "time.h"
#include "Key.h"

rgb_s rgbBuf[WS2812_NUMS];

void WS2812_Init()
{
	rgbBuf[0].R = 0;
	rgbBuf[0].G = 0;
	rgbBuf[0].B = 0;
}

void WS2812_Update()
{
	if(keyState == KEY_PRESS)
	{
		rgbBuf[0].R += 1;
		rgbBuf[0].G += rgbBuf[0].R / 2;
		rgbBuf[0].B += rgbBuf[0].R / 3;
	}
	WS2812_SendBuff(rgbBuf);
}

void WS2812_SendBuff(rgb_s *data pBuff) 
{
	pBuff = pBuff;
//	EA = 0;			

#pragma ASM
	
	CLR		WS2812_DI
	MOV		R0,	#150				//@24.000MHz  50us以上低电平RESET
RES_DELAY50:
	DJNZ	R0, RES_DELAY50
	MOV		R0,	#150
RES_DELAY50_N:
	DJNZ	R0, RES_DELAY50_N
	
	MOV		R5, #WS2812_LED_NUMS	//LED灯数
	MOV		A,	@R1					//RGB数据指针
	MOV		R0,	#8					//8bit记数
SEND_BIT_START:
	SETB	WS2812_DI
	NOP
	RLC		A						//左移判断
	JC		SEND_BIT1_H				//发1码		H:850ns   L:400ns		
	NOP								//发0码		H:400ns   L:850ns
	CLR		WS2812_DI
	CJNE	R0, #1,SEND_BIT0_L_NOP	//不是最后一位跳转执行空延时
	INC		R1						//是最后一位则取下一字节数据
	MOV		A, @R1
	MOV		R0,#9
	DJNZ	R5, SEND_NEXT_BIT		//发下一位码
	SJMP	SEND_END				//所有灯刷新完
SEND_BIT0_L_NOP:
	NOP
	NOP
	NOP
	NOP
	NOP
	NOP
	SJMP	SEND_NEXT_BIT
SEND_BIT1_H:
	CJNE	R0, #1,SEND_BIT1_H_NOP	//不是最后一位跳转执行空延时
	INC		R1						//是最后一位则取下一字节数据
	MOV		A, @R1
	MOV		R0,#9
	DJNZ	R5, SEND_BIT1_L			//发下一位码
	CLR		WS2812_DI				//所有灯刷新完
	NOP
	NOP
	NOP
	SJMP	SEND_END
SEND_BIT1_H_NOP:
	NOP
	NOP
	NOP
	NOP
	NOP
	NOP
	NOP
SEND_BIT1_L: 
	CLR		WS2812_DI
	NOP
	NOP
	NOP
SEND_NEXT_BIT: 
	DJNZ	R0, SEND_BIT_START
SEND_END: 
	SETB	WS2812_DI
	
#pragma ENDASM

//	EA = 1;
}

