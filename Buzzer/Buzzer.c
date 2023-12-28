#include "Buzzer.h"

void Buzzer_Delay2ms(void)
{
	unsigned char data i, j;

	_nop_();
	i = 4;
	j = 146;
	do
	{
		while (--j);
	} while (--i);
}

void Beep(void)
{
	static unsigned char times;
	
	for(times = 0; times < 15; times++)
	{
		Buzzer = !Buzzer;
		Buzzer_Delay2ms();
	}
}