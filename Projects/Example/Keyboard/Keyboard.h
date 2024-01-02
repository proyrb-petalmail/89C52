#ifndef __KEYBOARD_H__
#define __KEYBOARD_H__

#include <REGX52.H>

#define KEYBOARD_NONE 0 //定义无按钮组合
#define KEYBOARD_K1 1
#define KEYBOARD_K2 2
#define KEYBOARD_K3 3
#define KEYBOARD_K4 4
#define KEYBOARD_K5 5
#define KEYBOARD_K6 6
#define KEYBOARD_K7 7
#define KEYBOARD_K8 8
#define KEYBOARD_K9 9
#define KEYBOARD_K10 10
#define KEYBOARD_K11 11
#define KEYBOARD_K12 12
#define KEYBOARD_K13 13
#define KEYBOARD_K14 14
#define KEYBOARD_K15 15
#define KEYBOARD_K16 16

unsigned char Keyboard_Value(void);	//返回键盘的键值

#endif