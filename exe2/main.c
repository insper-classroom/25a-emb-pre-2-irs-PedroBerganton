#include "hardware/gpio.h"
#include "pico/stdlib.h"
#include <stdio.h>

const int BTN_PIN_R = 28;

volatile int inverso = 0;

int main() {
  stdio_init_all();

  gpio_init(BTN_PIN_R);
  gpio_set_dir(BTN_PIN_R, 0);
  gpio_pull_up(BTN_PIN_R);

  while (true) {
    if (gpio_get(BTN_PIN_R) == 0){
      gpio_set_dir(BTN_PIN_R, (1-inverso));
    }
  }
}
