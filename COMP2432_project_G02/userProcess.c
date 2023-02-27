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
#include "protocol/appointment_notification_protocol.h"
#include "protocol/schedule_requiring_protocol.h"

//child process:
//------------------------------------------------------------------------------------------------------------------------//------------------------------------------------------------------------------------------------------------------------//--------------------------------------------------------------------------------------------------------------------------

//static global function
static void closeUserConnection (int userIndex);

//function hierarchy.
//level 0:
void userProcess(int userIndex) {
//--------------------------------------------------------------------------------------------------------------------------
    printf("(pid: %d)  Child process %d is created for %s\n",  getpid(),userIndex, g_nameMap[userIndex]);
    sleep(1);
    printf("(pid: %d)  Child process %d  terminated\n",  getpid(),userIndex);
    exit(userIndex);
//--------------------------------------------------------------------------------------------------------------------------

    //1, initialize
    struct SAppointment * ap_array;
    int arraySize = 0;
    int p2c_read_pointer;
    int c2p_write_Pointer;

    //(1) IPC pointer
    closeUserConnection(userIndex);
    p2c_read_pointer = g_p2c_fd[2 * userIndex];
    c2p_write_Pointer = g_c2p_fd[2 * userIndex + 1];
    char *readBuffer = (char *) (malloc(sizeof(char) * P2C_BUFFER_SIZE));
    char *writeBuffer = (char *) (malloc(sizeof(char) * C2P_BUFFER_SIZE));

    //(2) ds: appointment array.
    ap_array = (struct SAppointment *) (malloc(sizeof(struct SAppointment) * DEFAULT_CAPACITY_OF_VECTOR));


    //2,  interprocess communication.
    int terminate = 0;
    int n;
    while (terminate == 0) { //continue to read message until get terminated signal
        //blocking
        //(1) read the mode
        if ((n = read(p2c_read_pointer, readBuffer, sizeof(int))) < 0) {
            perror("read");
            exit(1);
        }
        readBuffer[n] = 0;

        int portNumber = integer_little_endian_decoding(readBuffer);

        //branch of message mode: do the corresponding operation.
        if (portNumber == 0) { //case1: get the terminating message
            terminate = 1;

        } else {
            // (2) get the message
            //1' get message len
            if ((n = read(p2c_read_pointer, readBuffer, sizeof(int))) < 0) {
                perror("read");
                exit(1);
            }
            readBuffer[n] = 0;
            int messageLen = integer_little_endian_decoding(readBuffer);

            //2' get the message
            if ((n = read(p2c_read_pointer, readBuffer, sizeof(int) * messageLen)) < 0) {
                perror("read");
                exit(1);
            }
            readBuffer[n] = 0;

            //3' corresponding operations
            if (portNumber == 2) { //mode 2: appointment notification protocol: child process receive appointment information from parent.
                struct SAppointment newAp = appointmentNotification_protocol_requestMessage_decoding(readBuffer);
                ap_array[arraySize++] = newAp;

            } else {// mode 3: schedule request protocol: APO query user's schedule based on particular algorithm.
                scheduleRequering_protocol_serverAPI(readBuffer, c2p_write_Pointer, ap_array, arraySize);
            }
        }
    }

    //release recourse

}

//
static void closeUserConnection (int userIndex) {

}