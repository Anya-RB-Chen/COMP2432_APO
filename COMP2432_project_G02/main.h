//
// Created by 袁蕴宸 on 20/2/2023.
//

#ifndef COMP2432_PROJECT_G02_MAIN_H
#define COMP2432_PROJECT_G02_MAIN_H

#include "classes/time_type.h"
#include "classes/appointment.h"


//global variable & constant

//global variable definition
//(0) DS
extern const int DEFAULT_CAPACITY_OF_VECTOR;  //default capacity of vector in this program.

//（1）time
STime g_startTime, g_endTime; //define valid time range

//(2) name
char g_nameMap[10][50]; //array to store the user name.
int g_userNum;
//related function

//(3) IPC
int* g_p2c_fd; //pointer of pipe from parent to child
int* g_c2p_fd; //pointer of pipe from child to parent;
//const int P2C_BUFFER_SIZE = 800;
//const int C2P_BUFFER_SIZE = 800;

//(4) appointment
int g_apNum;
SAppointment g_appointmentArray[DEFAULT_CAPACITY_OF_VECTOR];  //assumption: not exceed the capacity
//!security problem: visible to the user process

#endif //COMP2432_PROJECT_G02_MAIN_H
