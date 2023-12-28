#ifndef __BUTTON_H__
#define __BUTTON_H__

#include <REGX52.H>

sfr __Button__ = 0xB0;

static unsigned char _Last_Button_ = 0;	    //last key
static unsigned char _Last_State_ = 0;      //last state of P3

unsigned char Button_Scan(void);		    //harvest now key(At the moment of falling edge) by scaning button

#endif