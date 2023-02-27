//
// Created by 袁蕴宸 on 25/2/2023.
//

#include <stdio.h>

#include "schedule_requiring_protocol.h"
#include "../classes/scheduling.h"


const int SCHHEDULE_REQUERING_PROTOCOL_REQUEST_MESSAGE_MAXIMUM_LENGTH = 800 ;
const int SCHEDULE_REQUERING_PROTOCOL_RESPONSE_MESSAGE_MAXIMUM_LENGTH  = 800;


//level 1: application layer API
//recipient:  parent process / APO
//server: child process / user
int  scheduleRequering_protocol_recipientAPI(enum SCHEDULING_ALGORITHM algorithm, int rp, int wp,  int** personalSchedule) {
    return 0;
}

//special one:
void  scheduleRequering_protocol_serverAPI(char* requestMessage, int wp, struct SAppointment ap_array[], int arraySize) {
    enum SCHEDULING_ALGORITHM algorithm = scheduleRequering_protocol_requestMessage_decoding(requestMessage);


    int** personalSchedule;
    switch (algorithm) {
        case FCFS:
            personalSchedule = FCFS_schedule_algorithm (ap_array,  arraySize);
            break;
        case Priority:
            break;
        case ALL:
            break;
    }
    //
}


//level 2: presentation layer interface
char * scheduleRequering_protocol_requestMessage_encoding(enum SCHEDULING_ALGORITHM algorithm) {
    return NULL;
}

enum SCHEDULING_ALGORITHM scheduleRequering_protocol_requestMessage_decoding(char *message) {
    return FCFS;
}

char * scheduleRequering_protocol_responseMessage_encoding(int** personalScheduleArray) {
    return NULL;
}

int  scheduleRequering_protocol_responseMessage_decoding(char *message, int** personalSchedule) {
    return 0;
}
