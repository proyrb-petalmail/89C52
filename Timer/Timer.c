#include "Timer.h"

//initial the timer0
void Timer0_Initial(const unsigned char high, const unsigned char low)
{
	//set the initial value for timer0
	_Timer0_H_ = high;
	_Timer0_L_ = low;
	
	EA = 1;				//open the root of interrupt
	ET0 = 1;			//open thr branch of interrupt
	
	TMOD = 0x01;	//set the mode(0000 0001)
	
	//the max value is 2^16 = 65536
	//the value is 64614=0xFC66(1ms)
	//the value is 56320=0xDC00(10ms)
	//the value is 19456=0x4C00(50ms)
	TL0 = _Timer0_L_;
	TH0 = _Timer0_H_;
	
	TR0 = 1;			//start the timer0 for ready
}

//restart the timer0
void Timer0_Restart(void)
{
	//reload the initial value
	TL0 = _Timer0_L_;
	TH0 = _Timer0_H_;
}

//the interrupt program of the timer0
void Timer0_Interrupt(void);		//the function needs to be defined in the file where that is used