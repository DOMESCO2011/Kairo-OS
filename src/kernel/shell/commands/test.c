#include "common.h"

// Segédfüggvény: megkeresi az első szóközt és visszaadja a maradék szöveget
const char* get_arg(const char* buf) {
    while (*buf != ' ' && *buf != '\0') buf++;
    if (*buf == ' ') return buf + 1;
    return ""; // Nincs argumentum
}

void command_test(const char* full_buffer) {
    const char* arg = get_arg(full_buffer);

    if (strcmp(arg, "echo") == 0) {
        print("Test: Echo system is working!\n");
    } 
    else if (strcmp(arg, "panic") == 0) {
        kernel_panic("TEST_PANIC: User triggered a crash test.");
    } 
    else if (strcmp(arg, "halt") == 0) {
        print("Test: Halting system...\n");
        asm volatile("hlt");
    }
    else {
        print("Usage: test <echo|panic|halt>\n");
    }
}