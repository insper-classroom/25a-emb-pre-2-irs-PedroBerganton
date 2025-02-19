#include "hardware/gpio.h"
#include "pico/stdlib.h"
#include <stdio.h>

const int BTN_PIN_R = 28;
const int BTN_PIN_G = 26;

const int LED_R = 4;
const int LED_G = 6;

volatile int FLAG_BOTAO_R = 0;
volatile int FLAG_BOTAO_G = 0;

void btn_callback(uint gpio, uint32_t events) {

  printf("entrou em callback");
  if (events == 0x4) {                                  // fall, botao apertado
    printf("entrou em fall");
    if (gpio == BTN_PIN_R){
      FLAG_BOTAO_R = 1;
    }
  }
  else if (events == 0x8){
    printf("entrou rise");
    if (gpio == BTN_PIN_G){
      FLAG_BOTAO_G = 1;
  }
}
}


int main() {
  stdio_init_all();

  // Botoes
  gpio_init(BTN_PIN_R);
  gpio_set_dir(BTN_PIN_R, GPIO_IN);
  gpio_pull_up(BTN_PIN_R);

  gpio_init(BTN_PIN_G);
  gpio_set_dir(BTN_PIN_G, GPIO_IN);
  gpio_pull_up(BTN_PIN_G);

  // LEDs
  gpio_init(LED_R);
  gpio_set_dir(LED_R, GPIO_OUT);

  gpio_init(LED_G);
  gpio_set_dir(LED_G, GPIO_OUT);

  // callback led r (first)
  gpio_set_irq_enabled_with_callback(BTN_PIN_R, GPIO_IRQ_EDGE_FALL, true, &btn_callback);

  // callback led g (nao usar _with_callback)
  gpio_set_irq_enabled_with_callback(BTN_PIN_G, GPIO_IRQ_EDGE_RISE, true, &btn_callback);

  int sinal = 0;
  int sinal1 = 0;
  
  while (true) {
    if (FLAG_BOTAO_R == 1){ //se botao estiver acionado
      FLAG_BOTAO_R = 0;
      sinal = 1 - sinal;
      gpio_put(LED_R, sinal);
    } 
    else if(FLAG_BOTAO_G == 1){
      FLAG_BOTAO_G = 0;
      sinal1 = 1 - sinal1;
      gpio_put(LED_G, sinal1);
    }
  }
}



