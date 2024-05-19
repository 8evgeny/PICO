/**
 * Copyright (c) 2020 Raspberry Pi (Trading) Ltd.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "pico/stdlib.h"
#if 0
- должно быть pico-sdk
- после компиляции зажать BOOT и подать питание на pico
- перетащить файл uf2 в корень
#endif
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
    uart_init(uart0, 115200);
    // Set the GPIO pin mux to the UART - 0 is TX, 1 is RX
    gpio_set_function(0, GPIO_FUNC_UART);
    gpio_set_function(1, GPIO_FUNC_UART);
    gpio_set_dir(RED_PIN, GPIO_OUT);
    gpio_set_dir(GREEN_PIN, GPIO_OUT);
    gpio_set_dir(BLUE_PIN, GPIO_OUT);
    while (true) {
        char ch = uart_getc(uart0);
        if (ch == '1'){
            gpio_put(RED_PIN, 1);
            gpio_put(GREEN_PIN, 0);
            gpio_put(BLUE_PIN, 0);
        }
        if (ch == '2'){
            gpio_put(RED_PIN, 0);
            gpio_put(GREEN_PIN, 1);
            gpio_put(BLUE_PIN, 0);
        }
        if (ch == '3'){
            gpio_put(RED_PIN, 0);
            gpio_put(GREEN_PIN, 0);
            gpio_put(BLUE_PIN, 1);
        }
        if (ch == '0'){
            gpio_put(RED_PIN, 0);
            gpio_put(GREEN_PIN, 0);
            gpio_put(BLUE_PIN, 0);
        }
        uart_putc(uart0, ch);
    }
#endif
}
