#include "Delay.h"

//for 11.0592MHz

void Delay2ms(void) {
	static unsigned char data i, j;

	_nop_();
	i = 4;
	j = 146;
	do {
		while (--j);
	} while (--i);
}

void Delay10ms(void) {
	static unsigned char data i, j;

	i = 18;
	j = 235;
	do {
		while (--j);
	} while (--i);
}