//
// Created by 袁蕴宸 on 20/2/2023.
//

#include <stdio.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//#include "userProcess.h"
#include "main.h"
#include "classes/appointment.h"
#include "protocol/coding_tools.h"
#include "classes/scheduling.h"
#include "protocol/protocol.h"

const int SCHEDULE_REQUERING_PROTOCOL_PORT_NUMBER = 1;
const int APPOINTMENT_NOTIFICATION_PROTOCOL_PORT_NUMBER = 2;

//child process:
//------------------------------------------------------------------------------------------------------------------------//------------------------------------------------------------------------------------------------------------------------//--------------------------------------------------------------------------------------------------------------------------

//static global function
static void closeUserConnection (int userIndex);

//function hierarchy.
//level 0:
void userProcess(int userIndex) {

    //1, initialize

    //(1) IPC pointer
    closeUserConnection(userIndex);
    int read_pointer = g_p2c_fd[2 * userIndex];
    int write_Pointer = g_c2p_fd[2 * userIndex + 1];

    //(2) ds: appointment array.
    SAppointment  ap_array[DEFAULT_CAPACITY_OF_VECTOR];
    int arraySize = 0;


    //2,  interprocess communication.
    char portNumbuffer[1];
    int terminate = 0;
    while (terminate == 0) {
        //(1) read the portNum ------ need the message from parent include port number.
        if (read(read_pointer, portNumbuffer, 1) < 0) {
            perror("userProcess: read port number.");
            exit(1);
        }

        int portNum = atoi(portNumbuffer);

        SAppointment newAp;
        SCHEDULING_ALGORITHM algorithm;
        switch (portNum) {
            case 0:
                terminate = 1;
                break;

            case APPOINTMENT_NOTIFICATION_PROTOCOL_PORT_NUMBER: //appointment protocol
                newAp = appointmentNotification_protocol_interpret_request(read_pointer);
                //
                ap_array[arraySize++] = newAp;
                //
                break;

            case SCHEDULE_REQUERING_PROTOCOL_PORT_NUMBER: //schedule protocol
                algorithm = scheduleRequering_protocol_interpret_request (read_pointer);
                //
                //scheuduling service.
                int **personalScheduleMap = (int**)malloc(sizeof (int**));
                personalScheduleMap[0] = (int*) malloc(sizeof (int*)*50);
                personalScheduleMap[1] = (int*) malloc(sizeof (int *)*50);

                switch (algorithm) {
                    case FCFS:
                        FCFS_schedule_algorithm (ap_array, arraySize, personalScheduleMap);
                        break;
                    case Priority:
                        Priority_schedule_algorithm(ap_array,arraySize, personalScheduleMap);
                        break;
                    case SRT:
                        SRT_schedule_algorithm(ap_array,arraySize, personalScheduleMap);
                        break;

                    default:
                        printf("userProcess: unknown algorithm\n");
                        exit(1);
                }
                //
                scheduleRequering_protocol_deliverScheduleMap(personalScheduleMap, arraySize,write_Pointer);
                free(personalScheduleMap);
                break;

            default:
                printf("Unknown port number %d\n", portNum);
                exit(1);
        }
    }


    //3, release recourse
    close(read_pointer);
    close(write_Pointer);
    exit(1);
}

//
static void closeUserConnection (int userIndex) {
    int readPtrIndex = userIndex * 2;
    int writePtrIndex = userIndex * 2 + 1;
    int i;
    for (i = 0; i < g_userNum * 2; ++i) {
        if (i != readPtrIndex) {
            close(g_p2c_fd[i]);
        }
        if (i != writePtrIndex) {
            close (g_c2p_fd[i]);
        }
    }
}

