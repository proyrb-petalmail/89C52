#include "Delay.h"

//@11.0592MHz

void Delay2ms(void)
{
	unsigned char data i, j;

	_nop_();
	i = 4;
	j = 146;
	do
	{
		while (--j);
	} while (--i);
}

void Delay5ms(void)
{
	unsigned char data i, j;

	i = 9;
	j = 244;
	do
	{
		while (--j);
	} while (--i);
}

void Delay10ms(void)
{
	unsigned char data i, j;

	i = 18;
	j = 235;
	do
	{
		while (--j);
	} while (--i);
}

void Delay50ms(void)
{
	unsigned char data i, j;

	i = 90;
	j = 163;
	do
	{
		while (--j);
	} while (--i);
}

void Delay100ms(void)
{
	unsigned char data i, j;

	i = 180;
	j = 73;
	do
	{
		while (--j);
	} while (--i);
}