#ifndef __KEY_MATRIX_H__
#define __KEY_MATRIX_H__

#include <REGX52.H>

sfr __KM__ = 0x90;		//equal to P1

static unsigned char _Last_Key_ = 0;	//last key

unsigned char KeyMatrix_Scan(void);		//harvest now key(At the moment of falling edge) by scaning key matrix

#endif