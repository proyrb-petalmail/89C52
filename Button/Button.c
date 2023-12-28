#include "Button.h"

//harvest now key(At the moment of falling edge) by scaning button
unsigned char Button_Scan(void) {
	static unsigned char now_button = 0, button = 0;

	last_state = __button__;		//save last state
	__button__ = 0x0F;				//initial button

	//0000 1110 0E
	//0000 1101 0D
	//0000 1011 0B
	//0000 0111 07
	//0000 1111 0F
	switch(__button__ & 0x0F) {
		case 0x0E:
			//K2
			now_button = 2;
			break;
		case 0x0D:
			//K1
			now_button = 1;
			break;
		case 0x0B:
			//K3
			now_button = 3;
			break;
		case 0x07:
			//K4
			now_button = 4;
			break;
		default:
			now_button = 0;
			break;
	}

	__button__ = last_state;		//recovery last state

	if(now_button == last_button) {
		button = 0;
	}
	else {
		if(last_button == 0) {
			button = 0;
		}
		else {
			button = last_button;
		}
	}
	last_button = now_button;

	return button;
}