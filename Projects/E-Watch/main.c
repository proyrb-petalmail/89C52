//功能实现：
//除了闹钟的显示有点bug，其他功能都实现了



#define MEMORY_SIZE (1024 * 32) //定义堆内存的大小

#define DIGITAL_VALUE_LENGTH 8 //定义数码管显示内容的长度

#include <stdlib.h>
#include "Timer/Timer.h"
#include "Button/Button.h"
#include "Buzzer/Buzzer.h"
#include "LEDQueue/LEDQueue.h"
#include "Digital/Digital.h"

static char xdata memory[MEMORY_SIZE]; //申请内存池

static bit signal_scan_button; //是否扫描按钮
static bit signal_boot_watch; //是否启动电子表
static bit signal_config_clock; //是否配置闹钟
static bit signal_flash_watch; //是否刷新电子表
static bit signal_flash_unit; //是否电子表闪烁
static bit signal_ring_watch; //是否闹铃闪烁
static unsigned char signal_config_unit; //配置电子表时间
static unsigned char hour, min, sec; //初始化电子表计时的小时、分钟和秒
static unsigned char clock_hour = 23, clock_min = 59, clock_sec = 59; //初始化电子表闹钟的小时、分钟和秒

void timer0_callback(void); //定时器0的回调函数
void timer1_callback(void); //定时器0的回调函数

