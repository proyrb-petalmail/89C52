#ifndef __LCD1602_H__
#define __LCD1602_H__

#include <REGX52.H>
#include "Delay/Delay.h"

void LCD_Initial(void); //初始化液晶屏

void LCD_Clear(void); //清屏

void LCD_PrtChar(const char value); //在光标当前位置打印指定字符

void LCD_PrtCharAt(const char value, const unsigned char x, const bit y); //在指定位置打印指定字符

void LCD_PrtStr(const char * value); //在光标当前位置打印指定字符串

void LCD_PrtStrAt(const char * value, const unsigned char x, const bit y); //在指定位置打印指定字符串

#endif