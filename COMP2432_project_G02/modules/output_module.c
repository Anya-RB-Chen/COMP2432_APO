//
// Created by 袁蕴宸 on 25/2/2023.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "../main.h"                //include the main function
#include "../classes/scheduling.c" 
#include "../classes/appointment.c"
#include "../classes/time_type.c"             


//output module:

//--------------------------------------------------------------------------------------------------------------------------
//use another format of matrix specification. The meaning is unchanged.
//need to maintain the sequence of output file.
void outputModule (int rows, int columns, int scheduleMatrix[][columns], SCHEDULING_ALGORITHM algorithm) {

    if (g_startTime.day == NULL || g_endTime.day == NULL) {
        g_startTime = getTime("20230401", "0000");
        g_endTime = getTime("20230430", "2359");
    }
    
    printf("Period 2023-04-01 to 2023-04-30\n");

    char* schedule_name = get_SchedingAlgorithm_name(algorithm);
    if (strcmp(schedule_name, "") == 0) {
        strcpy(schedule_name, "ALL");
    }
    printf("Algorithm used: %s\n", schedule_name);

    printf("\n***Appointment Schedule***\n");
}
//--------------------------------------------------------------------------------------------------------------------------

// Only for test usage
void main() {
    int scheduleMatrix[3][3] = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
    outputModule(3, 3, scheduleMatrix, FCFS);
}