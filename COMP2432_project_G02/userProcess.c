//
// Created by 袁蕴宸 on 20/2/2023.
//

#include <stdio.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "main.h"

char g_nameMap[10][50]; //array to store the user name.
int g_userNum;
//related function

//(3) IPC
//int* g_p2c_fd; //pointer of pipe from parent to child
//int* g_c2p_fd; //pointer of pipe from child to parent;
//const int P2C_BUFFER_SIZE = 800;
//const int C2P_BUFFER_SIZE = 800;

//(4) appointment
int g_apNum = 0;
//assumption: not exceed the capacity
//!security problem: visible to the user process
const int DEFAULT_CAPACITY_OF_VECTOR = 1000;
SAppointment g_appointmentArray[DEFAULT_CAPACITY_OF_VECTOR];  //assumption: not exceed the capacity

//child process:
//------------------------------------------------------------------------------------------------------------------------//------------------------------------------------------------------------------------------------------------------------//--------------------------------------------------------------------------------------------------------------------------

//static global function
static void closeUserConnection (int userIndex);
void test(SAppointment ap[],int); // only for testing
//function hierarchy.
//level 0:
void userProcess(int userIndex) {

    //1, initialize

    //(1) IPC pointer
    int read_pointer = g_p2c_fd[2 * userIndex];
    int write_Pointer = g_c2p_fd[2 * userIndex + 1];

    //(2) ds: appointment array.
    int arraySize = 0;

    //2,  interprocess communication.
    int terminate = 0;
    while (terminate == 0) {
        char portNumbuffer[1];
        //(1) read the portNum ------ need the message from parent include port number.
        if (read(read_pointer, portNumbuffer, 1) < 0) {
            perror("userProcess: read port number.");
            exit(1);
        }

        int portNum = atoi(portNumbuffer);
//        printf("idx %d pid %d, read port number %d\n",userIndex,getpid(),portNum);

        SAppointment newAp;
        SCHEDULING_ALGORITHM algorithm;
        switch (portNum) {
            case 0:
                terminate = 1;
                break;

            case 1: //appointment protocol
                newAp = appointmentNotification_protocol_interpret_request(read_pointer);
                //
                g_appointmentArray[arraySize++] = newAp;


                //
                break;

            case 2: //schedule protocol

            //------------------------------------------------------------------------------------------------------------

//                test(g_appointmentArray,arraySize);
                algorithm = scheduleRequering_protocol_interpret_request (read_pointer);
                //
                //scheuduling service.
                int **personalScheduleMap = (int**)malloc(sizeof (int**)*2);
                int i;
                personalScheduleMap[0] = (int*) malloc(sizeof (int*)*DEFAULT_CAPACITY_OF_VECTOR);
                personalScheduleMap[1] = (int*) malloc(sizeof (int *)*DEFAULT_CAPACITY_OF_VECTOR);


//                test(g_appointmentArray,arraySize);

                // 为了测试comment掉
                switch (algorithm) {
                    case FCFS:
                        FCFS_schedule_algorithm (g_appointmentArray, arraySize, personalScheduleMap);
                        //------------------------------------------------------------------------------------------------------------
                        break;
                    case Priority:
                        Priority_schedule_algorithm(g_appointmentArray,arraySize, personalScheduleMap);
                        break;
                    case SRT:
                        SRT_schedule_algorithm(g_appointmentArray,arraySize, personalScheduleMap);
                        break;

                    default:
                        printf("userProcess: unknown algorithm\n");
                        exit(1);
                }

//                printf("User %d\n", userIndex);
//                int row, col;
//                for (row = 0; row < 2; ++row) {
//                    for (col = 0; col < arraySize; ++col) {
//                        printf("%d  ",personalScheduleMap[row][col]);
//                    }
//                    printf("\n");
//                }
//                printf("\n");

                scheduleRequering_protocol_deliverScheduleMap(personalScheduleMap, arraySize,write_Pointer);
                free(personalScheduleMap);
                break;

            default:
                printf("Unknown port number %d\n", portNum);
                exit(1);
        }
    }


    //3, release recourse
//    close(read_pointer);
//    close(write_Pointer);
    closeUserConnection(userIndex);
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


void test(SAppointment ap[],int size){
    int i,j;
    for (i = 0; i<size; i++){
        printf("caller %s year %d, mon %d, duration %f, idx %d, ", ap[i].caller,ap[i].startTime.year, ap[i].startTime.month,
               ap[i].duration, ap[i].apIndex);
        printf("callees are ");
        for (j = 0;j<ap[i].numberOfCallee; j++){
            printf("%s, ",ap[i].callee[j]);
        }
        printf("\n");
    }
}

