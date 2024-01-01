#ifndef __DIGITAL_H__
#define __DIGITAL_H__

#include <REGX52.H>

#include "Delay/Delay.h"

void Digital_Initial(const unsigned char item[], const unsigned char amount); //设置数码管要显示的内容和内容长度

void Digital_Light(void); //点亮数码管

void Digital_Left(void); //左移

void Digital_Right(void); //右移

#endif