#include "hardware/gpio.h"
#include "pico/stdlib.h"
#include <stdio.h>

const int BTN_PIN_R = 28;

volatile int FLAG = 0;
volatile int EVENTS1 = 0;

void btn_callback(uint gpio, uint32_t events) {
  FLAG = 1;                                                  // mostra que evento aconteceuu
  EVENTS1 = events;                                          // adiciona um valor a variavel compativel a fall ou rise

  // if (events == 0x4) { // fall edge
  //   printf("fall \n");
  // } else if (events == 0x8) { // rise edge
  //   printf("rise \n");
  // }
}

int main() {
  stdio_init_all();

  gpio_init(BTN_PIN_R);
  gpio_set_dir(BTN_PIN_R, GPIO_IN);
  gpio_pull_up(BTN_PIN_R);

  gpio_set_irq_enabled_with_callback(
      BTN_PIN_R, GPIO_IRQ_EDGE_RISE | GPIO_IRQ_EDGE_FALL, true, &btn_callback);  //chama a funcao quando estiver em rise ou fall

  while (true) {
    if (FLAG != 0){
      FLAG = 0;                                                  // volta a flag para o padrao zero

      if (EVENTS1 == 0x4) { // fall edge - isso e quando o sinal cai de 1 para 0
        printf("fall \n");
      } else if (EVENTS1 == 0x8) { // rise edge - aqui e quando o sinal sobe de 0 para 1
        printf("rise \n");
  }
    }
  }
}
