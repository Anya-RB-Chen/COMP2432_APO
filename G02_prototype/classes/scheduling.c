//
// Created by 袁蕴宸 on 20/2/2023.
//

#include "scheduling.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int** FCFS_schedule_algorithm (struct SAppointment ap_array[],  int arraySize) {
    return NULL;
}

enum SCHEDULING_ALGORITHM getSCHEDULING_ALGORITHM (int mode) {
    static const int SCHEDULING_ALGORITHM_COUNT = 2;
    static const enum SCHEDULING_ALGORITHM SCHEDULING_ALGORITHM_ARRAY[] = {FCFS, ALL};
    if (mode < 0 || mode >= SCHEDULING_ALGORITHM_COUNT) {
        return (enum SCHEDULING_ALGORITHM) NULL; //?
    }
    return SCHEDULING_ALGORITHM_ARRAY[mode];
}

char* get_SchedingAlgorithm_name (enum SCHEDULING_ALGORITHM algorithm) {
    char* message;
    switch (algorithm) {
        case FCFS:
//            return "FCFS"; //?
             message = "FCFS";
             break;
        case Priority:
            message = "Priority";
            break;
        case ALL:
            message = "All";
            break;
        default:
            message = "";
    }
    char* result = (char*) (malloc((sizeof(char) *(strlen(message) + 1))));
    strcpy(result, message);
    return result;
}

