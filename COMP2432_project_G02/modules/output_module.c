//
// Created by 袁蕴宸 on 25/2/2023.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "modules.h"

//#include "../main.c"            //include the main function
//#include "../classes/scheduling.c"
//#include "../classes/appointment.c"
//#include "../classes/time_type.c"
//#include "appointment_module.c"
//// #include "../protocol/protocol.h"
//#include "../protocol/appointment_notification_protocol.c"
//#include "schedule_module.c"

// Global variables
int g_fileNum = 0;
char* nameToString(char name[50]);
int rescheduleALgorithm(int appointmentMap[],  SAppointment*  rescheduledAppointmentArray);
//--------------------------------------------------------------------------------------------------------------------------
void printAllAlgorithm(int scheduleMatrix[][g_apNum]) 
{
    // printf("FCFS\n");
    // printf("Priority\n");
    // printf("SRT\n");
    SCHEDULING_ALGORITHM SCHEDULING_ALGORITHM_ARRAY[] = {FCFS, Priority,SRT};
    int i;
    for (i=0; i<3; i++) {
        outputModule(g_userNum, g_apNum, scheduleMatrix, SCHEDULING_ALGORITHM_ARRAY[i]);
    }
}

//--------------------------------------------------------------------------------------------------------------------------

// Count the time duration of all appointments of one user
float countTimeDuration(int size, int scheduleMatrix[][size], int appointmentArray[size]) {
    float count = 0;
    int j;
    for (j = 0; j < size; j++) {
        if (appointmentArray[j] == 1) {
            count += g_appointmentArray[j].duration;
        }
    }
    return count;
}

// Check whether the appointment has been received by all users
int checkReceive(int size, int scheduleMatrix[][size], int appointmentIndex) {
    int i;
    for (i = 0; i < g_userNum; i++) {
        if (scheduleMatrix[i][appointmentIndex] == 0) {
            return 0;
        }
    }
    return 1;
}

// Count the time duration of accepted appointments of one user
float countAcceptedTimeDuration(int size, int scheduleMatrix[][size], int appointmentArray[size]) {
    float count = 0;
    int j;
    for (j = 0; j < size; j++) {
        if (appointmentArray[j] == 1 && checkReceive(size, scheduleMatrix, j) == 1) {
            count += g_appointmentArray[j].duration;
        }
    }
    return count;
}

// Count the number of appointments of one user that have been received by all users
int numberOfAppointment(int size, int scheduleMatrix[][size], int appointmentArray[size]) {
    int count = 0;
    int j;
    for (j = 0; j < size; j++) {
        if (checkReceive(size, scheduleMatrix, j) == 1) {
            count++;
        }
    }
    return count;
}


// Count the overall appointments that have been received by all users
int numberOfReceivedAppointment(int size, int scheduleMatrix[][size], SAppointment receivedAppointmentArray[size]) {
    int count = 0;
    int j;
    for (j = 0; j < size; j++) {
        if (checkReceive(size, scheduleMatrix, j) == 1) {
            receivedAppointmentArray[count] = g_appointmentArray[j];
            count++;
        }
    }
    return count;
}

