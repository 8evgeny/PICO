#include "pico/stdlib.h"
#include "FreeRTOS.h"
#include "task.h"
#include "hardware/pwm.h"
#include <stdio.h>
#include "pico/time.h"
#include "hardware/irq.h"

typedef struct struct_arg_t {
     uint8_t pin;
     float div;
     void (*on_pwm_wrap)()
} arg;

void on_pwm_wrap1() {
    static int fade = 0;
    static bool going_up = true;
    // Clear the interrupt flag that brought us here
    pwm_clear_irq(pwm_gpio_to_slice_num(PICO_DEFAULT_LED_PIN));

    if (going_up) {
        ++fade;
        if (fade > 250) {
            fade = 250;
            going_up = false;
        }
    } else {
        --fade;
        if (fade < 0) {
            fade = 0;
            going_up = true;
        }
    }
    // Square the fade value to make the LED's brightness appear more linear
    // Note this range matches with the wrap value
    pwm_set_gpio_level(PICO_DEFAULT_LED_PIN, fade * fade);
}
void on_pwm_wrap2() {
    static int fade = 0;
    static bool going_up = true;
    // Clear the interrupt flag that brought us here
    pwm_clear_irq(pwm_gpio_to_slice_num(2));

    if (going_up) {
        ++fade;
        if (fade > 250) {
            fade = 250;
            going_up = false;
        }
    } else {
        --fade;
        if (fade < 0) {
            fade = 0;
            going_up = true;
        }
    }
    // Square the fade value to make the LED's brightness appear more linear
    // Note this range matches with the wrap value
    pwm_set_gpio_level(2, fade * fade);
}

void vPwmTask(struct struct_arg_t * arg) {
    irq_set_exclusive_handler(PWM_IRQ_WRAP, arg->on_pwm_wrap);
    irq_set_enabled(PWM_IRQ_WRAP, true);
    gpio_set_function(arg->pin, GPIO_FUNC_PWM);
    uint slice_num = pwm_gpio_to_slice_num(arg->pin);

    pwm_clear_irq(slice_num);
    pwm_set_irq_enabled(slice_num, true);
    irq_set_exclusive_handler(PWM_IRQ_WRAP, arg->on_pwm_wrap);
    irq_set_enabled(PWM_IRQ_WRAP, true);

    // Get some sensible defaults for the slice configuration. By default, the
    // counter is allowed to wrap over its maximum range (0 to 2**16-1)
    pwm_config config = pwm_get_default_config();
    // Set divider, reduces counter clock to sysclock/this value
    pwm_config_set_clkdiv(&config, arg->div);
    // Load the configuration into our PWM slice, and set it running.
    pwm_init(slice_num, &config, true);
    while (1)
        tight_loop_contents();

}

int main() {

    arg arg1, arg2, arg3, arg4, arg5, arg6;

    arg1.div = 32.f; arg2.div = 8.f;
    arg1.pin = PICO_DEFAULT_LED_PIN; arg2.pin = 2; arg3.pin = 3; arg4.pin = 4; arg5.pin = 5; arg6.pin = 6;
    arg1.on_pwm_wrap= on_pwm_wrap1; arg2.on_pwm_wrap= on_pwm_wrap2;


    xTaskCreate(vPwmTask, "Pwm Task1", 128, (void *)&arg1, 1, NULL);
    xTaskCreate(vPwmTask, "Pwm Task2", 128, (void *)&arg2, 1, NULL);
    vTaskStartScheduler();
}

