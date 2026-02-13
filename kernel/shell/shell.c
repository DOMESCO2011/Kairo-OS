#include "common.h"

#define MAX_BUFFER_SIZE 128
static char shell_buffer[MAX_BUFFER_SIZE];
static int buffer_index = 0;

// Saját string összehasonlító (kötelező, mert nincs string.h)
int strcmp(const char* s1, const char* s2) {
    while (*s1 && (*s1 == *s2)) {
        s1++;
        s2++;
    }
    return *(unsigned char*)s1 - *(unsigned char*)s2;
}

// Puffer ürítése minden parancs után
void reset_buffer() {
    for (int i = 0; i < MAX_BUFFER_SIZE; i++) shell_buffer[i] = 0;
    buffer_index = 0;
}

// CPU Vendor lekérése assembly-vel
void get_cpu_vendor() {
    unsigned int ebx, ecx, edx;
    char vendor[13];
    asm volatile("cpuid" : "=b"(ebx), "=c"(ecx), "=d"(edx) : "a"(0));
    *((unsigned int*)&vendor[0]) = ebx;
    *((unsigned int*)&vendor[4]) = edx;
    *((unsigned int*)&vendor[8]) = ecx;
    vendor[12] = '\0';
    print(vendor);
}

// Szám-szöveg átalakító
void itoa(int n, char s[]) {
    int i, sign;
    if ((sign = n) < 0) n = -n;
    i = 0;
    do {
        s[i++] = n % 10 + '0';
    } while ((n /= 10) > 0);
    if (sign < 0) s[i++] = '-';
    s[i] = '\0';
    for (int j = 0, k = i-1; j < k; j++, k--) {
        char temp = s[j];
        s[j] = s[k];
        s[k] = temp;
    }
}

// Rendszeridő CMOS-ból
void print_time() {
    char buf[16];
    outb(0x70, 0x04); unsigned char hour = inb(0x71);
    outb(0x70, 0x02); unsigned char min  = inb(0x71);
    outb(0x70, 0x00); unsigned char sec  = inb(0x71);

    hour = (hour & 0x0F) + ((hour / 16) * 10);
    min = (min & 0x0F) + ((min / 16) * 10);
    sec = (sec & 0x0F) + ((sec / 16) * 10);

    itoa(hour, buf); print(buf); print(":");
    itoa(min, buf);  print(buf); print(":");
    itoa(sec, buf);  print(buf);
}

void execute_command() {
    print("\n");

    if (strcmp(shell_buffer, "help") == 0) {
        print("KairOS v0.4 - Command List:\n");
        print("help     -- Show this manual\n");
        print("clear    -- Clear the terminal\n");
        print("cpu      -- Display CPU Vendor and features\n");
        print("mem      -- Show detected base memory\n");
        print("time     -- Display current RTC time\n");
        print("whoami   -- Display current user info\n");
        print("halt     -- Halt the system\n");
        print("reboot   -- Restart the computer\n");
        print("echo     -- Simple test command\n");
    } 
    else if (strcmp(shell_buffer, "clear") == 0) {
        clear_screen();
    }
    else if (strcmp(shell_buffer, "cpu") == 0) {
        print("CPU Vendor: ");
        get_cpu_vendor();
        print("\nFeatures: FPU, VME, DE, PSE, TSC, MSR, PAE");
    }
    else if (strcmp(shell_buffer, "time") == 0) {
        print("System Time (UTC): ");
        print_time();
    }
    else if (strcmp(shell_buffer, "whoami") == 0) {
        print("User: root\nHost: KairOS-Machine\nPrivileges: Kernel-level");
    }
    else if (strcmp(shell_buffer, "echo") == 0) {
        print("KairOS says: Hello world!");
    }
    else if (strcmp(shell_buffer, "mem") == 0) {
        print("Lower Memory: 640 KB\nUpper Memory: 30720 KB (Estimated)");
        
    }

	else if (strcmp(shell_buffer, "zerodiv") == 0) {
		print("Attempting division by zero...\n");
		int a = 5;
		int b = 0;
		int c = a / b;

	}
    else if (strcmp(shell_buffer, "halt") == 0) {
        print("System halted. Power off manually.");
        asm volatile("hlt");
    }
    else if (strcmp(shell_buffer, "panic") == 0) {
		kernel_panic("USER_TRIGGERED_PANIC: Manual system crash test.");

    }
    else if (strcmp(shell_buffer, "reboot") == 0) {
        print("Rebooting...");
        outb(0x64, 0xFE);
    }
    else if (buffer_index > 0) {
        print("Unknown command: ");
        print(shell_buffer);
    }

    print("\nKairOS> ");
    reset_buffer();
}

void run_shell(unsigned char scancode) {
    unsigned char ascii = get_ascii(scancode);
    if (ascii == 0) return;

    if (ascii == '\n') {
        shell_buffer[buffer_index] = '\0';
        execute_command();
    } 
    else if (ascii == '\b') {
        if (buffer_index > 0) {
            buffer_index--;
            shell_buffer[buffer_index] = '\0';
            print("\b");
        }
    } 
    else {
        if (buffer_index < MAX_BUFFER_SIZE - 1) {
            shell_buffer[buffer_index] = ascii;
            buffer_index++;
            char s[2] = {ascii, '\0'};
            print(s);
        }
    }
}




