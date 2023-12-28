#include <INTRINS.H>
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
void LEDMatrix_Initial(const unsigned char values[], const unsigned char length) {
	_values_ = values;
	_length_ = length;
	_index_ = 0;
}

//light LEDMatrix
void LEDMatrix_Light(void) {
	static unsigned char column = 0, times = 0;
	
	for(column = 0; column < 8; column++) {
		__Column__ = 0xFF;
		
		for(times = 0; times < 8; times++) {
			if((*(_values_ + ((_index_ + column) % _length_)) & (0x80 >> times)) == (0x80 >> times)) {
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
		
		__Column__ = ~(0x80 >> column);
		
		LEDMatrix_Delay2ms();
	}
}

//load next values
void LEDMatrix_Next(void) {
	_index_++;
	_index_ %= _length_;
}