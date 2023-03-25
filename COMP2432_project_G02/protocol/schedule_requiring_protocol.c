//
// Created by 袁蕴宸 on 25/2/2023.
//

#include <stdio.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../classes/scheduling.h"
#include "protocol.h"


const int SCHHEDULE_REQUERING_PROTOCOL_REQUEST_MESSAGE_MAXIMUM_LENGTH = 800 ;
const int SCHEDULE_REQUERING_PROTOCOL_RESPONSE_MESSAGE_MAXIMUM_LENGTH  = 800;

const int SCHEDULE_REQUERING_PROTOCOL_PORT_NUMBER = 12345;

void scheduleRequering_protocol_requestMessage_encoding(SCHEDULING_ALGORITHM algorithm, char* dst);

SCHEDULING_ALGORITHM scheduleRequering_protocol_requestMessage_decoding(char *message);

char*  scheduleRequering_protocol_responseMessage_encoding(int** personalScheduleArray, int scheduleNum);

int**  scheduleRequering_protocol_responseMessage_decoding(char *message);


//level 1: application layer API
//recipient:  parent process / APO
//server: child process / user
int**  scheduleRequering_protocol_recipientAPI(SCHEDULING_ALGORITHM algorithm, int rp, int wp) {
    // write request message to the child
    char request[4];
    scheduleRequering_protocol_requestMessage_encoding(algorithm,request);
    write(wp,request,3);

    // read response, decoding and return
    int n,i,j;
    char message[648];
    n = read(rp, message, 648);
    int **res = (int **)malloc(2 * sizeof(int *));

    res = scheduleRequering_protocol_responseMessage_decoding(message);

    return res;
}

////special one:
//void  scheduleRequering_protocol_serverAPI(char* requestMessage, int wp, SAppointment ap_array[], int arraySize) {
//    SCHEDULING_ALGORITHM algorithm = scheduleRequering_protocol_requestMessage_decoding(requestMessage);
//
//
//    int** personalSchedule;
//    switch (algorithm) {
//        case FCFS:
//            personalSchedule = FCFS_schedule_algorithm (ap_array,  arraySize);
//            break;
//        case Priority:
//            personalSchedule = Priority_schedule_algorithm(ap_array,arraySize);
//            break;
//        case SRT:
//            personalSchedule = SRT_schedule_algorithm(ap_array,arraySize);
//            break;
//        case RR:
//            personalSchedule = RR_schedule_algorithm(ap_array,arraySize);
//    }
//
//    char* message;
//    // encode personal schedule
//    message = scheduleRequering_protocol_responseMessage_encoding(personalSchedule,arraySize);
//
//    // write schdule back to pointer
//    write(wp,message,sizeof (message));
//}


//level 2: presentation layer interface
void  scheduleRequering_protocol_requestMessage_encoding(SCHEDULING_ALGORITHM algorithm, char* dst) {
    if (algorithm == FCFS) {
        strcpy(dst,"FCF");
    } else if (algorithm == Priority){
        strcpy(dst,"PRI");
    } else if (algorithm == SRT){
        strcpy(dst,"SRT");
    } else if (algorithm == RR){
        strcpy(dst,"RRR");
    }
}


SCHEDULING_ALGORITHM scheduleRequering_protocol_requestMessage_decoding(char *message) {
    if (strcmp(message,"FCF") == 0) {
        return FCFS;
    } else if (strcmp(message,"PRI") == 0){
        return Priority;
    } else if (strcmp(message,"SRT") == 0){
        return SRT;
    } else if (strcmp(message,"RRR") == 0){
        return RR;
    }
    return 0;
}



char*  scheduleRequering_protocol_responseMessage_encoding(int** personalScheduleArray, int scheduleNum) {
    // encode message: scheduleNum|xxx|xxx|
    int i, j;
    static char encode[256];
    char *seperate = "|";
    char buffer[10];
    encode[0] = (char)( scheduleNum+48);
    encode[1] = '|';
    for (i = 0; i<2; i++) {
        for (j = 0; j < scheduleNum; j++){
            char *temp = Int2String(personalScheduleArray[i][j],buffer);
            strcat(encode,temp);
            strcat(encode,seperate);
        }
    }
    return encode;
}


int**  scheduleRequering_protocol_responseMessage_decoding(char *message) {
    int scheduleNum = message[0] - 48;
    int **schedule = (int **)malloc(2 * sizeof(int *));
    //int schedule[256][256];
    int i = 2, j, k = 0, m;
    for (m=0; m<scheduleNum; m++)
        schedule[m] = (int *)malloc(scheduleNum * sizeof(int));
    // appointment index
    for (j = 0; j<scheduleNum; j++){
        char temp[5];
        for (m = 0; m<5; m++) temp[m] = '\0';
        while (message[i] != '|'){
            temp[k] = message[i];
            i++;
            k++;
        }
        int res = atoi(temp);
        schedule[0][j] = res;
        k = 0;
        i++;
    }
    // decision
    for (j = 0; j<scheduleNum; j++){
        while (message[i] != '|'){
            schedule[1][j] = message[i] - 48;
            i++;
        }
        i++;
    }
    return schedule;
}
