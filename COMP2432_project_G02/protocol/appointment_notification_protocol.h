//
// Created by 袁蕴宸 on 21/2/2023.
//

#ifndef COMP2432_PROJECT_G02_APPOINTMENT_NOTIFICATION_PROTOCOL_H
#define COMP2432_PROJECT_G02_APPOINTMENT_NOTIFICATION_PROTOCOL_H

#include "../classes/appointment.h"
#include "../classes/scheduling.h"




//--------------------------------------------------------------------------------------------------------------------------
//appointment notification service / protocol

extern const int APPOINTMENT_NOTIFICATION_PROTOCOL_REQUEST_MESSAGE_MAXIMUM_LENGTH;
extern const int APPOINTMENT_NOTIFICATION_PROTOCOL_PORT_NUMBER;

//level 1: application layer API
void  appointmentNotification_protocol_API_(SAppointment ap,  int wp);
//新加的接口：
//输入： read pointer (read pointer 指向的pipe 队列头为request message （不含port number) ）
//输出： Scard
//process : read,  decoding, return.
SCard appointmentNotification_protocol_interpret_request (int rp)




#endif //COMP2432_PROJECT_G02_APPOINTMENT_NOTIFICATION_PROTOCOL_H
