//
// Created by 袁蕴宸 on 21/2/2023.
//

#ifndef COMP2432_PROJECT_G02_MODULES_H
#define COMP2432_PROJECT_G02_MODULES_H


#include "../classes/scheduling.h"
#include "../main.h"


void userProcess(int userIndex);
void appointmentModule (char* instruction);
void scheduleModule(char* instruction);
void outputModule (int rows, int columns, int scheduleMatrix[][columns], SCHEDULING_ALGORITHM algorithm);

#endif //COMP2432_PROJECT_G02_MODULES_H



