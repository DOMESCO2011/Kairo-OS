#ifndef SHELL_H
#define SHELL_H

typedef struct {
    const char* name;
    const char* help;
    void (*handler)(const char* full_buf);
} command_t;

void run_shell(unsigned char scancode);
void execute_command();

#endif

