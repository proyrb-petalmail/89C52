#include "Button.h"

//harvest now key(At the moment of falling edge) by scaning button
unsigned char Button_Scan(void) {
	static unsigned char _Now_Button_ = 0, _Button_ = 0;

	_Last_State_ = __Button__;		//save last state
	__Button__ = 0x0F;				//initial button

	//0000 1110 0E
	//0000 1101 0D
	//0000 1011 0B
	//0000 0111 07
	//0000 1111 0F
	switch(__Button__ & 0x0F) {
		case 0x0E:
			//K2
			_Now_Button_ = 2;
			break;
		case 0x0D:
			//K1
			_Now_Button_ = 1;
			break;
		case 0x0B:
			//K3
			_Now_Button_ = 3;
			break;
		case 0x07:
			//K4
			_Now_Button_ = 4;
			break;
		default:
			_Now_Button_ = 0;
			break;
	}

	__Button__ = _Last_State_;		//recovery last state

	if(_Now_Button_ == _Last_Button_) {
		_Button_ = 0;
	}
	else {
		if(_Last_Button_ == 0) {
			_Button_ = 0;
		}
		else {
			_Button_ = _Last_Button_;
		}
	}
	_Last_Button_ = _Now_Button_;

	return _Button_;
}