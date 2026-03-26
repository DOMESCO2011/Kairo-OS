#include "link.h"

// A változók csak itt léteznek (static = fájlra korlátozott)
static kp_msg_t msg_buffer;
static int has_msg = 0;

// src/kairopak/kp-link/link.c
void kp_link_post(kp_msg_t* msg) { // Itt is kell a csillag!
    msg_buffer = *msg; 
    has_msg = 1;
}

int kp_link_fetch(kp_msg_t* msg) {
    if (has_msg) {
        *msg = msg_buffer;
        has_msg = 0;
        return 1;
    }
    return 0;
}