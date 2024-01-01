#include "Digital.h"

sfr __digital__ = 0xA0;
sfr __data__ = 0x80;

//序号             数值
//0    0001 1100 = 0x1C
//1    0001 1000 = 0x18
//2    0001 0100 = 0x14
//3    0001 0000 = 0x10
//4    0000 1100 = 0x0C
//5    0000 1000 = 0x08
//6    0000 0100 = 0x04
//7    0000 0000 = 0x00
static const unsigned char code cell[8] = { 0x1C, 0x18, 0x14, 0x10, 0x0C, 0x08, 0x04, 0x00 }; //数码管单元

//显示符号 .gfe dcba   数值
//0        0011 1111 = 0x3F
//1        0000 0110 = 0x06
//2        0101 1011 = 0x5B
//3        0100 1111 = 0x4F
//4        0110 0110 = 0x66
//5        0110 1101 = 0x6D
//6        0111 1101 = 0x7D
//7        0000 0111 = 0x07
//8        0111 1111 = 0x7F
//9        0110 1111 = 0x6F
static const unsigned char code number[10] = { 0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7D, 0x07, 0x7F, 0x6F }; //显示字符

static const unsigned char * value; //想要显示的字符对应的数值数组
static unsigned char length; //数组长度
static unsigned char start; //显示起点

void Digital_Initial(const unsigned char item[], const unsigned char amount) {
	value = item;
	length = amount;
	start = 0;
}

void Digital_Light(void) {
	static unsigned char order; //显示数码管的序号
	
	for(order = 0; order < 8; order++) {
		__data__ = number[value[(start + order) % length]]; //显示字符
		__digital__ = cell[order]; //切换数码管
		Delay2ms(); //延时2ms
	}
}

void Digital_Left(void) {
	start = ++start % length;
}

void Digital_Right(void) {
	start = (start + length - 1) % length;
}