#include "Keyboard.h"

sfr __keyboard__ = 0x90;

unsigned char Keyboard_Value(void) {
   static unsigned char last_value; //上一次获取的键值
   unsigned char last_state; //执行之前引脚的状态
   unsigned char row; //当前扫描的行
   unsigned char row_value; //当前扫描的行的键值
   unsigned char now_value; //此次获取的键值
   unsigned char key_count; //当前按下的按键个数
   unsigned char value; //实际返回的键值

   last_state = __keyboard__; //记录执行之前引脚的状态
   for(key_count = now_value = row = 0; row < 4; row++) {
      __keyboard__ = 0xFF; //进行必要的初始化操作
      __keyboard__ = ~(0x80 >> row); //扫描当前行
      switch((~__keyboard__) & 0x0F) {
         case 0x00:
            row_value = 0; //没有按键按下
            break;
         case 0x01:
            row_value = row * 4 + 4;
            key_count++;
            break;
         case 0x02:
            row_value = row * 4 + 3;
            key_count++;
            break;
         case 0x04:
            row_value = row * 4 + 2;
            key_count++;
            break;
         case 0x08:
            row_value = row * 4 + 1;
            key_count++;
            break;
         default:
            row_value = 17; //多个按键按下
            key_count += 2;
            break;
		}
      if(key_count > 1) {
         now_value = 17; //如果有多个按键被按下则返回其他键值
         break;
      }
      if(row_value != 0) {
         now_value = row_value; //如果当前行有按键按下则返回对应键值
      }
   }
   __keyboard__ = last_state; //将引脚恢复到执行之前的状态
   value = (now_value == 0 && 0 < last_value && last_value < 17) ? last_value : 0; //获取单个按键抬起时对应的键值
   last_value = now_value; //更新上一次获取的键值

   return value; //返回键值
}