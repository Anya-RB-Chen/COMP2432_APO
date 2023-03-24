//
// Created by 袁蕴宸 on 21/2/2023.
//

#ifndef COMP2432_PROJECT_G02_APPOINTMENT_NOTIFICATION_PROTOCOL_H
#define COMP2432_PROJECT_G02_APPOINTMENT_NOTIFICATION_PROTOCOL_H

#include "../classes/appointment.h"
#include "../classes/scheduling.h"
#include <stdlib.h>
#include <string.h>



//--------------------------------------------------------------------------------------------------------------------------
//appointment notification service / protocol

extern const int APPOINTMENT_NOTIFICATION_PROTOCOL_REQUEST_MESSAGE_MAXIMUM_LENGTH;

//level 1: application layer API
void  appointmentNotification_protocol_API_(SAppointment ap,  int wp); //deliver the appointment message to user process.
//SAppointment  appointmentNotification_protocol_childAPI(int rp);

//level 2: presentation layer interface
char *appointmentNotification_protocol_requestMessage_encoding(SAppointment ap);
SAppointment *appointmentNotification_protocol_requestMessage_decoding(char *message);
char* Int2String(int num,char *str);

#endif //COMP2432_PROJECT_G02_APPOINTMENT_NOTIFICATION_PROTOCOL_H
