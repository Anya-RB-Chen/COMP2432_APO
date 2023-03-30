//
// Created by 袁蕴宸 on 25/2/2023.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "modules.h"

#include "../main.h"                //include the main function
#include "../classes/scheduling.c" 
#include "../classes/appointment.c"
#include "../classes/time_type.c"
#include "appointment_module.c"
   
//--------------------------------------------------------------------------------------------------------------------------
void printAllAlgorithm() {
    printf("FCFS\n");
    printf("Priority\n");
    printf("SRT\n");
}

//--------------------------------------------------------------------------------------------------------------------------
int numberOfAppointment(int appointmentMap[], int size) {
    int count = 0;
    for (int i = 0; i < size; i++) {
        if (appointmentMap[i] == 1) {
            count++;
        }
    }
    return count;
}



//output module:

//--------------------------------------------------------------------------------------------------------------------------
//use another format of matrix specification. The meaning is unchanged.
//need to maintain the sequence of output file.

// scheduleMatrix[i][j]: the response of user i to appointment j
// 1 -- accecpt, 0 -- reject, -1 -- not included
void outputModule (int rows, int columns, int scheduleMatrix[][columns], SCHEDULING_ALGORITHM algorithm) {

    //-------------------------------------------------------
    // This section is only for test
    // Comment this section when submit
    char nameMap[10][50] = {"John", "Paul", "Lucy", "Mary"};
    //-------------------------------------------------------

    //-------------------------------------------------------
    // Create the output file
    char* path = (char*)calloc(100, sizeof(char));
    strcat(path, "../output/");

    char* schedule_name = get_SchedingAlgorithm_name(algorithm);
    char* filename = (char*)calloc(100, sizeof(char));
    strcat(filename, "Ggg_02_");
    strcat(filename, schedule_name);
    strcat(filename, ".txt");

    strcat(path, filename);
    FILE *f = fopen(path, "w");
    // printf("Output file: %s\n", path);
    //-------------------------------------------------------

    //-------------------------------------------------------
    // print the time period
    if ( !g_startTime.day || !g_endTime.day) {
        g_startTime = getTime("230401", "0000");
        g_endTime = getTime("230430", "2359");
    }
    fprintf(f, "Period %s to %s\n", timeToString(g_startTime), timeToString(g_endTime));

    //-------------------------------------------------------
    // print the schedule type
    if (strcmp(schedule_name, "") == 0) {printAllAlgorithm();   return;}
    fprintf(f, "Algorithm used: %s\n", schedule_name);

    //-------------------------------------------------------
    // print the Appointment Schedule of every user
    fprintf(f, "\n***Appointment Schedule***\n\n");
    for (int i = 0; i < rows; i++) {
        fprintf(f, "\t%s, you have %d appointments.\n", nameMap[i], numberOfAppointment(scheduleMatrix[i], columns));
        fprintf(f, "Date         Start   End     Type             People\n");
        fprintf(f, "=========================================================================\n");
        for (int j = 0; j < columns; j++) {
            if (scheduleMatrix[i][j] == 1) {
                fprintf(f, "%s %s %s\n", timeToString(g_appointmentArray[j].startTime), timeToString(g_appointmentArray[j].endTime));
            }
        }
        fprintf(f, "\n");
    }



}
//--------------------------------------------------------------------------------------------------------------------------

int rescheduleALgorithm(int appointmentMap[],  SAppointment*  rescheduledAppointmentArray)
{
    int size_of_array;
    return size_of_array;
}

//--------------------------------------------------------------------------------------------------------------------------
// Only used for test
void printMatrix(int rows, int columns, int scheduleMatrix[][columns]) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < columns; j++) {
            printf("%d\t", scheduleMatrix[i][j]);
        }
        printf("\n");
    }
}

//--------------------------------------------------------------------------------------------------------------------------

// Only for test usage
void test_output() {
    g_userNum = 4;
    g_apNum = 3;
    int scheduleMatrix[4][3] = {{-1, 1, 0}, {1, 0, 0}, {1, -1, -1}, {0, 1, 1}};

    SAppointment appointment1 = interpretAppointmentInstruction("privateTime paul 20230401 1800 2.0");

    // Comment out the following line to test the scheduleMatrix
    printMatrix(g_userNum, g_apNum, scheduleMatrix);

    outputModule(g_userNum, g_apNum, scheduleMatrix, FCFS);
}