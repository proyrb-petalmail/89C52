#ifndef __TIMER_H__
#define __TIMER_H__

#include <REGX52.H>

//中断间隔 计数器数值
//0.50ms   65075 = 0xFE33
//1.00ms   64614 = 0xFC66
//10.0ms   56320 = 0xDC00
//50.0ms   19456 = 0x4C00
void Timer_Initial(const bit timer, const unsigned char high, const unsigned char low); //初始化指定定时器

void Timer_Control(const bit timer, const bit control); //控制指定定时器开关

void Timer_Callback(const bit timer, const void * const callback); //为指定定时器配置中断时的回调函数

#endif