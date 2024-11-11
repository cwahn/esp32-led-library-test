#include "include/esp32-led-blinker/esp32-led-blinker.hpp"

// #include <stdio.h>
// #include "freertos/FreeRTOS.h"
// #include "freertos/task.h"
// #include "driver/gpio.h"
// #include "esp_log.h"
// #include "led_strip.h"
// #include "sdkconfig.h"

#include "driver/gpio.h"

void setup_led(gpio_num_t gpio_num) {
    gpio_reset_pin(gpio_num);
    gpio_set_direction(gpio_num, GPIO_MODE_OUTPUT);
}

void toggle_led() {
    static bool is_led_on = false;

    if (is_led_on) {
        gpio_set_level(CONFIG_BLINK_GPIO, 0);
    } else {
        gpio_set_level(CONFIG_BLINK_GPIO, 1);
    }

    is_led_on = !is_led_on;
}