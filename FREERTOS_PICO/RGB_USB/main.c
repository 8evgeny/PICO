#include "pico/stdlib.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#define CFG_TUSB_MCU OPT_MCU_RP2040
#include "bsp/board.h"
#include "tusb.h"
const uint GREEN_PIN = 15;
//------------- prototypes -------------//
static void cdc_task(void);

/*------------- MAIN -------------*/
int main(void)
{
  board_init();
  gpio_init(GREEN_PIN);
  gpio_set_dir(GREEN_PIN, GPIO_OUT);
  // init device stack on configured roothub port
  tud_init(BOARD_TUD_RHPORT);

  while (1)
  {
    tud_task(); // tinyusb device task
    cdc_task();
  }

  return 0;
}

// echo to either Serial0 or Serial1
// with Serial0 as all lower case, Serial1 as all upper case
static void echo_serial_port(uint8_t itf, uint8_t buf[], uint32_t count)
{
  uint8_t const case_diff = 'a' - 'A';

  for(uint32_t i=0; i<count; i++)
  {
    if (itf == 0)
    {
      // echo back 1st port as lower case
      if (isupper(buf[i])) buf[i] += case_diff;
    }
    else
    {
      // echo back 2nd port as upper case
      if (islower(buf[i])) buf[i] -= case_diff;
    }

    tud_cdc_n_write_char(itf, buf[i]);
  }
  tud_cdc_n_write_flush(itf);
}

//--------------------------------------------------------------------+
// USB CDC
//--------------------------------------------------------------------+
static void cdc_task(void)
{
  uint8_t itf;

  for (itf = 0; itf < CFG_TUD_CDC; itf++)
  {
    // connected() check for DTR bit
    // Most but not all terminal client set this when making connection
    // if ( tud_cdc_n_connected(itf) )
    {
      if ( tud_cdc_n_available(itf) )
      {
        uint8_t buf[64];

        uint32_t count = tud_cdc_n_read(itf, buf, sizeof(buf));
        if (buf[0] == 'o' && buf[1] == 'n')
        {
            gpio_put(PICO_DEFAULT_LED_PIN, 1);
            gpio_put(GREEN_PIN, 1);
        }
        else if (buf[0] == 'o' && buf[1] == 'f' && buf[2] == 'f')
        {
            gpio_put(PICO_DEFAULT_LED_PIN, 0);
            gpio_put(GREEN_PIN, 0);
        }
        else if (buf[0] == '1')
        {
            gpio_put(PICO_DEFAULT_LED_PIN, 1);
            gpio_put(GREEN_PIN, 1);
            sleep_us(100);
            gpio_put(PICO_DEFAULT_LED_PIN, 0);
            gpio_put(GREEN_PIN, 0);
        }
        else if (buf[0] == '2')
        {
            gpio_put(PICO_DEFAULT_LED_PIN, 1);
            gpio_put(GREEN_PIN, 1);
            sleep_us(200);
            gpio_put(PICO_DEFAULT_LED_PIN, 0);
            gpio_put(GREEN_PIN, 0);
        }
        else if (buf[0] == '3')
        {
            gpio_put(PICO_DEFAULT_LED_PIN, 1);
            gpio_put(GREEN_PIN, 1);
            sleep_us(300);
            gpio_put(PICO_DEFAULT_LED_PIN, 0);
            gpio_put(GREEN_PIN, 0);
        }
        else if (buf[0] == '4')
        {
            gpio_put(PICO_DEFAULT_LED_PIN, 1);
            gpio_put(GREEN_PIN, 1);
            sleep_us(400);
            gpio_put(PICO_DEFAULT_LED_PIN, 0);
            gpio_put(GREEN_PIN, 0);
        }
        else if (buf[0] == '5')
        {
            gpio_put(PICO_DEFAULT_LED_PIN, 1);
            gpio_put(GREEN_PIN, 1);
            sleep_us(500);
            gpio_put(PICO_DEFAULT_LED_PIN, 0);
            gpio_put(GREEN_PIN, 0);
        }
        else if (buf[0] == '6')
        {
            gpio_put(PICO_DEFAULT_LED_PIN, 1);
            gpio_put(GREEN_PIN, 1);
            sleep_us(600);
            gpio_put(PICO_DEFAULT_LED_PIN, 0);
            gpio_put(GREEN_PIN, 0);
        }
        else if (buf[0] == '7')
        {
            gpio_put(PICO_DEFAULT_LED_PIN, 1);
            gpio_put(GREEN_PIN, 1);
            sleep_us(700);
            gpio_put(PICO_DEFAULT_LED_PIN, 0);
            gpio_put(GREEN_PIN, 0);
        }
        else if (buf[0] == '8')
        {
            gpio_put(PICO_DEFAULT_LED_PIN, 1);
            gpio_put(GREEN_PIN, 1);
            sleep_us(800);
            gpio_put(PICO_DEFAULT_LED_PIN, 0);
            gpio_put(GREEN_PIN, 0);
        }
        else if (buf[0] == '9')
        {
            gpio_put(PICO_DEFAULT_LED_PIN, 1);
            gpio_put(GREEN_PIN, 1);
            sleep_us(900);
            gpio_put(PICO_DEFAULT_LED_PIN, 0);
            gpio_put(GREEN_PIN, 0);
        }
        // echo back to both serial ports
//        echo_serial_port(0, buf, count);
//        echo_serial_port(1, buf, count);
      }
    }
  }
}
