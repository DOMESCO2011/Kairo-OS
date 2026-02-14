#include "common.h"

// Felhasználói infó
void command_whoami() {
    print("Current user: root\n");
    print("Privileges: ring 0 (Kernel Mode)\n");
}

// Idő (egyelőre egy egyszerűbb verzió, hogy ne legyen hiba)
void command_time() {
    print("RTC Time: Feature coming soon (needs CMOS driver)\n");
}