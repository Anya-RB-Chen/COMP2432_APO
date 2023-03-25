//
// Created by 袁蕴宸 on 21/2/2023.
//

#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>

#include "../classes/appointment.h"
#include "../main.h"
#include "../protocol/protocol.h"

static struct SAppointment interpretAppointmentInstruction (char* instruction);
static int isValidTimeRange(struct STime startTime, struct STime endTime);
static void notifyUsersAboutAP1 (struct SAppointment appointment);
static int get_p2cWritePointer_by_name (char* name);


//level 1
//input: appointment type instruction (not ensure the validity)
//output: interpret the instruction and do the corresponding operation

void appointmentModule (char* instruction) {
    //1, interpret the appointment instruction
   struct SAppointment appointment = interpretAppointmentInstruction(instruction);
   if (isValidTimeRange(appointment.startTime, appointment.endTime) == 0) {
       printf("The time is out of range.\n");
       return;
   }
    appointment.apIndex = g_apNum;
   g_appointmentArray[g_apNum++] = appointment;  //! problem: apo save appointment information.


   //2,  notify the users about the appointment
    // notify all the caller a& callee
    //1' caller
    int  writePtr_to_caller = get_p2cWritePointer_by_name(appointment.caller);
    if (writePtr_to_caller != -1) {
        appointmentNotification_protocol_API_(appointment,  writePtr_to_caller);
    }
    //2' callee
    int i;
    for (i = 0; i < appointment.numberOfCallee; ++i) {
        char* callee = appointment.callee[i]; // dangerous
        writePtr_to_caller = get_p2cWritePointer_by_name(callee);
        if ( writePtr_to_caller == -1) {
            printf("appointmentModule: The caller name is not valid.\n");
            exit(1);
        }
        appointmentNotification_protocol_API_(appointment,  writePtr_to_caller);
    }
}

//level 2
//------------------------------------------------------------------------------------------------------------------------//--------------------------------------------------------------------------------------------------------------------------
//input: Appointment type Instruction
//output: translate it to SAppointment type.
//        ( no need to initialize apIndex. If there is no caller, set the caller to empty string.)
static SAppointment interpretAppointmentInstruction (char* instruction) {
    SAppointment a;
    return a;
}

//input: time range
//output: is valid ( in range [ g_startTime, g_endTime])
static int isValidTimeRange(STime startTime, STime endTime) {
    return 0;
}
//--------------------------------------------------------------------------------------------------------------------------




//input: name
//output: user Index
//boudary case: name is empty string -> -1
static int get_UserIndex_by_name (char* name) {
    if (*name == 0) {
        return -1;
    }
    int userIndex;
    for (userIndex = 0; userIndex < g_userNum; ++userIndex) {
        if (strcmp(name, g_nameMap[userIndex]) == 0) {
            return userIndex;
        }
    }
    return -1; //error.
}


//intput: empty string or valid name
//output: -1           /     write pointer.
static int get_p2cWritePointer_by_name (char* name) {
    int userIndex = get_UserIndex_by_name(name);

    if (userIndex == -1) {
        return -1;
    }
    return g_p2c_fd[2 * userIndex + 1];
}
