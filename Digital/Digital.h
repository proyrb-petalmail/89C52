#ifndef __DIGITAL_H__
#define __DIGITAL_H__

#include <REGX52.H>
#include <INTRINS.H>

static unsigned char* _values_ = 0;

//LED8 -> Y7 -> 0001 1100 -> 0x1C
//LED7 -> Y6 -> 0001 1000 -> 0x18
//LED6 -> Y5 -> 0001 0100 -> 0x14
//LED5 -> Y4 -> 0001 0000 -> 0x10
//LED4 -> Y3 -> 0000 1100 -> 0x0C
//LED3 -> Y2 -> 0000 1000 -> 0x08
//LED2 -> Y1 -> 0000 0100 -> 0x04
//LED1 -> Y0 -> 0000 0000 -> 0x00
static const unsigned char _unit_[8] = { 0x00, 0x04, 0x08, 0x0C, 0x10, 0x14, 0x18, 0x1C };

//     .gfe dcba
//----------------------
//0 -> 0011 1111 -> 0x3F
//1 -> 0000 0110 -> 0x06
//2 -> 0101 1011 -> 0x5B
//3 -> 0100 1111 -> 0x4F
//4 -> 0110 0110 -> 0x66
//5 -> 0110 1101 -> 0x6D
//6 -> 0111 1101 -> 0x7D
//7 -> 0000 0111 -> 0x07
//8 -> 0111 1111 -> 0x7F
//9 -> 0110 1111 -> 0x6F
//- -> 0100 0000 -> 0x40
static const unsigned char _number_[10] = { 0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7D, 0x07, 0x7F, 0x6F };

void Digital_Initial(const unsigned char values[8]); //initial digital

void Digital_Light(void);   //light digital

#endif