CC      = arm-none-eabi-gcc
CFLAGS  = -mcpu=cortex-m3 -mthumb -O0 -g -Wall -Wextra -ffreestanding
LDFLAGS = -nostdlib -T linker.ld -Wl,-Map=firmware.map

SRCS = startup.c uart.c main.c

all: firmware.elf

firmware.elf: $(SRCS) linker.ld uart.h
	$(CC) $(CFLAGS) $(SRCS) $(LDFLAGS) -o $@

run: firmware.elf
	qemu-system-arm -M mps2-an385 -nographic -kernel firmware.elf -d unimp,guest_errors

clean:
	rm -f firmware.elf firmware.map
