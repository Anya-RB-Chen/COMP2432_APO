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
static void notifyUsersAboutAP1 (struct SAppointment appointment);
static int get_p2cWritePointer_by_name (char* name);


//level 1
//input: appointment type instruction (not ensure the validity)
//output: interpret the instruction and do the corresponding operation

void appointmentModule (char* instruction) {
    //1, interpret the appointment instruction

    SAppointment appointment = interpretAppointmentInstruction(instruction);
    appointment.apIndex = g_apNum;

//// only for testing, 最后删掉
//    SAppointment appointment;
//    appointment.startTime.year = 2023;
//    appointment.startTime.month = 4;
//    appointment.startTime.day = 2;
//    appointment.startTime.hour = 19;
//    appointment.startTime.minute = 0;
//    appointment.duration = 2.0f;
//    strcpy(appointment.caller,"john");
//    strcpy(appointment.callee[0],"paul");
//    strcpy(appointment.callee[1],"mary");
//    appointment.numberOfCallee = 2;
//    appointment.apIndex = 1;
//    appointment.type = ProjectMeeting;

    g_appointmentArray[g_apNum++] = appointment;  //! problem: apo save appointment information.
    printf("current apNum %d\n",g_apNum);

   //2,  notify the users about the appointment
    // notify all the caller a& callee
    //1' caller
    int  writePtr_to_caller = get_p2cWritePointer_by_name(appointment.caller);
    if (writePtr_to_caller != -1) {
        appointmentNotification_protocol_API_(appointment,  writePtr_to_caller);
    }
    //2' callee
    int i;
    for (i = 0; i < appointment.numberOfCallee; i++) {
        char callee[15];// dangerous
        strcpy(callee,appointment.callee[i]);
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
SAppointment interpretAppointmentInstruction (char* instruction) {

    SAppointment a;
    int len = strlen(instruction);
    int i;
    //find the length of the type
    int count = 0;
    for(i =0; i < len; i ++){
        if(instruction[i] == ' ') break;
        count++;
    }

    //copy and store
    char type[count+1];
    for (i = 0; i<count+1; i++) type[i] = '\0';
    for(i = 0; i < count;i++){
        type[i] = instruction[i];
    }
    printf("type %s",type);
    int mode = getInstructionMode(type);
    a.type = getAP_TYPE(mode);


    //get the name of the caller
    count++;
    for (i = 0; i < len;i++){
        if(instruction[count] == ' '){
            break;
        }
        a.caller[i] = instruction[count];
        count++; // move the pointer
    }

    //get two time
    char date[9], hour[5];
    count++;//the pointer for all storage
    //get the date
    for(i = 0; i < len; i++){
        if(instruction[count] == ' '){
            break;
        }
        date[i] = instruction[count];
        count++; // move the pointer
    }

    //get the hour
    count++;
    for(i = 0; i < len; i++){
        if(instruction[count] == ' '){
            break;
        }
        hour[i] = instruction[count];
        count++; // move the pointer
    }

    a.startTime = getTime(date, hour);

    //get the duration
    count++;
    float duration;
    char duration_trans[3];
    for(i = 0; i < len; i++){
        if(instruction[count] == ' '){
            break;
        }
        duration_trans[i] = instruction[count];
        count++; // move the pointer
    }
    duration = atol(duration_trans);
    a.duration = duration;


    //calculate the end time
    a.endTime = a.startTime;
    //judge whether there is a half
    if(atol(duration_trans) != atoi(duration_trans)){
        //yes, there is a 0.5
        a.endTime.minute += 30;
        if(a.endTime.minute >= 60) a.endTime.minute -= 60;
        a.endTime.hour += 1;
    }

    //add the hours
    a.endTime.hour += atoi(duration_trans);

    count++;
    //get the callee
    int num = 0; // for several callees
    if(count == len-1){
        //do not have the callee
        return a;
    }
    else{
        //do have the callee
        char temp[15];
        int m;
        for (m = 0; m<15; m++) temp[m] = '\0';
        int k;
        while (count<len) {
            k = 0;
            while (instruction[count] != ' ' && instruction[count] != '\0') {
                temp[k] = instruction[count];
                count++;
                k++;
            }
            strcpy(a.callee[num],temp);
            num++;
            count++;
        }
    }

    //calculate the number of the callees
    if(num == 0){
        //special case that have one callee or not
        if(a.callee[0][0] == '\0') a.numberOfCallee = 0;
        else  a.numberOfCallee = num;
    }
    else a.numberOfCallee = num;

    printf("caller %s, year %d, mon %d, duration %f, idx %d\n", a.caller,a.startTime.year, a.startTime.month,
           a.duration, a.apIndex);

    return a;
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
