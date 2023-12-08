#include "KeyMatrix.h"

//scan the key matrix to get the pressed key value
unsigned char KM_Scan(void)
{
	static unsigned char row = 0, key = 0;
	
	key = 0;
	
	//scan every row
	for(row = 0; row < 4; row++)
	{
		__KM__ = 0xFF;
		__KM__ = ~(0x80 >> row);	//select the row
		
		//get the key value
		switch((~__KM__) & 0x0F)
		{
			case 0x00:
				break;
			case 0x01:
				key = row * 4 + 4;
				break;
			case 0x02:
				key = row * 4 + 3;
				break;
			case 0x04:
				key = row * 4 + 2;
				break;
			case 0x08:
				key = row * 4 + 1;
				break;
		}
		
		//out of the loop if a key is pressed
		if(key != 0)
		{
			break;
		}
	}
	
	return key;
}