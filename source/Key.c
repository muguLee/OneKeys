
#include "Key.h"

keyState_e keyState;

void Key_Init(void)
{
	KEY_PIN = 1;
	keyState = KEY_RELEASE;
}


void Key_Update(void)
{
	static uchar8 debonce;
	
	if(KEY_PIN == KEY_PRESSED)
	{
		debonce += 1;
		if(debonce > DEBONCE_CNT)
		{
			debonce = DEBONCE_CNT;
			keyState = KEY_PRESS;
			return;
		}
		keyState = KEY_RELEASE;
		return;
	}
	debonce = 0;
	keyState = KEY_RELEASE;	
}


