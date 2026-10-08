ENTRY (_start)

SECTIONS
{
    . = 0x0;

    .text : {
        *(.text*)
    }

    .rodata : {
        *(.rodata*)
    }

    .data : {
        *(.data*)
        *(COMMON)
    }

    . = ALIGN(16);
    .stack : {
        __stack_bottom = .;
        . += 0x4000;
        __stack_top = .;
    }
}
