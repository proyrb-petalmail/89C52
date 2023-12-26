#ifndef __LCD1602_H__
#define __LCD1602_H__

#include <REGX52.H>

sbit _LCD_RW_ = P2^5;		//set read-mode(1) or write-mode(0)
sbit _LCD_RS_ = P2^6;		//set data-mode(1) or command-mode(0)
sbit _LCD_EN_ = P2^7;		//set the reading status of LCD registers: LCD get the value(1) or LCD execute the value(0)
sbit _LCD_BS_ = 0x80^7;		//set the state of LCD

sfr __LCD_Ports__ = 0x80;	//that is equal to P0

void LCD_Write(const unsigned char value, const unsigned char mode);    //write into LCD

void LCD_Initial(void);		//initial the LCD

void LCD_Clear(void);		//clear the screen

void LCD_PrtChar(const char value);		//print a char at the current cursor

void LCD_PrtCharAt(const char value, const unsigned char x, const unsigned char y);		//print a char at the position

void LCD_PrtStr(const char *value);		//print a string at the current cursor

void LCD_PrtStrAt(const char *value, const unsigned char x, const unsigned char y);		//print a string at the position

#endif