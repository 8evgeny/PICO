#include "pico/stdlib.h"
#include "FreeRTOS.h"
#include "task.h"
#include "hardware/pwm.h"

typedef struct struct_arg_t {
     uint8_t pin;
     uint16_t period;
} arg;
void vPwmTask(struct struct_arg_t * arg) {
    gpio_set_function(arg->pin, GPIO_FUNC_PWM);
    // Find out which PWM slice is connected to GPIO pin
    uint slice_num = pwm_gpio_to_slice_num(arg->pin);
    // Set period of 4 cycles (0 to 3 inclusive)
    pwm_set_wrap(slice_num, 3);
    // Set channel A output high for one cycle before dropping
    pwm_set_chan_level(slice_num, PWM_CHAN_A, 1);
    // Set initial B output high for three cycles before dropping
    pwm_set_chan_level(slice_num, PWM_CHAN_B, 3);
    // Set the PWM running
    pwm_set_enabled(slice_num, true);
    // Note we could also use pwm_set_gpio_level(gpio, x) which looks up the
    // correct slice and channel for a given GPIO.

   for (;;) {
      vTaskDelay(arg->period);
   }
}

int main() {

   arg arg1, arg2, arg3, arg4, arg5, arg6;
   arg1.period = 100;arg2.period = 200;arg3.period = 300;arg4.period = 400;arg5.period = 500;arg6.period = 600;
   arg1.pin = PICO_DEFAULT_LED_PIN;
   arg2.pin = 2;arg3.pin = 3;arg4.pin = 4;arg5.pin = 5;arg6.pin = 6;
   xTaskCreate(vPwmTask, "Pwm Task", 128, (void *)&arg1, 1, NULL);

   vTaskStartScheduler();
}

