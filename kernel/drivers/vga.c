#include "common.h"

#define VGA_WIDTH 80
#define VGA_HEIGHT 25
#define VGA_ADDRESS 0xB8000

static int cursor_x = 0;
static int cursor_y = 0;

// Kurzort a hardver szintjén mozgatja
void update_cursor() {
    unsigned short pos = cursor_y * VGA_WIDTH + cursor_x;
    // Port regiszterek kezelése (0x3D4 és 0x3D5 a VGA vezérlőhöz)
    outb(0x3D4, 0x0F);
    outb(0x3D5, (unsigned char)(pos & 0xFF));
    outb(0x3D4, 0x0E);
    outb(0x3D5, (unsigned char)((pos >> 8) & 0xFF));
}

void scroll() {
    unsigned short* video_memory = (unsigned short*)VGA_ADDRESS;
    if (cursor_y >= VGA_HEIGHT) {
        // Sorok feltolása eggyel
        for (int i = 0; i < (VGA_HEIGHT - 1) * VGA_WIDTH; i++) {
            video_memory[i] = video_memory[i + VGA_WIDTH];
        }
        // Az utolsó sor kitakarítása
        for (int i = (VGA_HEIGHT - 1) * VGA_WIDTH; i < VGA_HEIGHT * VGA_WIDTH; i++) {
            video_memory[i] = (unsigned short)' ' | (0x0F << 8);
        }
        cursor_y = VGA_HEIGHT - 1;
    }
}

void print(const char* str) {
    unsigned short* video_memory = (unsigned short*)VGA_ADDRESS;
    
    for (int i = 0; str[i] != '\0'; i++) {
        if (str[i] == '\n') {
            cursor_x = 0;
            cursor_y++;
        } 
        else if (str[i] == '\b') {
            // Vizuális Backspace logika
            if (cursor_x > 0) {
                cursor_x--;
            } else if (cursor_y > 0) {
                // Ha a sor elején vagyunk, visszalépünk az előző sor végére
                cursor_y--;
                cursor_x = VGA_WIDTH - 1;
            }
            // Karakter törlése: szóköz beírása a kurzor helyére
            video_memory[cursor_y * VGA_WIDTH + cursor_x] = (unsigned short)' ' | (0x0F << 8);
        } 
        else {
            video_memory[cursor_y * VGA_WIDTH + cursor_x] = (unsigned short)str[i] | (0x0F << 8);
            cursor_x++;
        }

        // Sorvég figyelése
        if (cursor_x >= VGA_WIDTH) {
            cursor_x = 0;
            cursor_y++;
        }
        scroll();
    }
    update_cursor();
}

void clear_screen() {
    unsigned short* video_memory = (unsigned short*)VGA_ADDRESS;
    for (int i = 0; i < VGA_WIDTH * VGA_HEIGHT; i++) {
        video_memory[i] = (unsigned short)' ' | (0x0F << 8);
    }
    cursor_x = 0;
    cursor_y = 0;
    update_cursor();
}


// Funkció a háttérszín megváltoztatásához (piros háttér = 0x4F)
void clear_screen_color(unsigned char color_code) {
    unsigned short* video_memory = (unsigned short*)VGA_ADDRESS;
    for (int i = 0; i < VGA_WIDTH * VGA_HEIGHT; i++) {
        video_memory[i] = (unsigned short)' ' | (color_code << 8);
    }
    cursor_x = 0;
    cursor_y = 0;
    update_cursor();
}

void kernel_panic(const char* message) {
    // 0x4F: Piros háttér (4), Fehér villogás nélküli szöveg (F)
    clear_screen_color(0x4F); 

    print("\n");
    print("  !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!  \n");
    print("  !!                                                                      !!  \n");
    print("  !!   _  _   _   _ _   _  _    ___   _   _  _   _    ___  _   _  _  ___  !!  \n");
    print("  !!  | |/ / / \\ | | | | |/ /  | _ \\ / \\ | \\| | | |  | _ \\| \\_/ || |/ __| !!  \n");
    print("  !!  | ' < | o || _ | | ' <   |  _/| o || \\  | |_|  |  _/| | | || | (__  !!  \n");
    print("  !!  |_|\\_\\|_n_||_| |_|_|\\_\\  |_|  |_n_||_|\\_| (_)  |_|  |_| |_||_|\\___| !!  \n");
    print("  !!                                                                      !!  \n");
    print("  !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!  \n");
    
    print("\n  A fatal error has occurred and KairOS has been halted to prevent damage.\n");
    print("  --------------------------------------------------------------------------\n");
    
    print("  KERNEL NAME:    "); print(KERNEL_NAME);    print("\n");
    print("  VERSION:    "); print(KERNEL_VERSION); print("\n");
    print("  ERROR MSG:  "); print(message);        print("\n");
    
    print("  --------------------------------------------------------------------------\n");
    print("  TECHNICAL INFORMATION:\n\n");
    print("  * Instruction Pointer (EIP) and Registers: [DUMPED TO SERIAL]\n");
    print("  * System state: ATOMIC_CRITICAL_SECTION\n");
    print("  * Scheduler: SUSPENDED\n\n");
    
    print("  Please manually power off or restart your hardware.\n");
    print("  The system is now in an infinite loop. Contact domesco for support.\n");


    asm volatile("cli"); 
    for(;;) {
        asm volatile("hlt");
    }
}
