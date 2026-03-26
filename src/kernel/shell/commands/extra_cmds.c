#include "common.h"

void command_echo(const char* args) {
    // A "echo " utáni részt írjuk ki (5. karaktertől)
    if (strlen(args) > 5) {
        print(args + 5);
        print("\n");
    } else {
        print("\n");
    }
}

void command_rand(const char* args) {
    print("Random: 4 (Chosen by fair dice roll, guaranteed to be random)\n");
}