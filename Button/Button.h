#ifndef __BUTTON_H__
#define __BUTTON_H__

#include <REGX52.H>

sfr __button__ = 0xB0;

static unsigned char last_button = 0;	    //last key
static unsigned char last_state = 0;        //last state of P3

unsigned char Button_Scan(void);		    //harvest now key(At the moment of falling edge) by scaning button

#endif