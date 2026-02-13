#include "vga.h"
#include "keyboard.h"
#include "shell.h"
#include "common.h"
void gdt_install(); 

void kmain() {
    gdt_install();
    idt_install();
    clear_screen();
    print("Welcome to KairOS (x86 Bare Metal Edition)\n");
    print("Copyright (c) 2026. All rights reserved.\n");
    print("Type 'help' to see available commands.\n\n");
    print("KairOS> ");

    while(1) {
        unsigned char scancode = get_scancode();
        if (scancode > 0) {
            run_shell(scancode);
        }
    }
}
