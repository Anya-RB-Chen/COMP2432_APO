//
// Created by 袁蕴宸 on 20/2/2023.
//


//convention about protocol mode:
//terminated -- 1, application notification -- 2, schedule requering -- 3.

#include "coding_tools.h"

void integer_little_endian_encoding (int num, char* dst) {
    //clear
    int i;
    for (i = 0; i < 4; ++i) {
        dst[i] &= 0x00;
    }
    //write
    for (i = 0; i < 4; ++i) {
        dst[i] |= (num >> (sizeof(char) * i))/* & 0xff*/;
    }
}

int integer_little_endian_decoding(char* src) {
    int res = 0;
    int i;
    for (i = 0; i < 4; ++i) {
        res |= (src[i] << (sizeof(char) * i));
    }
    return res;
}