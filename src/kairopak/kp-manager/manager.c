#include "../../kernel/common.h" 
#include "../kp-link/link.h"     
#include "manager.h"

#define ID_MANAGER  "PBP0_0"

// Saját belső másoló, hogy ne kelljen string.h vagy lib.c módosítás
// Ne fix hosszat adj meg (pl. 8), hanem a célméretet!
void local_copy(char* dest, const char* src, int n) {
    int i;
    for (i = 0; i < n && src[i] != '\0'; i++) {
        dest[i] = src[i];
    }
    for (; i < n; i++) dest[i] = '\0'; // Biztonságos lezárás
}


void start_kp_system() {
    static kp_msg_t boot_msg; // Static = nem a vermet terheli
    boot_msg.region = 1;
    boot_msg.state = 4;
    local_copy(boot_msg.from, ID_MANAGER, 8);
    local_copy(boot_msg.to, ID_RECORDER, 8);
    local_copy(boot_msg.content, "System core services starting up", 127);
    
    kp_link_post(&boot_msg);
}

void kp_manager_main() {
    print("[MANAGER] Initializing Kairopak...\n");
    start_kp_system();
    
    print("[MANAGER] Boot message sent via kp-link.\n");

    int b = 0;
    while(1) {
        print("");
    }
}