#include "LCD1602.h"

//read state of LCD
void LCD_Write(const unsigned char value, const unsigned char mode)
{
	static unsigned char busy_state = 0;
	
	_LCD_RW_ = 1;				//read-mode
	_LCD_RS_ = 0;				//state-mode
	do
	{
		_LCD_EN_ = 1;
		busy_state = _LCD_BS_;
		_LCD_EN_ = 0;
	} while(busy_state & 0x01 != 0x00);
	
	_LCD_RW_ = 0;					//write-mode
	_LCD_RS_ = mode;				//0(command) 1(data)
	__LCD_Ports__ = value;		//commands
	_LCD_EN_ = 1;					//LCD get the value
	_LCD_EN_ = 0;					//LCD execute the value
}

//initial the LCD
void LCD_Initial(void)
{
	LCD_Write(0x38, 0);			//use 8 bits to control 2 rows of 5*7 LED matrix
	LCD_Write(0x06, 0);			//AC add one, screen maintain
	LCD_Write(0x0C, 0);			//open screen, close cursor, close blink
	LCD_Write(0x01, 0);			//clear the screen
}

//clear the screen
void LCD_Clear(void)
{
	LCD_Write(0x01, 0);			//clear the screen
}

//print a char at the current cursor
void LCD_PrtChar(const char value)
{	
	LCD_Write(value, 1);
}

//print a char at the position
void LCD_PrtCharAt(const char value, const unsigned char x, const unsigned char y)
{
	LCD_Write(0x80 | (y * 0x40 + x), 0);
	LCD_Write(value, 1);
}

//print a string at the current cursor
void LCD_PrtStr(const char *value)
{
	while(*value != '\0')
	{
		LCD_PrtChar(*value);
		value++;
	}
}

//print a string at the position
void LCD_PrtStrAt(const char *value, const unsigned char x, const unsigned char y)
{
	if(*value != '\0')
	{
		LCD_PrtCharAt(*value, x, y);
		value++;
	}
	while(*value != '\0')
	{
		LCD_PrtChar(*value);
		value++;
	}
}