#include "hardware/gpio.h"
#include "pico/stdlib.h"
#include <stdio.h>

const int BTN_PIN_R = 28;
const int BTN_PIN_G = 26;

volatile int FLAG_BOTAO_R = 0;
volatile int FLAG_BOTAO_G = 0;

void btn_callback(uint gpio, uint32_t events) {
  if (events == 0x4) {         // se for um FALL, botao foi apertado
    if (gpio == BTN_PIN_R){
      FLAG_BOTAO_R = 1;
    } else if(gpio == BTN_PIN_G){
      FLAG_BOTAO_G = 1;
    }
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

  // callback led r (first)
  gpio_set_irq_enabled_with_callback(BTN_PIN_R, GPIO_IRQ_EDGE_FALL, true, &btn_callback);

  // callback led g (nao usar _with_callback)
  gpio_set_irq_enabled_with_callback(BTN_PIN_G, GPIO_IRQ_EDGE_FALL, true, &btn_callback);

  while (true) {
    if (FLAG_BOTAO_R == 1){ //se botao estiver acionado
        FLAG_BOTAO_R = 0;
        printf("fall red\n");
    }
    if (FLAG_BOTAO_G == 1){ //se botao estiver acionado
        FLAG_BOTAO_G = 0;
        printf("fall green\n");
    }
  }

}
