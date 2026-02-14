#include "common.h"

void command_cpu(const char* args) {
    unsigned int eax, ebx, ecx, edx;
    static char vendor[13];
    static char brand[49];

    // 1. Vendor lekérése (EAX=0)
    asm volatile("cpuid" : "=a"(eax), "=b"(ebx), "=c"(ecx), "=d"(edx) : "a"(0));
    *((unsigned int*)&vendor[0]) = ebx;
    *((unsigned int*)&vendor[4]) = edx;
    *((unsigned int*)&vendor[8]) = ecx;
    vendor[12] = '\0';

    // 2. Brand String lekérése (EAX=0x80000002, 0x80000003, 0x80000004)
    // Megnézzük, támogatja-e a CPU a Brand stringet
    asm volatile("cpuid" : "=a"(eax) : "a"(0x80000000));
    if (eax >= 0x80000004) {
        unsigned int *brand_ptr = (unsigned int*)brand;
        for (unsigned int i = 0; i < 3; i++) {
            asm volatile("cpuid" 
                         : "=a"(brand_ptr[i*4 + 0]), "=b"(brand_ptr[i*4 + 1]), 
                           "=c"(brand_ptr[i*4 + 2]), "=d"(brand_ptr[i*4 + 3]) 
                         : "a"(0x80000002 + i));
        }
        brand[48] = '\0';
    } else {
        brand[0] = '\0'; // Ha nem támogatja, üres marad
    }

    // 3. Magok száma (EAX=1 -> EBX bits 16-23)
    asm volatile("cpuid" : "=a"(eax), "=b"(ebx), "=c"(ecx), "=d"(edx) : "a"(1));
    int cores = (ebx >> 16) & 0xFF;
    char core_buf[4];
    itoa(cores, core_buf);

    // 4. KIÍRÁS (Egyetlen blokkban, hogy ne legyen Triple Fault a sok hívástól)
    print("\nCPU: ");
    print(vendor);
    if (brand[0] != '\0') {
        print(" (");
        print(brand);
        print(")");
    }
    print("\nLogical Cores: ");
    print(core_buf);
    print("\n");
}