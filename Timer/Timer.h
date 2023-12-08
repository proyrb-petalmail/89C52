#ifndef __TIMER_H__
#define __TIMER_H__

#include <REGX52.H>

static unsigned char _Timer0_H_ = 0x00, _Timer0_L_ = 0x00;		//the initial value of the timer0

void Timer0_Initial(const unsigned char high, const unsigned char low);		//initial the timer0

void Timer0_Restart(void);			//restart the timer0

void Timer0_Interrupt(void);		//the interrupt program

#endif