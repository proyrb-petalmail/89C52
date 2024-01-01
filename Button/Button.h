#ifndef __BUTTON_H__
#define __BUTTON_H__

#include <REGX52.H>

//引脚状态    值   按钮组合
//0000 1111 = 0x0F 无
//0000 1110 = 0x0E B2
//0000 1101 = 0x0D B1
//0000 1011 = 0x0B B3
//0000 0111 = 0x07 B4
//0000 1100 = 0x0C B1 B2
//0000 1010 = 0x0A B3 B2
//0000 0110 = 0x06 B4 B2
//0000 1001 = 0x09 B3 B1
//0000 0101 = 0x05 B4 B1
//0000 0011 = 0x03 B4 B3
//0000 1000 = 0x08 B3 B1 B2
//0000 0100 = 0x04 B4 B1 B2
//0000 0010 = 0x02 B4 B3 B2
//0000 0001 = 0x01 B4 B3 B1
//0000 0000 = 0x00 B4 B3 B1 B2
#define BUTTON_NONE 0x0F //定义无按钮组合
#define BUTTON_B1 0x0D
#define BUTTON_B2 0x0E
#define BUTTON_B3 0x0B
#define BUTTON_B4 0x07
#define BUTTON_B1_B2 0x0C
#define BUTTON_B1_B3 0x09
#define BUTTON_B1_B4 0x05
#define BUTTON_B2_B3 0x0A
#define BUTTON_B2_B4 0x06
#define BUTTON_B3_B4 0x03
#define BUTTON_B1_B2_B3 0x08
#define BUTTON_B1_B2_B4 0x04
#define BUTTON_B1_B3_B4 0x01
#define BUTTON_B2_B3_B4 0x02
#define BUTTON_B1_B2_B3_B4 0x00

unsigned char Button_Value(void); //获取所有按钮抬起时对应的键值

#endif