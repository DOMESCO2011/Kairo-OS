#include "common.h"           
#include "drivers/keyboard.h" 
#include "drivers/vga.h" 

// Kézi deklaráció (így nem kell a header-rel küzdeni a fordítás ezen szakaszában)
extern void kp_manager_main(void);

void enable_sse() {
    asm volatile (
        "mov %%cr0, %%eax\n"
        "and $0xFFFB, %%ax\n"
        "or $0x2, %%ax\n"
        "mov %%eax, %%cr0\n"
        "mov %%cr4, %%eax\n"
        "or $0x600, %%eax\n"
        "mov %%eax, %%cr4\n"
        : : : "eax"
    );
}
void kmain() {
    gdt_install();
    
    // 1. LÉPÉS: Hardver felkészítése
    // Ezt minél előbb meg kell tenni, mert a C fordító 
    // bármikor beilleszthet egy SSE utasítást.
    enable_sse(); 

    idt_install();
    clear_screen();
    
    print("Welcome to KairOS\n");
    print("Kernel version: ");
    print(KERNEL_VERSION);
    print("\n");

    print("[KERNEL] Handing over to kp-manager...\n");
    
    // 2. LÉPÉS: Megszakítások engedélyezése
    // Érdemes a kp_manager előtt kiadni az sti-t, 
    // hogy a manager már tudjon reagálni pl. billentyűzetre.
    __asm__ __volatile__ ("sti");

    // 3. LÉPÉS: A "nehéz" kód hívása
    // Itt történik a 0x101522 címen lévő másolás.
    kp_manager_main();

    while(1) {
        asm volatile("hlt");
    }
}