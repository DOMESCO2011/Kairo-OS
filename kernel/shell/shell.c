#include "common.h"
#include "shell.h"

#define MAX_BUFFER_SIZE 128
static char shell_buffer[MAX_BUFFER_SIZE];
static int buffer_index = 0;

extern void clear_screen(); // Ez a vga.c-ben van


void command_clear(const char* args) {
    clear_screen();
}


// Extern deklarációk (Hogy a shell lássa a többi fájlt)
extern void command_cpu(const char* args);
extern void command_info(const char* args);
extern void command_uptime(const char* args);
extern void command_reboot(const char* args);
extern void command_shutdown(const char* args);
extern void command_version(const char* args);
extern void command_stats_placeholder(const char* args);
extern void command_stackdump(const char* args);
extern void command_in(const char* args);
extern void command_out(const char* args);
extern void command_hlt(const char* args);
extern void command_nop(const char* args);
extern void command_echo(const char* args);
extern void command_test(const char* args);

command_t commands[] = {
    {"cpu",      "CPU info",          command_cpu},
    {"info",     "System info",       command_info},
    {"uptime",   "System uptime",     command_uptime},
    {"reboot",   "Reboot system",     command_reboot},
    {"shutdown", "Shutdown system",   command_shutdown},
    {"version",  "Kernel version",    command_version},
    {"tasks",    "Task list",         command_stats_placeholder},
    {"stackdump","Dump stack",        command_stackdump},
    {"in",       "Read port",         command_in},
    {"out",      "Write port",        command_out},
    {"hlt",      "Halt CPU",          command_hlt},
    {"nop",      "No operation",      command_nop},
    {"echo",     "Print text",        command_echo},
    {"test",     "Run tests",         command_test},
    {"clear",    "Clear screen",      command_clear} // VGA driverben van
};

int num_commands = sizeof(commands) / sizeof(command_t);
void reset_buffer() {
    for (int i = 0; i < MAX_BUFFER_SIZE; i++) shell_buffer[i] = 0;
    buffer_index = 0;
}

void execute_command() {
    print("\n");
    shell_buffer[buffer_index] = '\0';

    if (strcmp(shell_buffer, "help") == 0) {
        print("KairOS v0.4 - Available Commands:\n");
        for (int i = 0; i < num_commands; i++) {
            print(commands[i].name); print(" - "); print(commands[i].help); print("\n");
        }
    } 
    else {
        int found = 0;
        for (int i = 0; i < num_commands; i++) {
            int name_len = strlen(commands[i].name);
            // Itt használjuk a lib.c-ben lévő strncmp-t
            if (strncmp(shell_buffer, commands[i].name, name_len) == 0 && 
               (shell_buffer[name_len] == ' ' || shell_buffer[name_len] == '\0')) {
                commands[i].handler(shell_buffer);
                found = 1;
                break;
            }
        }
        if (!found && buffer_index > 0) {
            print("Unknown command: "); print(shell_buffer);
        }
    }

    print("\nKairOS> ");
    reset_buffer();
}

// ... run_shell függvény ...
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




