#include "uart.h"
#include <stdint.h>

#define CPU_ID (*(volatile uint32_t *)0xE000ED00u)

int main(void) {
  uart_init();

  uart_puts("Hello, World\n");
  uart_puthex(0x412FC230);

  while (1) {
    // loop here
  }
}
