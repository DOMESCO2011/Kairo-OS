#ifndef KP_RECORDER_H
#define KP_RECORDER_H

#include <stdint.h>

// Type1: Általános súlyossági szintek
typedef enum {
    LOG_INFO = 0,
    LOG_ERRO,
    LOG_WARN,
    LOG_SUCC,
    LOG_FAIL,
    LOG_OTHE
} log_type1_t;

// Bináris log rekord struktúra (fix méret a gyors íráshoz)
typedef struct {
    uint32_t timestamp;    // Időbélyeg (a kp-syncronizer-től jöhet)
    uint8_t  t1;           // log_type1_t
    char     t2[8];        // Type2: Alrendszer neve (pl. "KERNEL", "DRV_KBD")
    uint8_t  sender_id;    // Küldő komponens ID-ja (id.c alapján)
    char     message[64];  // Maga az üzenet
} log_entry_t;

#endif