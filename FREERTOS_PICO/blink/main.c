#include "pico/stdlib.h"
#include "FreeRTOS.h"
#include "task.h"

void vBlinkTask(uint8_t pin, uint16_t period) {
   for (;;) {
      gpio_put(pin, 1);
      vTaskDelay(period);
      gpio_put(pin, 0);
      vTaskDelay(period);
   }
}

void main() {

   gpio_init(PICO_DEFAULT_LED_PIN);
   gpio_set_dir(PICO_DEFAULT_LED_PIN, GPIO_OUT);
   gpio_set_dir(4, GPIO_OUT);
   typedef struct struct_arg_t {
        uint8_t pin;
        uint16_t period;
   } arg;
   arg arg1, arg2;
   arg1.period = 100;
   arg1.pin = PICO_DEFAULT_LED_PIN;
   arg2.period = 300;
   arg2.pin = 4;
   xTaskCreate(vBlinkTask, "Blink Task", 128, (void*)&arg1, 1, NULL);
   xTaskCreate(vBlinkTask, "Blink Task2", 128, (void*)&arg2, 1, NULL);


   vTaskStartScheduler();
}

