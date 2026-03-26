// src/kairopak/kp-link/link.h
#ifndef LINK_H
#define LINK_H

#include "../kp-manager/manager.h" // Ez hozza be a kp_msg_t-t és az ID_RECORDER-t

// Érték szerinti átadás helyett mutatót használunk
void kp_link_post(kp_msg_t* msg); 
int kp_link_fetch(kp_msg_t* msg);

#endif