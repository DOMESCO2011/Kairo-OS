// src/kairopak/kp-recorder/recorder.c
#include "recorder.h"
#include "../kp-link/link.h"
#include "../kp-manager/manager.h" // Itt van az ID_RECORDER!
#include "../../kernel/common.h"   // strcmp, print

// A save_to_binary_storage-nek a hívás ELŐTT kell lennie
void save_to_binary_storage(kp_msg_t msg) {
    print("[RECORDER] Data stored: ");
    print(msg.content);
    print("\n");
}

void process_incoming_logs() {
    static kp_msg_t current_msg;
    if (kp_link_fetch(&current_msg)) {
        if (strcmp(current_msg.to, ID_RECORDER) == 0 || strcmp(current_msg.to, "*") == 0) {
            save_to_binary_storage(current_msg);
        }
    }
}