void main(void) {
   unsigned char button_value = BUTTON_NONE; //按钮的键值
   unsigned char digital_value[DIGITAL_VALUE_LENGTH] = {0,0,10,0,0,10,0,0}; //数码管显示内容
   
   init_mempool(memory, MEMORY_SIZE); //初始化内存池
   
   Buzzer_Initial(500, 4); //设置蜂鸣器发声时长500ms和频率250Hz
   Digital_Initial(digital_value, DIGITAL_VALUE_LENGTH); //设置数码管显示内容和其长度
   
   Timer_Initial(0, 0x4C, 0x00); //将定时器0的中断间隔设置为50.0ms
   Timer_Callback(0, timer0_callback); //配置定时器0中断时的回调函数
	Timer_Control(0, 1); //启动定时器0
   
   Timer_Initial(1, 0xFC, 0x66); //将定时器1的中断间隔设置为1.00ms
   Timer_Callback(1, timer1_callback); //配置定时器1中断时的回调函数
	Timer_Control(1, 1); //启动定时器1
   
   while(1) {
      //扫描按钮
      if(signal_scan_button == 1) {
         signal_scan_button = 0; //重置信号
         if((button_value = Button_Value()) != BUTTON_NONE) {Buzzer_Emit(1);} //获取按钮的键值并发声
         switch(button_value) {
            case BUTTON_B1:
               signal_boot_watch = ~signal_boot_watch;
               break;
            case BUTTON_B2:
               if(((signal_boot_watch == 0) && (signal_config_clock == 0)) || (signal_config_clock == 1)) {
                  signal_config_unit++;
                  if(signal_config_clock == 1 && signal_config_unit == 4) {
                     signal_config_unit = 1; //设置电子表时间或闹钟的调整模式
                  }
                  else {
                     signal_config_unit %= 4; //设置电子表时间或闹钟的调整模式
                  }
               }
               break;
            case BUTTON_B3:
               switch(signal_config_unit) {
                  case 1:
                     ((signal_boot_watch == 0) && (signal_config_clock == 0)) ? ++sec : ++clock_sec;
                     break;
                  case 2:
                     ((signal_boot_watch == 0) && (signal_config_clock == 0)) ? ++min : ++clock_min;
                     break;
                  case 3:
                     ((signal_boot_watch == 0) && (signal_config_clock == 0)) ? ++hour : ++clock_hour;
                     break;
                  default:
                     break;
               }
               break;
            case BUTTON_B4:
               signal_config_unit = ((signal_config_clock = ~signal_config_clock) == 1) ? 1 : 0;
               break;
            default:
               break;
         }
      }
      
      //闪烁
      if((clock_hour == hour) && (clock_min == min) && (clock_sec == sec)) {
         signal_ring_watch = 1;
      }
      
      //刷新显示数码管
      if(signal_flash_watch == 1) {
         signal_flash_watch = 0;
         signal_flash_unit = ~signal_flash_unit;
         if(signal_config_unit == 0 && signal_config_clock == 0) {
            digital_value[7] = sec % 10;
            digital_value[6] = sec / 10;
            digital_value[4] = min % 10;
            digital_value[3] = min / 10;
            digital_value[1] = hour % 10;
            digital_value[0] = hour / 10;
         }
         else {
            if(signal_boot_watch == 0 && signal_config_unit != 0) {
               switch(signal_config_unit) {
                  case 1:
                     if(signal_flash_unit == 1) {
                        digital_value[7] = sec % 10;
                        digital_value[6] = sec / 10;
                     }
                     else {
                        digital_value[7] = 11;
                        digital_value[6] = 11;
                     }
                     digital_value[4] = min % 10;
                     digital_value[3] = min / 10;
                     digital_value[1] = hour % 10;
                     digital_value[0] = hour / 10;
                     break;
                  case 2:
                     digital_value[7] = sec % 10;
                     digital_value[6] = sec / 10;
                     if(signal_flash_unit == 1) {
                        digital_value[4] = min % 10;
                        digital_value[3] = min / 10;
                     }
                     else {
                        digital_value[4] = 11;
                        digital_value[3] = 11;
                     }
                     digital_value[1] = hour % 10;
                     digital_value[0] = hour / 10;
                     break;
                  case 3:
                     digital_value[7] = sec % 10;
                     digital_value[6] = sec / 10;
                     digital_value[4] = min % 10;
                     digital_value[3] = min / 10;
                     if(signal_flash_unit == 1) {
                        digital_value[1] = hour % 10;
                        digital_value[0] = hour / 10;
                     }
                     else {
                        digital_value[1] = 11;
                        digital_value[0] = 11;
                     }
                     break;
                  default:
                     break;
               }
            }
            else {
               if(signal_config_clock == 1) {
                  if(signal_boot_watch == 0 && signal_config_unit != 0) {
                     switch(signal_config_unit) {
                        case 1:
                           if(signal_flash_unit == 1) {
                              digital_value[7] = clock_sec % 10;
                              digital_value[6] = clock_sec / 10;
                           }
                           else {
                              digital_value[7] = 11;
                              digital_value[6] = 11;
                           }
                           digital_value[4] = clock_min % 10;
                           digital_value[3] = clock_min / 10;
                           digital_value[1] = clock_hour % 10;
                           digital_value[0] = clock_hour / 10;
                           break;
                        case 2:
                           digital_value[7] = clock_sec % 10;
                           digital_value[6] = clock_sec / 10;
                           if(signal_flash_unit == 1) {
                              digital_value[4] = clock_min % 10;
                              digital_value[3] = clock_min / 10;
                           }
                           else {
                              digital_value[4] = 11;
                              digital_value[3] = 11;
                           }
                           digital_value[1] = clock_hour % 10;
                           digital_value[0] = clock_hour / 10;
                           break;
                        case 3:
                           digital_value[7] = clock_sec % 10;
                           digital_value[6] = clock_sec / 10;
                           digital_value[4] = clock_min % 10;
                           digital_value[3] = clock_min / 10;
                           if(signal_flash_unit == 1) {
                              digital_value[1] = clock_hour % 10;
                              digital_value[0] = clock_hour / 10;
                           }
                           else {
                              digital_value[1] = 11;
                              digital_value[0] = 11;
                           }
                           break;
                        default:
                           break;
                     }
                  }
               }
               else {
                  digital_value[7] = 11;
                  digital_value[6] = 11;
                  digital_value[4] = 11;
                  digital_value[3] = 11;
                  digital_value[1] = 11;
                  digital_value[0] = 11;
               }
            }
         }
      }
      Digital_Light(); //点亮数码管
   }
}

void timer0_callback(void) {
   static unsigned char count; //记录回调函数执行次数
   static unsigned int time; //记录电子表执行次数
   
   count++;
   if((count %= 2) == 0) {
      signal_scan_button = 1;//发出扫描按钮和键盘的信号
   }
   
   time++;
   if(signal_boot_watch == 1) {
      if((time %= 20) == 0) {
         sec++;
         if(sec == 60) {
            sec = 0;
            min++;
            if(min == 60) {
               min = 0;
               hour = ++hour % 60;
            }
         }
      }
   }
}

void timer1_callback(void) {
   static unsigned int count; //记录回调函数执行次数
   static unsigned char time; //记录回调函数执行次数
   
   Buzzer_Beep(); //按钮发声
   
   time++;
   if((time %= 200) == 0) {
      signal_flash_watch = 1;
   }
   
   if(signal_ring_watch == 1) {
      count++;
      if(count % 60 == 0) {
         LEDQueue_Light(count);
      }
      if(count % 60000 == 0) {
         count = signal_ring_watch = 0; //重置
      }
   }
}