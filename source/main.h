
#ifndef _MAIN_H_
#define	_MAIN_H_

#include <reg51.h>

typedef unsigned char uchar8;
typedef unsigned int  uint16;

#define		FOSC	24000000L
#define		T1MS	(65536 - FOSC/1000);

sfr 	IE2       	= 0xaf;
sfr 	AUXR		= 0x8e;
sfr 	INT_CLKO	= 0x8f;
sfr 	T2H       	= 0xd6;
sfr 	T2L       	= 0xd7;

sbit 	T0CLKO		= P3^5;
sbit 	P3_3 		= P3^3;
sbit	P3_4		= P3^4;

static void SCH_Init(void);
static void SCH_Start(void);

#endif
