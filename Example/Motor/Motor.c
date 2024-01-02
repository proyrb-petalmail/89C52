#include "Motor.h"

#define COUNT_MAX 10

sbit _motor_ = P1^0;

static float rate; //直流电机上下文
static bit state; //直流电机状态

//initial motor
void Motor_Initial(const float invert_rate) {
	rate = invert_rate;
}

//emit or shut sound
void Motor_Emit(const bit value) {
	state = (value == 0) ? 0 : 1;
}

//execute
void Motor_Drive(void) {
   static unsigned char count; //计数器
   
   if(state == 1) {
		if(count < COUNT_MAX * rate) {_motor_ = 1;}
		else {_motor_ = 0;}
      count = ++count % COUNT_MAX;
   }
   else {_motor_ = 0;}
}