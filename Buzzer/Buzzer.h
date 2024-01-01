#ifndef __BUZZER_H__
#define __BUZZER_H__

#include <REGX52.H>

void Buzzer_Initial(const unsigned char time, const unsigned char period); //设置蜂鸣器发声时长和频率

void Buzzer_Emit(const bit value); //发出信号

void Buzzer_Beep(void); //发声

#endif