#ifndef __TIMER_H__
#define __TIMER_H__

#include <REGX52.H>

static unsigned char timer0_h = 0x00, timer0_l = 0x00;		//initial value of the timer0
static unsigned char timer1_h = 0x00, timer1_l = 0x00;		//initial value of the timer1

static void (*timer0_interrupt)(void);		    //function of timer0
static void (*timer1_interrupt)(void);		    //function of timer1

void Timer_Initial(const unsigned char timer, const unsigned char high, const unsigned char low);   //initial timer

void Timer_Start(const unsigned char timer);    //start timer

void Timer_Stop(const unsigned char timer);	    //stop timer

void Timer_Interrput(const unsigned char timer, const void* function);		//callback

#endif