//
// Created by 袁蕴宸 on 20/2/2023.
//

#include "scheduling.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int** FCFS_schedule_algorithm (SAppointment ap_array[],  int arraySize) {
    return NULL;
}

SCHEDULING_ALGORITHM getSCHEDULING_ALGORITHM (int mode) {
    static const int SCHEDULING_ALGORITHM_COUNT = 2;
    static const SCHEDULING_ALGORITHM SCHEDULING_ALGORITHM_ARRAY[] = {FCFS, ALL};
    return SCHEDULING_ALGORITHM_ARRAY[mode];
}

char* get_SchedingAlgorithm_name (SCHEDULING_ALGORITHM algorithm) {
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

