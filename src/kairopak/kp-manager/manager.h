#ifndef MANAGER_H
#define MANAGER_H

// Csak itt definiáljuk az ID-t, és csak egyszer!
#define ID_RECORDER "REC" 

// src/kairopak/kp-manager/manager.h
typedef struct {
    char from[16];
    char to[16];
    char content[128];
    int region;
    int state;
} __attribute__((packed)) kp_msg_t;

#endif