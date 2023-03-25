//
// Created by 袁蕴宸 on 20/2/2023.
//


//convention about protocol mode:
//terminated -- 1, application notification -- 2, schedule requering -- 3.

#include "coding_tools.h"


//integer coding
void integer_little_endian_encoding (int num, char* dst) {
    //clear the buffer
    int i;
    for (i = 0; i < 4; ++i) {
        dst[i] = 0;
    }
    //extract & write
    for (int i = 0; i < 4; ++i) {
        //1' extract
        int mask = (num >> (sizeof(char) * 8 * i)) & 0xff;
        //2' write
        dst[i] = (char) mask;
    }
}

int integer_little_endian_decoding(const char* src) {
    int res = 0;
    int i;
    for (i = 0; i< 4; ++i) {
        int mask = (int) ((unsigned char) (src[i]));
        mask <<= ( 8 * i);
        res |= mask;
    }
    return res;
}