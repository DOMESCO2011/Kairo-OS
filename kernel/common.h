#ifndef COMMON_H
#define COMMON_H

/* --- OS Információk --- */
#define KERNEL_VERSION "0.0.3"
#define KERNEL_NAME "Thank You Gary"

/* --- VGA / Megjelenítés --- */
void print(const char* str);
void clear_screen();
void clear_screen_color(unsigned char color_code);
void kernel_panic(const char* message);

/* --- Alapvető I/O (kernel/lib.c) --- */
unsigned char inb(unsigned short port);
void outb(unsigned short port, unsigned char val);
void outw(unsigned short port, unsigned short val);
/* --- Utility / Library (kernel/lib.c) --- */
int strcmp(const char* s1, const char* s2);
int strlen(const char* str);
void itoa(int n, char s[]);
void get_cpu_vendor();

/* --- Billentyűzet (drivers/keyboard.c) --- */
unsigned char get_scancode();
unsigned char get_ascii(unsigned char scancode);

/* --- Shell (shell/shell.c) --- */
void run_shell(unsigned char scancode);

/* --- Rendszer / Deskriptor táblák --- */
void gdt_install();
void idt_install();
void pic_remap();





int strncmp(const char* s1, const char* s2, int n);

#endif