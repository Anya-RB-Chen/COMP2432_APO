//
// Created by 袁蕴宸 on 20/2/2023.
//

#ifndef COMP2432_PROJECT_G02_G02_PROTOTYPE_H
#define COMP2432_PROJECT_G02_G02_PROTOTYPE_H

#include "classes/time_type.h"
#include "classes/appointment.h"


//global variable & constant

//(0) DS
const int DEFAULT_CAPACITY_OF_VECTOR;  //default capacity of vector in this program.
// assumption: the size of vector will not exceed 128, and we do not need to invoke expand method.
//----simplify the DS vector to array & write pointer.

//（1）time
struct STime g_startTime, g_endTime; //define valid time range

//(2) name
char** g_nameMap; //array to store the user name.
int g_userNum;
//related function

//(3) IPC
int* g_p2c_fd; //pointer of pipe from parent to child
int* g_c2p_fd; //pointer of pipe from child to parent;
extern const int P2C_BUFFER_SIZE ;
extern const int C2P_BUFFER_SIZE ;

//(4) appointment
int g_apNum;
struct SAppointment *g_appointmentArray; //assumption: not exceed the capacity

#endif //COMP2432_PROJECT_G02_G02_PROTOTYPE_H
