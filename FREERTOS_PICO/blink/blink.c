/**
 * Copyright (c) 2020 Raspberry Pi (Trading) Ltd.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "pico/stdlib.h"

int main() {
#ifndef PICO_DEFAULT_LED_PIN
#warning blink example requires a board with a regular LED
#else
//    const uint LED_PIN = PICO_DEFAULT_LED_PIN;
    const uint RED_PIN = 2;
    const uint GREEN_PIN = 3;
    const uint BLUE_PIN = 4;
    gpio_init(RED_PIN);
    gpio_init(GREEN_PIN);
    gpio_init(BLUE_PIN);
    gpio_set_dir(RED_PIN, GPIO_OUT);
    gpio_set_dir(GREEN_PIN, GPIO_OUT);
    gpio_set_dir(BLUE_PIN, GPIO_OUT);
    while (true) {
        gpio_put(RED_PIN, 1);
        sleep_ms(1000);
        gpio_put(RED_PIN, 0);
        sleep_ms(1000);
        gpio_put(GREEN_PIN, 1);
        sleep_ms(1000);
        gpio_put(GREEN_PIN, 0);
        sleep_ms(1000);
        gpio_put(BLUE_PIN, 1);
        sleep_ms(1000);
        gpio_put(BLUE_PIN, 0);
        sleep_ms(1000);
    }
#endif
}
