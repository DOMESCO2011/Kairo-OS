#include "common.h"

struct idt_entry {
    unsigned short base_lo;
    unsigned short sel;        // Kernel Code Segment (0x08)
    unsigned char  always0;
    unsigned char  flags;      // 0x8E = Interrupt Gate
    unsigned short base_hi;
} __attribute__((packed));

struct idt_ptr {
    unsigned short limit;
    unsigned int base;
} __attribute__((packed));

struct idt_entry idt[256];
struct idt_ptr idtp;

// Külső assembly függvények
extern void idt_load(unsigned int);
extern void isr0();

void divide_by_zero_handler() {
    kernel_panic("EXCEPTION 0x00: Division by Zero");
}

void idt_set_gate(unsigned char num, unsigned long base, unsigned short sel, unsigned char flags) {
    idt[num].base_lo = (base & 0xFFFF);
    idt[num].base_hi = (base >> 16) & 0xFFFF;
    idt[num].sel = sel;
    idt[num].always0 = 0;
    idt[num].flags = flags;
}

void idt_install() {
    idtp.limit = (sizeof(struct idt_entry) * 256) - 1;
    idtp.base = (unsigned int)&idt;

    // Tábla alaphelyzetbe állítása
    for(int i = 0; i < 256; i++) idt_set_gate(i, 0, 0, 0);

    // 0-s megszakítás (Division by Zero) regisztrálása
    idt_set_gate(0, (unsigned long)isr0, 0x08, 0x8E);

    // Átadjuk a processzornak
    idt_load((unsigned int)&idtp);
}
