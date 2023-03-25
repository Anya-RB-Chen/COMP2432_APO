//
// Created by 袁蕴宸 on 25/3/2023.
//


#include "classes/appointment.h"
#include "classes/scheduling.h"
#include "classes/time_type.h"

//main module function
//--------------------------------------------------------------------------------------------------------------------------
//input: instruction string
//output: [endProgram] -> 0,  [appointment instruction] -> 1,  [printSchd] -> 2
//       boudary case: invalid format -> -1
static int getInstructionMode (char* instruction) {
    return 0;
}
//--------------------------------------------------------------------------------------------------------------------------


//--------------------------------------------------------------------------------------------------------------------------
//input: scheudle instruction string ( printSchd sssss / ALL)
//output: the schedule algorithm involved.
static SCHEDULING_ALGORITHM interpretScheduleInstruction (char* instruction) {
    return FCFS;
}
//--------------------------------------------------------------------------------------------------------------------------


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



//------------------------------------------------------------------------------------------------------------------------//--------------------------------------------------------------------------------------------------------------------------
//time type

//methods to manipulate time
//input: 202304, 02
STime getTime (char* date, char* hour);

//input: format like "20230402"
STime getTimeFromStandardForm (char* str);

//input:
//output: [same] -> 0, [time1 before time2] -> -1, [later] -> 1.
int timeComparison (STime time1, STime time2);
//--------------------------------------------------------------------------------------------------------------------------


 //--------------------------------------------------------------------------------------------------------------------------
//scheduling algorithm.
//output format: 2d array:  2 * arraySize
//row 1: appointment index
//row 2: accept 1 / reject 0
void FCFS_schedule_algorithm (SAppointment ap_array[],  int arraySize, int (*schduleMap)[2] );
void Priority_schedule_algorithm (SAppointment ap_array[],  int arraySize, int (*schduleMap)[2] );
void SRT_schedule_algorithm (SAppointment ap_array[],  int arraySize, int (*schduleMap)[2] );
//--------------------------------------------------------------------------------------------------------------------------
