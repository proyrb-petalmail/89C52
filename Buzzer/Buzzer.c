#include "Buzzer.h"

sbit _buzzer_ = P2^5;

static unsigned char context[3]; //执行前的上下文
static bit last_state; //执行之前引脚的状态

void Buzzer_Initial(const unsigned char time, const unsigned char period) {
	context[0] = time;
	context[1] = period;
}

void Buzzer_Emit(const bit value) {
	context[2] = (value == 0) ? 0 : 1;
	last_state = _buzzer_; //记录执行之前引脚的状态
}

void Buzzer_Beep(void) {
   static unsigned char count; //计数器
   
	if(context[2] == 1) {
		if(count == context[0]) {
			count = context[2] = 0; //重置
			_buzzer_ = last_state; //将引脚恢复到执行前的状态
			return;
		}
		if(count % context[1] == 0) {
			_buzzer_ = ~_buzzer_;
		}
		count++;
	}
}