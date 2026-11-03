#include "uart.h"
#include <stdint.h>

#define CPU_ID (*(volatile uint32_t *)0xE000ED00u)

#define DEMCR (*(volatile uint32_t *)0xE000EDFC)
#define DEMCR_TRCENA (1u << 24)

#define DWT_CTRL (*(volatile uint32_t *)0xE0001000)
#define DWT_CYCCNT (*(volatile uint32_t *)0xE0001004)

#define DWT_CTRL_CYCCNTENA (1u << 0)
#define DWT_NOCYCCNT (1u << 25)

#define ROM_BASE 0xE00FF000u
#define ROM_SCS (*(volatile uint32_t *)(ROM_BASE + 0x000u))
#define ROM_DWT (*(volatile uint32_t *)(ROM_BASE + 0x004u))

typedef enum { OK, EMULATOR, INCONCLUSIVE } result_t;

result_t check_rom_table(void) {
  // ROM_SCS should always be present according to reference
  // and it's value should be exactly 0xFFF0F003
  uint32_t rom = ROM_SCS;

  uart_puts("\nrom_scs: ");
  uart_puthex(rom);
  
  if (rom != 0xFFF0F003) {
    return EMULATOR;
  }

  return OK;
}

result_t check_dwt(void) {
  DEMCR |= DEMCR_TRCENA;

  if (DWT_CTRL & DWT_NOCYCCNT) {
    return INCONCLUSIVE;
  } else {
    DWT_CTRL |= DWT_CTRL_CYCCNTENA;
    uart_puts("\ndwt_ctrl: ");
    uart_puthex(DWT_CTRL);

    if (DWT_CTRL == 0) {
      return INCONCLUSIVE;
    }

    uint32_t start = DWT_CYCCNT;
    uart_puts("\nstart-cyccnt: ");
    uart_puthex(start);

    for (volatile int i = 0; i < 5000; i++) {
    }

    uint32_t end = DWT_CYCCNT;
    uart_puts("\nend-cyccnt: ");
    uart_puthex(end);

    uint32_t diff = end - start;
    uart_puts("\ndiff-cyccnt: ");
    uart_puthex(diff);

    if (diff == 0) {
      return EMULATOR;
    }

    return OK;
  }
}

int main(void) {
  uart_init();

  uart_puts("\ncpu-id: ");
  uart_puthex(CPU_ID);

  uart_puts("\nchecking rom table\n");

  if (check_rom_table() == EMULATOR) {
    uart_puts("emulator detected.\n");
  } else {
    uart_puts("seems real silicon\n");
  }

  uart_puts("\nchecking through dwt\n");

  result_t res = check_dwt();

  if (res == INCONCLUSIVE) {
    uart_puts("unable to check.\n");
  } else if (res == EMULATOR) {
    uart_puts("emulator detected.\n");
  } else {
    uart_puts("seems real silicon\n");
  }

  while (1) {
    // loop here
  }
}
