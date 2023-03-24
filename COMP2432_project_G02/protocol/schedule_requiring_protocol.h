//
// Created by 袁蕴宸 on 25/2/2023.
//

#ifndef COMP2432_PROJECT_G02_SCHEDULE_REQUIRING_PROTOCOL_H
#define COMP2432_PROJECT_G02_SCHEDULE_REQUIRING_PROTOCOL_H

#include "../classes/appointment.h"
#include "../classes/scheduling.h"
//schedule requering service / protocol


extern const int SCHHEDULE_REQUERING_PROTOCOL_REQUEST_MESSAGE_MAXIMUM_LENGTH  ;
extern const int SCHEDULE_REQUERING_PROTOCOL_RESPONSE_MESSAGE_MAXIMUM_LENGTH  ;

//level 1: application layer API
//recipient:  parent process / APO
//server: child process / user
void  scheduleRequering_protocol_serverAPI(char* requestMessage, int wp, SAppointment ap_array[], int arraySize);
int**  scheduleRequering_protocol_recipientAPI(SCHEDULING_ALGORITHM algorithm, int rp, int wp);


//level 2: presentation layer interface
void scheduleRequering_protocol_requestMessage_encoding(SCHEDULING_ALGORITHM algorithm, char* dst);

SCHEDULING_ALGORITHM scheduleRequering_protocol_requestMessage_decoding(char *message);

char*  scheduleRequering_protocol_responseMessage_encoding(int** personalScheduleArray, int scheduleNum);

int**  scheduleRequering_protocol_responseMessage_decoding(char *message);

#endif //COMP2432_PROJECT_G02_SCHEDULE_REQUIRING_PROTOCOL_H
