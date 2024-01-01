#ifndef __LEDMATRIX_H__
#define __LEDMATRIX_H__

#include <REGX52.H>
#include "Delay/Delay.h"

void LEDMatrix_Initial(const unsigned char item[], const unsigned char amount); //初始化发光二极管矩阵

void LEDMatrix_Light(void); //点亮发光二极管矩阵

void LEDMatrix_Left(void); //左移

void LEDMatrix_Right(void); //右移

#endif