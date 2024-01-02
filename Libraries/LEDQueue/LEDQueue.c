#include "LEDQueue.h"

sfr __led_queue__ = 0xA0;

void LEDQueue_Light(const unsigned char number) {
   __led_queue__ = ~number;
}