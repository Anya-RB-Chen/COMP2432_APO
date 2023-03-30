//
// Created by 袁蕴宸 on 20/2/2023.
//

#ifndef COMP2432_PROJECT_G02_MAIN_H
#define COMP2432_PROJECT_G02_MAIN_H

#include "classes/time_type.h"
#include "classes/appointment.h"
#include "modules/modules.h"
#include "protocol/coding_tools.h"
#include "protocol/protocol.h"
#include "classes/scheduling.h"

//global variable & constant

//global variable definition
//(0) DS
  //default capacity of vector in this program.

extern const int DEFAULT_CAPACITY_OF_VECTOR;

//（1）time
STime g_startTime, g_endTime; //define valid time range

//(2) name
char g_nameMap[10][50]; //array to store the user name.
int g_userNum;
//related function

//(3) IPC
int* g_p2c_fd; //pointer of pipe from parent to child
int* g_c2p_fd; //pointer of pipe from child to parent;
//int g_p2c_fd[][2]; //pointer of pipe from parent to child
//int g_c2p_fd[][2]; //pointer of pipe from child to parent;

//const int P2C_BUFFER_SIZE = 800;
//const int C2P_BUFFER_SIZE = 800;

//(4) appointment
int g_apNum;
  //assumption: not exceed the capacity
//!security problem: visible to the user process

SAppointment g_appointmentArray[1000];  //assumption: not exceed the capacity

#define SCHEDULE_REQUERING_PROTOCOL_PORT_NUMBER = 1;
#define APPOINTMENT_NOTIFICATION_PROTOCOL_PORT_NUMBER = 2;

static void initialize(int argc, char* argv[]);
int getInstructionMode (char* instruction);
static void freeUpProgram ();

#endif //COMP2432_PROJECT_G02_MAIN_H
