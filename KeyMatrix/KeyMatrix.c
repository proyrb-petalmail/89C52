#include "KeyMatrix.h"

//scan key matrix
unsigned char KeyMatrix_Scan(void)
{
	static unsigned char row = 0, now_key = 0, key = 0;
	
	//scan every row
	for(row = 0; row < 4; row++)
	{
		__KM__ = 0xFF;					//reset
		__KM__ = ~(0x80 >> row);	//select the row
		
		//get the key value
		switch((~__KM__) & 0x0F)
		{
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
		}
		
		//out of the loop if a key is pressed
		if(now_key != 0)
		{
			break;
		}
	}
	
	if(_Last_Key_ == 0)
	{
		key = 0;
	}
	else
	{
		if(now_key == 0)
		{
			key = _Last_Key_;
		}
		else
		{
			key = 0;
		}
	}
	_Last_Key_ = now_key;
	
	return key;
}