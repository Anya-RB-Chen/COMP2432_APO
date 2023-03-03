//
// Created by 袁蕴宸 on 21/2/2023.
//

#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>

#include "../classes/appointment.h"
#include "../G02_prototype.h"
#include "../protocol/appointment_notification_protocol.h"

static struct SAppointment interpretAppointmentInstruction (char* instruction);
static int isValidTimeRange(struct STime startTime, struct STime endTime);
static void notifyUsersAboutAP1 (struct SAppointment appointment);
static int get_p2cWritePointer_by_name (char* name);


//level 1
void appointmentModule (char* instruction) {
    //1, interpret the appointment instruction
   struct SAppointment appointment = interpretAppointmentInstruction(instruction);
   if (isValidTimeRange(appointment.startTime, appointment.endTime) == 0) {
       printf("The time is out of range.\n");
       return;
   }
   g_appointmentArray[g_apNum++] = appointment; //! problem: apo save appointment information.


   //2,  notify the users about the appointment
    //(1) encode the message.
    char writeBuffer[APPOINTMENT_NOTIFICATION_PROTOCOL_REQUEST_MESSAGE_MAXIMUM_LENGTH];
    char* message = appointmentNotification_protocol_requestMessage_encoding(appointment);
    strcpy(writeBuffer, message); //dangerous on format of string

    //(2) notify all the caller a& callee
    int writePtr_to_caller = 0;
    //1' caller
    if (appointment.caller != NULL) { //have to keep caller = NULL if the appointment don't have caller !
        writePtr_to_caller = get_p2cWritePointer_by_name(appointment.caller);
        appointmentNotification_protocol_API_(appointment,  writePtr_to_caller);
    }
    //2' callee
    int i;
    for (i = 0; i < appointment.numberOfCallee; ++i) {
        char* callee = appointment.callee[i];
        writePtr_to_caller = get_p2cWritePointer_by_name(callee);
        appointmentNotification_protocol_API_(appointment,  writePtr_to_caller);
    }

}

//level 2
static struct SAppointment interpretAppointmentInstruction (char* instruction) {
    struct SAppointment a;
    return a;
}
static int isValidTimeRange(struct STime startTime, struct STime endTime) {
    return 0;
}


static int get_UserIndex_by_name (char* name);

//assumption: all the name is valid.
static int get_p2cWritePointer_by_name (char* name) {
    return 0;
}

//level 3
static int get_UserIndex_by_name (char* name) {
    return 0;
}
