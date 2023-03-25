//
// Created by 袁蕴宸 on 20/2/2023.
//

#ifndef COMP2432_PROJECT_G02_CODING_TOOLS_H
#define COMP2432_PROJECT_G02_CODING_TOOLS_H

#include "../classes/time_type.h"

int integer_little_endian_decoding(const char* src);
void integer_little_endian_encoding (int num, char* dst);
char* time_encoding (STime time);
STime time_decoding (char* str);

#endif //COMP2432_PROJECT_G02_CODING_TOOLS_H
