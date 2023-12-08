#include "LCD1602.h"

//delay 1ms
void LCD_Delay1ms(void)	//@11.0592MHz
{
	unsigned char data i, j;

	_nop_();
	i = 2;
	j = 199;
	do
	{
		while (--j);
	} while (--i);
}

//write command to LCD
void LCD_WriteCommand(const unsigned char command)
{
	_LCD_RW_ = 0;			//write-mode
	_LCD_RS_ = 0;			//command-mode
	__LCD_Ports__ = command;		//command
	_LCD_EN_ = 1;			//LCD get the value
	LCD_Delay1ms();		//delay 1ms
	_LCD_EN_ = 0;			//LCD execute the value
	LCD_Delay1ms();		//delay 1ms
}

//write value to LCD
void LCD_WriteValue(const unsigned char value)
{
	_LCD_RW_ = 0;			//write-mode
	_LCD_RS_ = 1;			//value-mode
	__LCD_Ports__ = value;		//value
	_LCD_EN_ = 1;			//LCD get the value
	LCD_Delay1ms();		//delay 1ms
	_LCD_EN_ = 0;			//LCD execute the value
	LCD_Delay1ms();		//delay 1ms
}

//clear the screen
void LCD_Clear(void)
{
	LCD_WriteCommand(0x01);		//clear the screen
}

//initial the LCD
void LCD_Initial(void)
{
	LCD_WriteCommand(0x38);		//use 8 bits to control 2 rows of 5*7 LED matrix
	LCD_WriteCommand(0x06);		//AC add one, screen maintain
	LCD_WriteCommand(0x0C);		//open screen, close cursor, close blink
	LCD_WriteCommand(0x01);		//clear the screen
}

//print a char at the current cursor
void LCD_PrtChar(const char value)
{	
	LCD_WriteValue(value);
}

//print a char at the position
void LCD_PrtCharAt(const char value, const unsigned char x, const unsigned char y)
{
	LCD_WriteCommand(0x80 | (y * 0x40 + x));
	LCD_WriteValue(value);
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