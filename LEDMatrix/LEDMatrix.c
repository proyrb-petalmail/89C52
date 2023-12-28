#include "LEDMatrix.h"

void LEDMatrix_Delay2ms(void) {
	static unsigned char data i, j;

	_nop_();
	i = 4;
	j = 146;
	do {
		while (--j);
	} while (--i);
}

//inital LEDMatrix
void LEDMatrix_Initial(const unsigned char value[], const unsigned char amount) {
	item = value;
	length = amount;
	start = 0;
}

//light LEDMatrix
void LEDMatrix_Light(void) {
	static unsigned char column = 0, times = 0;
	
	for(column = 0; column < 8; column++) {
		__column__ = 0xFF;
		
		for(times = 0; times < 8; times++) {
			if((*(item + ((start + column) % length)) & (0x80 >> times)) == (0x80 >> times)) {
				_DI_ = 1;
			}
			else {
				_DI_ = 0;
			}
			
			_DA_ = 0;
			_DA_ = 1;
		}
		
		_DO_ = 0;
		_DO_ = 1;
		
		__column__ = ~(0x80 >> column);
		
		LEDMatrix_Delay2ms();
	}
}

//load next values
void LEDMatrix_Next(void) {
	start++;
	start %= length;
}