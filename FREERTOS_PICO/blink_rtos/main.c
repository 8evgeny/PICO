#include "pico/stdlib.h"
#include "FreeRTOS.h"
#include "task.h"
typedef struct struct_arg_t {
     uint8_t pin;
     uint16_t period;
} arg;
void vBlinkTask(struct struct_arg_t * arg) {
    gpio_init(arg->pin);
    gpio_set_dir(arg->pin, GPIO_OUT);
   for (;;) {
      gpio_put(arg->pin, 1);
      vTaskDelay(arg->period);
      gpio_put(arg->pin, 0);
      vTaskDelay(arg->period);
   }
}

int main() {

   arg arg1, arg2, arg3, arg4, arg5, arg6;
   arg1.period = 100;arg2.period = 200;arg3.period = 300;arg4.period = 400;arg5.period = 500;arg6.period = 600;
   arg1.pin = PICO_DEFAULT_LED_PIN;
   arg2.pin = 2;arg3.pin = 3;arg4.pin = 4;arg5.pin = 5;arg6.pin = 6;
   xTaskCreate(vBlinkTask, "Blink Task", 128, (void *)&arg1, 1, NULL);
   xTaskCreate(vBlinkTask, "Blink Task2", 128, (void *)&arg2, 1, NULL);
   xTaskCreate(vBlinkTask, "Blink Task3", 128, (void *)&arg3, 1, NULL);
   xTaskCreate(vBlinkTask, "Blink Task4", 128, (void *)&arg4, 1, NULL);
   xTaskCreate(vBlinkTask, "Blink Task5", 128, (void *)&arg5, 1, NULL);
   xTaskCreate(vBlinkTask, "Blink Task6", 128, (void *)&arg6, 1, NULL);
   vTaskStartScheduler();
}

