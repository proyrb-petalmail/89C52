#include "Button.h"

sfr __button__ = 0xB0;

unsigned char Button_Value(void) {
   static unsigned char last_value = BUTTON_NONE; //上一次获取的键值
   unsigned char now_value; //此次获取的键值
   unsigned char value; //实际返回的键值
   
   __button__ = BUTTON_NONE; //进行必要的初始化操作
   now_value = __button__; //获取当前键值
   value = ((now_value == BUTTON_NONE) && (last_value != BUTTON_NONE)) ? last_value : BUTTON_NONE; //获取所有按钮抬起时对应的键值
   last_value = now_value; //更新上一次获取的键值

   return value; //返回键值
}