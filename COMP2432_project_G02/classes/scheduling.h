//
// Created by 袁蕴宸 on 20/2/2023.
//

#ifndef COMP2432_PROJECT_G02_SCHEDULING_H
#define COMP2432_PROJECT_G02_SCHEDULING_H

#include "appointment.h"

typedef enum  SCHEDULING_ALGORITHM{
    FCFS = 0 , Priority = 1 , ALL//...
} SCHEDULING_ALGORITHM;

SCHEDULING_ALGORITHM getSCHEDULING_ALGORITHM (int mode);
char* get_SchedingAlgorithm_name (SCHEDULING_ALGORITHM algorithm);

typedef enum RESCHEDULING_ALGORITHM{
    RE_FCFS
} RESCHEDULING_ALGORITHM;

//output format: 2d array:  2 * arraySize
//row 1: appointment index
//row 2: accept 1 / reject 0
int** FCFS_schedule_algorithm (SAppointment ap_array[],  int arraySize);
int** Priority_schedule_algorithm (SAppointment ap_array[],  int arraySize);

#endif //COMP2432_PROJECT_G02_SCHEDULING_H
