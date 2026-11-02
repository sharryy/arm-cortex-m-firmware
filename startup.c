#include <stdint.h>
#include "uart.h"

extern uint32_t _estack;
extern uint32_t _sidata;
extern uint32_t _sbss;
extern uint32_t _ebss;
extern uint32_t _sdata;
extern uint32_t _edata;

int main(void);

void Reset_Handler(void) {
  uint32_t *src = &_sidata;
  uint32_t *dst = &_sdata;

  while (dst < &_edata) {
    *dst++ = *src++;
  }

  dst = &_sbss;

  while (dst < &_ebss) {
    *dst++ = 0;
  }

  main();

  while (1) {
  }
}

void Default_Handler(void) {
    uart_init();
    uart_puts("default handler fault!\n");

    while (1) {

    }
}

const uint32_t vector_table[] __attribute__((section(".vectors"), used)) = {
    (uint32_t)&_estack,             // Initial Stack Pointer
    (uint32_t)Reset_Handler,        // Reset Handler
    (uint32_t)Default_Handler,      // NMI
    (uint32_t)Default_Handler,      // Hard Fault
    (uint32_t)Default_Handler,      // MemManage
    (uint32_t)Default_Handler,      // BusFault
    (uint32_t)Default_Handler,      // UsageFault
    0,0,0,0,
    (uint32_t)Default_Handler,      // SVCall
    (uint32_t)Default_Handler,      // DebugMonitorHandler
    0,
    (uint32_t)Default_Handler,      // PendSV
    (uint32_t)Default_Handler,      // SysTick

};
