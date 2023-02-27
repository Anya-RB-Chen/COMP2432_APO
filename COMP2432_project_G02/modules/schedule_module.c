//
// Created by 袁蕴宸 on 21/2/2023.
//
#include "../classes/scheduling.h"
#include "../main.h"
#include "../protocol/appointment_notification_protocol.h"
#include "../protocol/schedule_requiring_protocol.h"
#include "output_module.h"

static enum SCHEDULING_ALGORITHM interpretScheduleInstruction (char* instruction);
static void analysisScheduleMatrix (int** scheduleMatrix, int userNum, int apNum, enum SCHEDULING_ALGORITHM);

void scheduleModule (char* intstuction) {
    //(1) interpret instruction
    enum SCHEDULING_ALGORITHM algorithm = interpretScheduleInstruction(intstuction);
    if (algorithm == ALL) {
        //...
    }

    //(2) get the personal schedule of users -- matrix
    //1' initialize
    int** scheduleMatrix ; //format: ...
    //2' get the personal schedule
    int userIndex, rp, wp;
    int** personalSchedule;
    int numberOfSchedule;
    for (userIndex = 0; userIndex < g_userNum; ++userIndex) {
        rp = g_c2p_fd[2*userIndex];
        wp = g_p2c_fd[2*userIndex + 1];
        numberOfSchedule = scheduleRequering_protocol_recipientAPI(algorithm,rp, wp, personalSchedule );
        //save to matrix
        //...
    }

    //(3) output:
    outputModule(scheduleMatrix,algorithm);


    //(4) rescheduling.
    //...
}

//level 2
static enum SCHEDULING_ALGORITHM interpretScheduleInstruction (char* instruction) {
    return FCFS;
}

