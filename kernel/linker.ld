/* Meghatározzuk a belépési pontot */
ENTRY(_start)

SECTIONS
{
    /* 1MB-nál kezdünk */
    . = 0x100000;

    /* A kód szekció, multiboot fejléccel az elején */
    .text BLOCK(4K) : ALIGN(4K)
    {
        *(.multiboot)
        *(.text)
    }

    /* Csak olvasható adatok (pl. az ASCII logód és stringek) */
    .rodata BLOCK(4K) : ALIGN(4K)
    {
        *(.rodata)
    }

    /* Inicializált adatok */
    .data BLOCK(4K) : ALIGN(4K)
    {
        *(.data)
    }

    /* BSS szekció (inicializálatlan adatok, ide kerül az IDT is) */
    .bss BLOCK(4K) : ALIGN(4K)
    {
        *(COMMON)
        *(.bss)
    }
}
