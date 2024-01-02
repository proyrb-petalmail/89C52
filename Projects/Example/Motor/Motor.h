#ifndef __MOTOR_H__
#define __MOTOR_H__

#include <REGX52.H>

void Motor_Initial(const float invert_rate); //初始化直流电机

void Motor_Emit(const bit value); //发出信号

void Motor_Drive(void); //驱动

#endif