#include "pico/stdlib.h"
#include "FreeRTOS.h"
#include "task.h"
typedef struct struct_arg_t {
     uint8_t pin;
     uint16_t period;
} arg;
void vBlinkTask(struct struct_arg_t * arg) {
   for (;;) {
      gpio_put(arg->pin, 1);
      vTaskDelay(arg->period);
      gpio_put(arg->pin, 0);
      vTaskDelay(arg->period);
   }
}

void main() {

   gpio_init(PICO_DEFAULT_LED_PIN);
   gpio_init(6);
   gpio_set_dir(PICO_DEFAULT_LED_PIN, GPIO_OUT);
   gpio_set_dir(6, GPIO_OUT);

   arg arg1, arg2;
   arg1.period = 300;
   arg1.pin = PICO_DEFAULT_LED_PIN;
   arg2.period = 1000;
   arg2.pin = 6;
   xTaskCreate(vBlinkTask, "Blink Task", 128, (void *)&arg1, 1, NULL);
   xTaskCreate(vBlinkTask, "Blink Task2", 128, (void *)&arg2, 1, NULL);


   vTaskStartScheduler();
}

