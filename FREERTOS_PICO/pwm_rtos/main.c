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
     uint32_t timeSleep
} arg;

void vPwmTask(struct struct_arg_t * arg) {
    gpio_set_function(arg->pin, GPIO_FUNC_PWM);
    uint slice_num = pwm_gpio_to_slice_num(arg->pin);


    // Get some sensible defaults for the slice configuration. By default, the
    // counter is allowed to wrap over its maximum range (0 to 2**16-1)
    pwm_config config = pwm_get_default_config();
    // Set divider, reduces counter clock to sysclock/this value
    pwm_config_set_clkdiv(&config, arg->div);
    // Load the configuration into our PWM slice, and set it running.
    pwm_init(slice_num, &config, true);


    static int fade = 0;
    static bool going_up = true;
//    // Set period of 4 cycles (0 to 3 inclusive)
//    pwm_set_wrap(slice_num, 3);
//    // Set channel A output high for one cycle before dropping
//    pwm_set_chan_level(slice_num, PWM_CHAN_A, 1);
//    // Set initial B output high for three cycles before dropping
//    pwm_set_chan_level(slice_num, PWM_CHAN_B, 3);
//    // Set the PWM running
//    pwm_set_enabled(slice_num, true);


    while (1)
    {
        if (going_up) {
            ++fade;
            if (fade > 250) {
                fade = 250;
                going_up = false;
//                sleep_ms(arg->timeSleep);
            }
        } else {
            --fade;
            if (fade < 0) {
                fade = 0;
                going_up = true;
//                sleep_ms(arg->timeSleep);
            }
        }
        // Square the fade value to make the LED's brightness appear more linear
        // Note this range matches with the wrap value
        pwm_set_gpio_level(arg->pin, fade * fade);
        sleep_ms(10);
    }

}

int main() {

    arg arg1, arg2, arg3, arg4, arg5, arg6;

    arg1.div = 4.f; arg2.div = 4.f; arg3.div = 4.f; arg5.div = 4.f;
    arg1.pin = PICO_DEFAULT_LED_PIN; arg2.pin = 2; arg3.pin = 3; arg4.pin = 4;
    arg1.timeSleep = 1000; arg2.timeSleep = 2000; arg3.timeSleep = 3000; arg4.timeSleep = 4000;


    xTaskCreate(vPwmTask, "Pwm Task1", 128, (void *)&arg1, 1, NULL);
    xTaskCreate(vPwmTask, "Pwm Task2", 128, (void *)&arg2, 1, NULL);
//    xTaskCreate(vPwmTask, "Pwm Task3", 128, (void *)&arg3, 1, NULL);
//    xTaskCreate(vPwmTask, "Pwm Task4", 128, (void *)&arg4, 1, NULL);
    vTaskStartScheduler();
}

