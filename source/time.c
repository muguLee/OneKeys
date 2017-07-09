
#include "time.h"

void Delay_us(uchar8 xus)		//@24.000MHz
{
	uchar8 i, j;	
	for(i=xus; i!=0; i--)
	{
		j = 3;
		while (--j);
	}
}
