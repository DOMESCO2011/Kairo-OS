#include "common.h"           
#include "drivers/keyboard.h" 
#include "drivers/vga.h" 






void gdt_install(); 
void kmain() {
    gdt_install();
    idt_install();
    clear_screen();
    print("Welcome to KairOS\n");
    print("Kernel version: ");
    print(KERNEL_VERSION);
    print("\n");
    print("main> ");

    while(1) {
        unsigned char scancode = get_scancode();
        if (scancode > 0) {
            run_shell(scancode);
        }
    }
}
