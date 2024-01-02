#define MEMORY_SIZE (1024 * 32) //定义堆内存的大小

#define DIGITAL_VALUE_LENGTH 16 //定义数码管显示内容的长度
#define LEDMATRIX_VALUE_LENGTH 16 //定义发光二极管矩阵显示内容的长度

#include <stdlib.h>
#include "Timer/Timer.h"
#include "Button/Button.h"
#include "Keyboard/Keyboard.h"
#include "Buzzer/Buzzer.h"
#include "LEDQueue/LEDQueue.h"
#include "Digital/Digital.h"
#include "LEDMatrix/LEDMatrix.h"
#include "LCD1602/LCD1602.h"
#include "Motor/Motor.h"

static char xdata memory[MEMORY_SIZE]; //申请内存池

static bit signal_scan_button; //是否扫描按钮
static bit signal_scan_keyboard; //是否扫描键盘

void timer0_callback(void); //定时器0的回调函数

void main(void) {
   unsigned char button_value = BUTTON_NONE; //按钮的键值
   unsigned char keyboard_value = KEYBOARD_NONE; //键盘的键值
   //unsigned char code digital_value[DIGITAL_VALUE_LENGTH] = {1,2,3,4,5,6,7,8,8,7,6,5,4,3,2,1}; //数码管显示内容
   //unsigned char code ledmatrix_value[LEDMATRIX_VALUE_LENGTH] = {0x00,0x00,0x12,0x22,0x7E,0x02,0x00,0x00,0x00,0x22,0x42,0x46,0x4A,0x52,0x22,0x00}; //发光二极管矩阵显示内容
   
   init_mempool(memory, MEMORY_SIZE); //初始化内存池
   
   Buzzer_Initial(50, 1); //设置蜂鸣器发声时长和频率
   Motor_Initial(1.0); //设置直流电机驱动比
   //Digital_Initial(digital_value, DIGITAL_VALUE_LENGTH); //设置数码管显示内容和其长度
   //LEDMatrix_Initial(ledmatrix_value, LEDMATRIX_VALUE_LENGTH); //设置发光二极管矩阵显示内容和其长度
   //LCD_Initial(); //初始化液晶屏
   
   Timer_Initial(0, 0xFC, 0x66); //将定时器0的中断间隔设置为1ms
   Timer_Callback(0, timer0_callback); //配置定时器0中断时的回调函数
	Timer_Control(0, 1); //启动定时器0
   
   while(1) {
      if(signal_scan_button == 1) {
         signal_scan_button = 0; //重置信号
         if((button_value = Button_Value()) != BUTTON_NONE) {Buzzer_Emit(1);} //获取按钮的键值并发声
         switch(button_value) {
            case BUTTON_B1:
               Motor_Emit(1);
               break;
            case BUTTON_B2:
               Motor_Emit(0);
               break;
            case BUTTON_B3:
               Motor_Initial(0.1);
               break;
            case BUTTON_B4:
               Motor_Initial(1.0);
               break;
            default:
               break;
         }
      }
      if(signal_scan_keyboard == 1) {
         signal_scan_keyboard = 0; //重置信号
         if((keyboard_value = Keyboard_Value()) != KEYBOARD_NONE) {Buzzer_Emit(1);} //获取键盘的键值并发声
         switch(keyboard_value) {
            case KEYBOARD_K1:
               break;
            case KEYBOARD_K2:
               break;
            case KEYBOARD_K3:
               break;
            case KEYBOARD_K4:
               break;
            case KEYBOARD_K5:
               break;
            case KEYBOARD_K6:
               break;
            case KEYBOARD_K7:
               break;
            case KEYBOARD_K8:
               break;
            case KEYBOARD_K9:
               break;
            case KEYBOARD_K10:
               break;
            case KEYBOARD_K11:
               break;
            case KEYBOARD_K12:
               break;
            case KEYBOARD_K13:
               break;
            case KEYBOARD_K14:
               break;
            case KEYBOARD_K15:
               break;
            case KEYBOARD_K16:
               break;
            default:
               break;
         }
      }
      //Digital_Light();
      //LEDMatrix_Light();
   }
}

void timer0_callback(void) {
   static unsigned char count; //记录回调函数执行次数
   
   if(count % 100 == 0) {
      signal_scan_keyboard = signal_scan_button = 1;//发出扫描按钮和键盘的信号
   }
   Buzzer_Beep(); //发声
   Motor_Drive(); //驱动

   count = ++count % 200; //计一次数
}