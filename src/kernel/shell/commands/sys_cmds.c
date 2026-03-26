#include "common.h"

void command_info(const char* args) {
    print("\n--- KairOS System Info ---\n");
    print("Kernel: "); print(KERNEL_NAME); print("\n");
    print("Version: "); print(KERNEL_VERSION); print("\n");
    print("Build: " __DATE__ " " __TIME__ "\n");
    print("Status: Operational / Ring 0\n");
}

void command_uptime(const char* args) {
    print("Uptime: Feature requires PIT timer initialization.\n");
}

void command_reboot(const char* args) {
    print("Rebooting via PS/2 Controller...\n");
    outb(0x64, 0xFE);
}

void command_shutdown(const char* args) {
    print("Shutting down...\n");
    outw(0x604, 0x2000);   // QEMU - outb helyett outw!
    outw(0x4004, 0x3400);  // VirtualBox - outb helyett outw!

}

void command_version(const char* args) {
    print("KairOS Version: "); print(KERNEL_VERSION); print("\n");
}

void command_stats_placeholder(const char* args) {
    print("Statistics: Scheduler/Memory Manager not yet reporting.\n");
}