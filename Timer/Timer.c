#include "Timer.h"

//initial timer
void Timer_Initial(const unsigned char timer, const unsigned char high, const unsigned char low) {
	switch(timer) {
		case 0:
			//set the initial value for timer0
			timer0_h = high;
			timer0_l = low;
			
			//the max value is 2^16 = 65536
			//the value is 64614=0xFC66(1ms)
			//the value is 56320=0xDC00(10ms)
			//the value is 19456=0x4C00(50ms)
			TL0 = timer0_l;
			TH0 = timer0_h;
			
			TMOD = (TMOD & 0xF0) | 0x01;	//set the mode(xxxx 0001)
		
			ET0 = 1;	//open thr branch of interrupt
			break;
		case 1:
			//set the initial value for timer1
			timer1_h = high;
			timer1_l = low;
			
			//the max value is 2^16 = 65536
			//the value is 64614=0xFC66(1ms)
			//the value is 56320=0xDC00(10ms)
			//the value is 19456=0x4C00(50ms)
			TL1 = timer1_l;
			TH1 = timer1_h;
			
			TMOD = (TMOD & 0x0F) | 0x10;	//set the mode(0001 xxxx)
		
			ET1 = 1;	//open thr branch of interrupt
			break;
		default:
			break;
	}
	EA = 1;				//open the root of interrupt
}

//start timer
void Timer_Start(const unsigned char timer) {
	switch(timer) {
		case 0:
			TR0 = 1;			//start timer0
			break;
		case 1:
			TR1 = 1;			//start timer1
			break;
		default:
			break;
	}
}

//stop timer
void Timer_Stop(const unsigned char timer) {
	switch(timer) {
		case 0:
			TR0 = 0;			//stop timer0
			break;
		case 1:
			TR1 = 0;			//stop timer1
			break;
		default:
			break;
	}
}

//callback
void Timer_Interrput(const unsigned char timer, const void* function) {
	switch(timer) {
		case 0:
			timer0_interrupt = function;
			break;
		case 1:
			timer1_interrupt = function;
			break;
		default:
			break;
	}
}