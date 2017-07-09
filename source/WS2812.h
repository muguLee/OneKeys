
#ifndef _WS2812_H_
#define	_WS2812_H_

#include "main.h"

#define		WS2812_NUMS			1
#define		WS2812_LED_NUMS		WS2812_NUMS*3
#define		WS2812_DI			P3_3

typedef struct _RGB_STRUCT
{
	uchar8 	G;
	uchar8 	R;
	uchar8 	B;		
}rgb_s;

extern rgb_s rgbBuf[WS2812_NUMS];

void WS2812_Init();
void WS2812_Update();
static void WS2812_SendBuff(rgb_s *data pBuff);

#endif