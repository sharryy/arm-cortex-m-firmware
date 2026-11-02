#include "uart.h"

int main(void) {
  uart_init();

  uart_puts("hello from bare-metal\n");

  while (1) {
    // loop here
  }
}
