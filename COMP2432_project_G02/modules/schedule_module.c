//
// Created by 袁蕴宸 on 21/2/2023.
//
#include "../classes/scheduling.h"
#include "../main.h"
#include "../protocol/protocol.h"
#include "module.h"

static SCHEDULING_ALGORITHM interpretScheduleInstruction (char* instruction);
static void analyseSchedule (SCHEDULING_ALGORITHM algorithm);
static int rescheduling( int (*scheduleMatrix)[g_apNum],SAppointment* rescheduledAppointments);



//input: instruction
//output: go to txt file.
void scheduleModule (char* intstuction) {
    //(1) interpret instruction
    SCHEDULING_ALGORITHM algorithm = interpretScheduleInstruction(intstuction);

    if (algorithm == ALL) {
        int i;
        for (i = 0; i < SCHEDULING_ALGORITHM_COUNT; ++i) {
            analyseSchedule(SCHEDULING_ALGORITHM_ARRAY[i]);
        }
    } else {
        analyseSchedule(algorithm);
    }

}

//level 2
//--------------------------------------------------------------------------------------------------------------------------
//input: scheudle instruction string ( printSchd sssss / ALL)
//output: the schedule algorithm involved.
static SCHEDULING_ALGORITHM interpretScheduleInstruction (char* instruction) {
    return FCFS;
}
//--------------------------------------------------------------------------------------------------------------------------



static void analyseSchedule (SCHEDULING_ALGORITHM algorithm) {
    //(1) initialize
    int (*scheduleMatrix)[g_apNum] = calloc(g_userNum, sizeof *scheduleMatrix) ;

    //( 2) get the personal schedule
    int userIndex, rp, wp;
    int (*personalSchedule)[2];
    int numberOfSchedule;
    for (userIndex = 0; userIndex < g_userNum; ++userIndex) {
        //get the reply
        rp = g_c2p_fd[2*userIndex];
        wp = g_p2c_fd[2*userIndex + 1];
        numberOfSchedule = scheduleRequering_protocol_recipientAPI(algorithm, rp, wp, personalSchedule );  // the format of personalSchedule !

        //save to schedule matrix
        int apIndex, i,reply;
        for (apIndex = 0; apIndex < g_apNum; ++apIndex) { //record not inclued meeting
            scheduleMatrix[userIndex][apIndex] = -1;
        }
        for ( i =0; i < numberOfSchedule; ++i) {
            apIndex = personalSchedule[i][0];
            reply = personalSchedule[i][1];
            scheduleMatrix[userIndex][apIndex] = reply;
        }
    }

    //(3) rescheduling


    //(4) output:
    outputModule(g_userNum, g_apNum, scheduleMatrix,algorithm);


    //(5) free up
    free (scheduleMatrix);
}


//------------------------------------------------------------------------------------------------------------------------//--------------------------------------------------------------------------------------------------------------------------
//input:
// scheduleMatrix. -- initial reply from users. format:
////scheduleMatrix[userIndex][apIndex] = response
////
////        row:
////the index of user
////maximum length -- total number of users: g_userNum
////        column:
////the index of appointment
////maximum length -- total number of appointments: g_apNum
////        element:
////scheduleMatrix[i][j]: the response of user i to appointment j
////1 -- accecpt, 0 -- reject, -1 -- not included
//appoinment information array:  global variable -- g_apNum, g_appointmentArray

//output: rescheduledAppointments -- save the appointments to the  rescheduledAppointments (need malloc), return array size.
static int rescheduling( int (*scheduleMatrix)[g_apNum],SAppointment* rescheduledAppointments) {
    return 0;
}
//--------------------------------------------------------------------------------------------------------------------------
