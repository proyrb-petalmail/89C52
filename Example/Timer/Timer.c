#include "Timer.h"

static unsigned char timer0_h, timer0_l; //定时器0的计数器的初始值
static unsigned char timer1_h, timer1_l; //定时器1的计数器的初始值

static void (* timer0_callback)(void); //定时器0中断时的回调函数
static void (* timer1_callback)(void); //定时器1中断时的回调函数

void Timer_Initial(const bit timer, const unsigned char high, const unsigned char low) {
   switch((unsigned char)timer) {
      case 0:
         TH0 = timer0_h = high;TL0 = timer0_l = low; //记录定时器0计数器的初始值
         TMOD = (TMOD & 0xF0) | 0x01; //设置定时器0的工作模式
         ET0 = 1;	//打开定时器0的中断
         break;
      case 1:
         TH1 = timer1_h = high;TL1 = timer1_l = low; //记录定时器1计数器的初始值
         TMOD = (TMOD & 0x0F) | 0x10; //设置定时器1的工作模式
         ET1 = 1; //打开定时器1的中断
         break;
	}
   EA = 1; //打开总中断
}

void Timer_Control(const bit timer, const bit control) {
   (timer == 0) ? (TR0 = (control == 0 ? 0 : 1)) : (TR1 = (control == 0 ? 0 : 1)); //启动或停止指定定时器的计数器
}

void Timer_Callback(const bit timer, void * const callback) {
   (timer == 0) ? (timer0_callback = callback) : (timer1_callback = callback); //为指定定时器配置中断时的回调函数
}

void Timer0_Interrupt(void) interrupt 1 {
   TH0 = timer0_h;TL0 = timer0_l; //将定时器0的计数器恢复为初始值
   if(timer0_callback) timer0_callback(); //如果定时器0中断时的回调函数存在则执行
}

void Timer1_Interrupt(void) interrupt 3 {
   TH1 = timer1_h;TL1 = timer1_l; //将定时器1的计数器恢复为初始值
   if(timer1_callback) timer1_callback(); //如果定时器1中断时的回调函数存在则执行
}