// Count the overall appointments that have been rejected by all users
int numberOfRejectedAppointment(int size, int scheduleMatrix[][size], SAppointment rejectedAppointmentArray[size]) {
    int count = 0;
    int i,j;
    for (j = 0; j < size; j++) {
        for (i=0; i < g_userNum; i++) {
            if (scheduleMatrix[i][j] == 0) {
                rejectedAppointmentArray[count] = g_appointmentArray[j];
                count++;
                break;
            }
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

    g_fileNum++;

    //-------------------------------------------------------
    // This section is only for test
    // Comment this section when submit
    // char nameMap[10][50] = {"John", "Paul", "Lucy", "Mary"};
    //-------------------------------------------------------

    //-------------------------------------------------------
    // Create the output file
    char* path = (char*)calloc(100, sizeof(char));
    strcat(path, "../output/");

    char* schedule_name = get_SchedingAlgorithm_name(algorithm);
    char* filename = (char*)calloc(100, sizeof(char));
    strcat(filename, "Ggg_");

    if (g_fileNum < 10) {
        strcat(filename, "0");
    }
    char fileNum[10];
    sprintf(fileNum, "%d", g_fileNum);
    strcat(filename, fileNum);
    strcat(filename, "_");

    if (strcmp(schedule_name, "") == 0) {
        strcat(filename, "All");
    } else{
        strcat(filename, schedule_name);
    }

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
    fprintf(f, "Period %s to %s\n", dateToString(g_startTime), dateToString(g_endTime));

    //-------------------------------------------------------
    // print the schedule type
    if (strcmp(schedule_name, "") == 0) {printAllAlgorithm(scheduleMatrix);   return;}
    fprintf(f, "Algorithm used: %s\n", schedule_name);

    //-------------------------------------------------------
    // print the Appointment Schedule of every user
    SAppointment receivedAppointmentArray[columns];
    int numberOfReceived = numberOfReceivedAppointment(columns, scheduleMatrix, receivedAppointmentArray);

    int i, j;
    for (i = 0; i<g_userNum; i++){
        if (g_nameMap[i][0]>=97 && g_nameMap[i][0]<=122){
            g_nameMap[i][0] = g_nameMap[i][0] - 32;
        }
    }

    fprintf(f, "\n***Appointment Schedule***\n\n");
    for (i = 0; i < rows; i++) {
        fprintf(f, "\t%s, you have %d appointments.\n", g_nameMap[i], numberOfAppointment(columns, scheduleMatrix, scheduleMatrix[i]));
        fprintf(f, "Date         Start   End     Type             People\n");
        fprintf(f, "=========================================================================\n");
        for (j = 0; j < columns; j++) {
            if (checkReceive(columns, scheduleMatrix, i) == 1 ) {
                SAppointment appointment = g_appointmentArray[j];
                fprintf(f, "%s   %s   %s   %s  ", dateToString(appointment.startTime), timeToString(appointment.startTime), timeToString(appointment.endTime), getAP_TYPE(appointment.type));
                for (int k = 0; k < appointment.numberOfCallee; k++) {
                    fprintf(f, "%s ", appointment.callee[k]);
                }
                fprintf(f, "                     - End of %s’s Schedule -\n                       ", g_nameMap[i]);
                fprintf(f, "=========================================================================\n");
            }
        }
        fprintf(f, "\n");
    }

    //-------------------------------------------------------
    // print the Rejected List of every appointment
    SAppointment rejectedAppointmentArray[columns];
    int numberOfRejected = numberOfRejectedAppointment(columns, scheduleMatrix, rejectedAppointmentArray);

    fprintf(f, "\n***Rejected List***\n\n");
    fprintf(f, "Altogether there are %d appointments rejected.\n", numberOfRejected);
    fprintf(f, "=========================================================================\n");

    for (i=0; i < columns; i++) {
        if (rejectedAppointmentArray[i].startTime.day) {
            fprintf(f, "%d. ", i+1);
            fprintf(f, "%s %s %s %s %d", get_AP_TYPE_name(rejectedAppointmentArray[i].type), nameToString(rejectedAppointmentArray[i].caller),
                    dateToString(rejectedAppointmentArray[i].startTime), 
                    timeToString(rejectedAppointmentArray[i].startTime), 
                    rejectedAppointmentArray[i].duration);
            for (j=0; j < rejectedAppointmentArray[i].numberOfCallee; j++) {
                fprintf(f, " %s", rejectedAppointmentArray[i].callee[j]);
            }
        }
    }
    fprintf(f, "                     - End of Rejected List -\n                       ");
    fprintf(f, "=========================================================================\n");

    //-------------------------------------------------------
    // print the Performance of this algorithm
    fprintf(f, "\n***Performance***\n\n");

    fprintf(f, "Total Number of Requests Received: %d\n", columns);
    float receivedRate = (float)numberOfReceived / (float)columns;
    fprintf(f, "Total Number of Requests Accepted: %d (%f)\n", numberOfReceived, receivedRate);
    float rejectedRate = (float)numberOfRejected / (float)columns;
    fprintf(f, "Total Number of Requests Rejected: %d (%f)\n", numberOfRejected, rejectedRate);

    fprintf(f, "\n\n\n");

    // Number of Requests Accepted by Individual Users
    fprintf(f, "Number of Requests Accepted by Individual:\n\n");
    for (i = 0; i < rows; i++) {
        fprintf(f, "\t%s \t\t\t %d\n", g_nameMap[i], numberOfAppointment(columns, scheduleMatrix, scheduleMatrix[i]));
    }

    fprintf(f, "\n\n\n");

    // Utilization of Time Slot
    fprintf(f, "Utilization of Time Slot:\n\n");
    for (i = 0; i < rows; i++) {
        float timeDuration = countTimeDuration(columns, scheduleMatrix, scheduleMatrix[i]);
        float acceptedDuration = countAcceptedTimeDuration(columns, scheduleMatrix, scheduleMatrix[i]);
        float utilization = acceptedDuration / timeDuration;
        fprintf(f, "\t%s \t\t\t %f\n", g_nameMap[i], utilization);
    }

    fprintf(f, "\n\n\n");

    //-------------------------------------------------------
    // print the Rescheduled List of every appointment
    int numOfRescheduled = rescheduleALgorithm(appointmentMap, rescheduledAppointmentArray);

    fprintf(f, "\n***Rescheduled List***\n\n");
    fprintf(f, "There are %d appointments to be rescheduled.\n", numOfRescheduled);
    fprintf(f, "=========================================================================\n");
    int n;
    for (n=0; n < numOfRescheduled; n++) {
        fprintf(f, "%d. ", n+1);
        fprintf(f, "%s  %s  %s  %s  %d", get_AP_TYPE_name(rescheduledAppointmentArray[n].type), nameToString(rescheduledAppointmentArray[n].caller),
                dateToString(rescheduledAppointmentArray[n].startTime), 
                timeToString(rescheduledAppointmentArray[n].startTime), 
                rescheduledAppointmentArray[n].duration);
        for (j=0; j < rescheduledAppointmentArray[n].numberOfCallee; j++) {
            fprintf(f, " %s", rescheduledAppointmentArray[n].callee[j]);
        }
    }

    //-------------------------------------------------------
    // close the file
    fclose(f);

}
//--------------------------------------------------------------------------------------------------------------------------

int rescheduleALgorithm(int appointmentMap[],  SAppointment*  rescheduledAppointmentArray)
{
    int count = 0;
    while (rescheduledAppointmentArray[count].startTime.day) {
        count++;
    }
    return count;
}

char* nameToString(char name[50]){
    char* nameString = (char*)calloc(50, sizeof(char));
    strcat(nameString, name);
    return nameString;
}

//--------------------------------------------------------------------------------------------------------------------------
// Only used for test
void printMatrix(int rows, int columns, int scheduleMatrix[][columns]) {
    int i, j;
    for (i = 0; i < rows; i++) {
        for (j = 0; j < columns; j++) {
            printf("%d\t", scheduleMatrix[i][j]);
        }
        printf("\n");
    }
}

//--------------------------------------------------------------------------------------------------------------------------