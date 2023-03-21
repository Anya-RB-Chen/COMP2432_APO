//
// Created by 袁蕴宸 on 21/2/2023.
//

#include <stdio.h>

#include "appointment_notification_protocol.h"
#include "../classes/scheduling.h"

const int APPOINTMENT_NOTIFICATION_PROTOCOL_REQUEST_MESSAGE_MAXIMUM_LENGTH = 800;


//level 1: application layer API
//deliver the appointment message to user process.
void  appointmentNotification_protocol_API_(SAppointment ap,  int wp) {

}

//level 2: presentation layer interface
void appointmentNotification_protocol_requestMessage_encoding(SAppointment ap, char* dst) {

}

SAppointment appointmentNotification_protocol_requestMessage_decoding(char *message) {
    SAppointment a;
    return a;
}
