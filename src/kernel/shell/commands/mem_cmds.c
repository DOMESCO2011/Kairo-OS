#include "common.h"

void command_stackdump(const char* args) {
    print("Stack Dump (Current Frame):\n");
    unsigned int *esp;
    asm volatile("mov %%esp, %0" : "=r"(esp));
    
    for(int i = 0; i < 8; i++) {
        print("0x");
        // Itt a már megírt cpu_print_hex-et használhatnád
        print(" [Frame data placeholder]\n");
    }
}

void command_mem_placeholder(const char* args) {
    print("Memory operation: Paging/Dynamic Allocator required for this command.\n");
}