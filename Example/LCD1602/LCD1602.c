#include "LCD1602.h"

sbit _LCD_RW_ = P2^5;
sbit _LCD_RS_ = P2^6;
sbit _LCD_EN_ = P2^7;
sbit _LCD_BS_ = 0x80^7;

sfr __LCD_port__ = 0x80;

void LCD_Write(const unsigned char value, const bit mode) {
	bit busy_state;
	
	_LCD_RW_ = 1;_LCD_RS_ = 0; //读状态模式
	do {
		_LCD_EN_ = 1;busy_state = _LCD_BS_;_LCD_EN_ = 0; //读状态
	} while(busy_state & 0x01 != 0x00);
	_LCD_RW_ = 0;_LCD_RS_ = mode; //写0:指令或1:数据模式
	__LCD_port__ = value; //准备
	_LCD_EN_ = 1;_LCD_EN_ = 0; //写入
}

void LCD_Initial(void) {
	unsigned char times;
	
	for(times = 0; times < 5; times++) {
		_LCD_RW_ = 0;_LCD_RS_ = 0;
		__LCD_port__ = 0x38;
		_LCD_EN_ = 1;_LCD_EN_ = 0;
		Delay10ms(); //延迟10ms
	}
	LCD_Write(0x38, 0);
	LCD_Write(0x06, 0);
	LCD_Write(0x01, 0);
	LCD_Write(0x0f, 0);
}

void LCD_Clear(void) {
	LCD_Write(0x01, 0);
}

void LCD_PrtChar(const char value) {	
	LCD_Write(value, 1);
}

void LCD_PrtCharAt(const char value, const unsigned char x, const bit y) {
	LCD_Write(0x80 | (y * 0x40 + x), 0);
	LCD_Write(value, 1);
}

void LCD_PrtStr(const char * value) {
	while(*value != '\0') {
		LCD_PrtChar(*value);
		value++;
	}
}

void LCD_PrtStrAt(const char * value, const unsigned char x, const bit y) {
	if(*value != '\0') {
		LCD_PrtCharAt(*value, x, y);
		value++;
	}
	while(*value != '\0') {
		LCD_PrtChar(*value);
		value++;
	}
}