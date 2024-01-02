#include "LEDMatrix.h"

sbit _DI_ = P3^4;
sbit _DA_ = P3^6;
sbit _DO_ = P3^5;

sfr __column__ = 0x80;

static const unsigned char * value; //要显示的内容的数组
static unsigned char length; //数组长度
static unsigned char start; //显示起点

void LEDMatrix_Initial(const unsigned char item[], const unsigned char amount) {
   value = item;
   length = amount;
   start = 0;
}

void LEDMatrix_Light(void) {
   unsigned char column; //当前显示的列
   unsigned char times; //当前执行移位的次数
   
   for(column = 0; column < 8; column++) {
      __column__ = 0xFF; //消除上一列残影
      for(times = 0; times < 8; times++) {
         if((value[(start + column) % length] & (0x80 >> times)) == (0x80 >> times)) {_DI_ = 1;} //载入位数据
         else {_DI_ = 0;}
         _DA_ = 0;_DA_ = 1; //移位
      }
      _DO_ = 0;_DO_ = 1;//送出数据
      __column__ = ~(0x80 >> column); //切换下一列
      Delay2ms(); //延时2ms
	}
}

void LEDMatrix_Left(void) {
	start = ++start % length;
}

void LEDMatrix_Right(void) {
	start = (start + length - 1) % length;
}