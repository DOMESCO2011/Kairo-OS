#ifndef COMMON_H
#define COMMON_H

// VGA
void print(const char* str);
void clear_screen();

// Keyboard & I/O
unsigned char inb(unsigned short port);
void outb(unsigned short port, unsigned char val);
unsigned char get_scancode();
unsigned char get_ascii(unsigned char scancode);
void kernel_panic(const char* message);
// Shell & Utils
void run_shell(unsigned char scancode);
void reset_buffer();
int strcmp(const char* s1, const char* s2);
void get_cpu_vendor();
void itoa(int n, char s[]);

// GDT
void gdt_install();

//IDT
void idt_install();
void pic_remap();
#endif


//info
#define KERNEL_VERSION "0.0.1"
#define KERNEL_NAME "Thank_you_Gary"