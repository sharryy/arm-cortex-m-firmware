ENTRY(Reset_Handler)

MEMORY
{
    flash (rx) : ORIGIN = 0x00000000,    LENGTH = 4M /* ZBT_SSRAM1 for flash storage */
    ram   (wx) : ORIGIN = 0x20000000,    LENGTH = 4M /* ZBT_SSRAM2&3 for RAM */
}

SECTIONS
{
    .text : {
        KEEP(*(.vectors))
        *(.text*)
        *(.rodata*)
        . = ALIGN(4);
        _etext = .;
    } > flash

    .data : {
        . = ALIGN(4);
        _sdata = .;
        *(.data*)
        . = ALIGN(4);
        _edata = .;
    } > ram AT> flash

    _sidata = LOADADDR(.data);

    .bss : {
        . = ALIGN(4);
        _sbss = .;
        *(.bss*)
        *(COMMON)
        . = ALIGN(4);
        _ebss = .;
    } > ram

    _estack = ORIGIN(ram) + LENGTH(ram);
}
