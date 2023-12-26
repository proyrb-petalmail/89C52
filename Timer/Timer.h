#ifndef __TIMER_H__
#define __TIMER_H__

#include <REGX52.H>

static unsigned char _Timer0_H_ = 0x00, _Timer0_L_ = 0x00;		//initial value of the timer0
static unsigned char _Timer1_H_ = 0x00, _Timer1_L_ = 0x00;		//initial value of the timer1

void Timer_Initial(const unsigned char timer, const unsigned char high, const unsigned char low);		//initial timer

void Timer_Start(const unsigned char timer);		//start timer

void Timer_Stop(const unsigned char timer);			//stop timer

void Timer0_Interrupt(void);	//interrupt of 1

void Timer1_Interrupt(void);	//interrupt of 3

#endif