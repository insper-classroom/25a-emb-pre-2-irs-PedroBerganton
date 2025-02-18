#include "hardware/gpio.h"
#include "pico/stdlib.h"
#include <stdio.h>

const int BTN_PIN_R = 28;
const int LED = 4;

volatile int FLAG_BOTAO = 0;

void btn_callback(uint gpio, uint32_t events) {
  if (events == 0x4) {         // se for um FALL, botao deve ser 1
    FLAG_BOTAO = 1;}
    else if (events == 0x8){  // se for um RISE, botao deve ser 0
    FLAG_BOTAO = 0;
}
}

int main() {
  stdio_init_all();

  gpio_init(BTN_PIN_R);
  gpio_set_dir(BTN_PIN_R, GPIO_IN);
  gpio_pull_up(BTN_PIN_R);

  gpio_init(LED);
  gpio_set_dir(LED, GPIO_OUT);


  gpio_set_irq_enabled_with_callback(BTN_PIN_R, GPIO_IRQ_EDGE_RISE | GPIO_IRQ_EDGE_FALL, true, &btn_callback);

  int sinal = 0;
  while (true) {
    if (FLAG_BOTAO == 0){ //se botao estiver acionado
      sinal = 1 - sinal;
      gpio_set_dir(LED, (sinal));
    }
  }
}
