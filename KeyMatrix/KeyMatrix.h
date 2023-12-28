#ifndef __KEY_MATRIX_H__
#define __KEY_MATRIX_H__

#include <REGX52.H>

sfr __key_matrix__ = 0x90;		        //equal to P1

static unsigned char last_key = 0;	    //last key
static unsigned char last_state = 0;	//last state of P1

unsigned char KeyMatrix_Scan(void);		//harvest now key(At the moment of falling edge) by scaning key matrix

#endif