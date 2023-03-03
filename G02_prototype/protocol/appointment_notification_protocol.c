//
// Created by 袁蕴宸 on 21/2/2023.
//

#include <stdio.h>

#include "appointment_notification_protocol.h"
#include "../classes/scheduling.h"

const int APPOINTMENT_NOTIFICATION_PROTOCOL_REQUEST_MESSAGE_MAXIMUM_LENGTH = 800;


//level 1: application layer API
//deliver the appointment message to user process.
void  appointmentNotification_protocol_API_(struct SAppointment ap,  int wp) {

}

//level 2: presentation layer interface
char * appointmentNotification_protocol_requestMessage_encoding(struct SAppointment ap) {
    return NULL;
}

struct SAppointment appointmentNotification_protocol_requestMessage_decoding(char *message) {
    struct SAppointment a;
    return a;
}
