#ifndef __KEY_MATRIX_H__
#define __KEY_MATRIX_H__

#include <REGX52.H>

sfr __KM__ = 0x90;		//equal to P1

unsigned char KM_Scan(void);		//scan the key matrix to get the pressed key value

#endif