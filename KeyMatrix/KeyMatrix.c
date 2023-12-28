#include "KeyMatrix.h"

//scan key matrix
unsigned char KeyMatrix_Scan(void) {
	static unsigned char row = 0, now_key = 0, key = 0;
	
	last_state = __key_matrix__;			//save last state
	
	//scan every row
	for(row = 0; row < 4; row++) {
		__key_matrix__ = 0xFF;				//reset
		__key_matrix__ = ~(0x80 >> row);	//select the row
		
		//get the key value
		switch((~__key_matrix__) & 0x0F) {
			case 0x00:
				now_key = 0;
				break;
			case 0x01:
				now_key = row * 4 + 4;
				break;
			case 0x02:
				now_key = row * 4 + 3;
				break;
			case 0x04:
				now_key = row * 4 + 2;
				break;
			case 0x08:
				now_key = row * 4 + 1;
				break;
			default:
				now_key = 0;
				break;
		}
		
		//out of the loop if a key is pressed
		if(now_key != 0) {
			break;
		}
	}
	
	__key_matrix__ = last_state;	//recovery last state
	
	if(last_key == 0) {
		key = 0;
	}
	else {
		if(now_key == 0) {
			key = last_key;
		}
		else {
			key = 0;
		}
	}
	last_key = now_key;
	
	return key;
}