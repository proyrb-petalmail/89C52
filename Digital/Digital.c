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
void Digital_Initial(const unsigned char values[8]) {
    _values_ = values;
}

//light digital
void Digital_Light(void) {
	for(index = 0; index < 8; index++) {
		P2 = _unit_[index];
		P0 = _values_[index];
		Digital_Delay2ms();
	}
}