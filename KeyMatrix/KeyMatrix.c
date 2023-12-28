#include "KeyMatrix.h"

//scan key matrix
unsigned char KeyMatrix_Scan(void) {
	static unsigned char _row_ = 0, now_key = 0, _key_ = 0;
	
	_Last_state_ = __KM__;	//save last state
	
	//scan every row
	for(_row_ = 0; _row_ < 4; _row_++) {
		__KM__ = 0xFF;				//reset
		__KM__ = ~(0x80 >> _row_);	//select the row
		
		//get the key value
		switch((~__KM__) & 0x0F) {
			case 0x00:
				now_key = 0;
				break;
			case 0x01:
				now_key = _row_ * 4 + 4;
				break;
			case 0x02:
				now_key = _row_ * 4 + 3;
				break;
			case 0x04:
				now_key = _row_ * 4 + 2;
				break;
			case 0x08:
				now_key = _row_ * 4 + 1;
				break;
		}
		
		//out of the loop if a key is pressed
		if(now_key != 0) {
			break;
		}
	}
	
	__KM__ = _Last_state_;	//recovery last state
	
	if(_Last_Key_ == 0) {
		_key_ = 0;
	}
	else {
		if(now_key == 0) {
			_key_ = _Last_Key_;
		}
		else {
			_key_ = 0;
		}
	}
	_Last_Key_ = now_key;
	
	return _key_;
}