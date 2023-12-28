#include "Digital.h"

void Digital_Delay2ms(void) {
	static unsigned char data i, j;

	_nop_();
	i = 4;
	j = 146;
	do {
		while (--j);
	} while (--i);
}

//initial digital
void Digital_Initial(const unsigned char value[8]) {
    item = value;
}

//light digital
void Digital_Light(void) {
	static unsigned char index = 0;
	
	for(index = 0; index < 8; index++) {
		__digital__ = cell[index];
		__data__ = number[item[index]];
		Digital_Delay2ms();
	}
}