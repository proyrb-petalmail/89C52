#ifndef __LED_MATRIX_H__
#define __LED_MATRIX_H__

#include <REGX52.H>
#include <INTRINS.H>

sbit _DI_ = P3^4;			//set import
sbit _DA_ = P3^6;			//set add
sbit _DO_ = P3^5;		    //set output

sfr __column__ = 0x80;		//set column select

static const unsigned char *item = 0;   //values to light
static unsigned char length = 0;        //length of values
static unsigned char start = 0;		    //index of values

void LEDMatrix_Initial(const unsigned char value[], const unsigned char amount);	//inital LEDMatrix

void LEDMatrix_Light(void);	//light LEDMatrix

void LEDMatrix_Next(void);	//load next values

#endif