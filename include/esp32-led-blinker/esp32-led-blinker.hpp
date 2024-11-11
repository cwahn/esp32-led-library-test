#ifndef _ESP32_LED_BLINKER_HPP
#define _ESP32_LED_BLINKER_HPP

#include "driver/gpio.h"

void setup_led(gpio_num_t gpio_num);

void toggle_led();

#endif // _ESP32_LED_BLINKER_HPP
