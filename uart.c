#include <stdint.h>
#include "uart.h"

#define UART0_BASE 0x40004000u

#define UART0_DATA (*(volatile uint32_t *)(UART0_BASE + 0x000))
#define UART0_STATE (*(volatile uint32_t *)(UART0_BASE + 0x004))
#define UART0_CTRL (*(volatile uint32_t *)(UART0_BASE + 0x008))
#define UART0_BAUD_DIV (*(volatile uint32_t *)(UART0_BASE + 0x010))
#define UART0_BAUD_DIV_MIN 16

#define UART0_CTRL_TX_EN (1u << 0)
#define UART0_STATE_TX_FULL (1u << 0)

void uart_init(void) {
  UART0_BAUD_DIV = UART0_BAUD_DIV_MIN;
  UART0_CTRL |= UART0_CTRL_TX_EN;
}

void uart_putc(char c) {
  while (UART0_STATE & UART0_STATE_TX_FULL) {
    // wait here
  }

  UART0_DATA = (uint8_t)c;
}

void uart_puts(const char *s) {
  while (*s != '\0') {
    uart_putc(*s++);
  }
}
