#include "common.h"

void command_in(const char* args) {
    print("Usage: in <port_hex>\n");
    // Parsolás után: unsigned char val = inb(port);
}

void command_out(const char* args) {
    print("Usage: out <port_hex> <val_hex>\n");
}

void command_hlt(const char* args) {
    print("System Halted. Press any key (IRQ) to wake.\n");
    asm volatile("hlt");
}

void command_nop(const char* args) {
    asm volatile("nop");
    print("Executed NOP.\n");
}