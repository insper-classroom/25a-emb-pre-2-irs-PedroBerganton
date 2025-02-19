#include "hardware/gpio.h"
#include "pico/stdlib.h"
#include <stdio.h>

const int BTN_PIN_R = 28;
const int BTN_PIN_G = 26;

void btn_callback(uint gpio, uint32_t events) {
  if (events == 0x4) {                                  // botao foi pressionado
    // if (gpio == BTN_PIN_R)
    // //   FLAG_BOTAO_R = 0;
    //   // printf("fall red\n");
    // else if (gpio == BTN_PIN_G)
    // //   FLAG_BOTAO_G = 0;
    //   // printf("fall green\n");
  }
}

int main() {
  stdio_init_all();

  gpio_init(BTN_PIN_R);
  gpio_set_dir(BTN_PIN_R, GPIO_IN);
  gpio_pull_up(BTN_PIN_R);

  gpio_init(BTN_PIN_G);
  gpio_set_dir(BTN_PIN_G, GPIO_IN);
  gpio_pull_up(BTN_PIN_G);

  
  while (true) {
  }
}
