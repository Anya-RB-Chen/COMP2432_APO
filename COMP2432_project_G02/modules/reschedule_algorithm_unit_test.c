//
// Created by 袁蕴宸 on 31/3/2023.
//

#include "modules.h"
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>

#include "../main.c"            //include the main function
#include "../classes/scheduling.c"
#include "../classes/appointment.c"
#include "../classes/time_type.c"
#include "appointment_module.c"
// #include "../protocol/protocol.h"
#include "../protocol/appointment_notification_protocol.c"

//
////tools
//static int getTimeSpan(STime startTime, STime endTime);
//static int getTimeIndex(STime startTime, STime time);
//static STime getTimeFromIndex (STime startTime, int timeIndex);
//static int getUserIndex (char* userName);
//
//
////save the time of appointment to schedule matrix.
//static void saveAppointmentTime (SAppointment appointment,int timeSize, int scheduleMatrix[][timeSize]);
//static int fitHole (int startTimeIndex, int duration, const int participantArray[],int timeSize, int scheduleMatrix[][timeSize]);
//
////
//
////boundary case: not valid -> all time = -1.
//int rescheduleALgorithm(const int apValidMap[],  SAppointment*  resApArray) {
//    //0, initlize DS: resApArray, scheduleMatrix, rejestApMatrix
//    //(1) get rejected appointment number.
//    int rejApNum = 0;
//    int i;
//    for (i = 0; i < g_apNum; ++i) {
//        if (apValidMap[i] == 0) {
//            rejApNum++;
//        }
//    }
//    //(2) initialize -- calloc have default initialization -> 0.
//    resApArray =  calloc(rejApNum ,sizeof (SAppointment)); // resArray contains new Appointment.
//
//    int (*rejectApMatrix)[g_userNum] = calloc(rejApNum, sizeof *rejectApMatrix); //rejectApMatrix[rejIndex][userIndex] -> 1 / 0 need to free up. // very dandrous
//
//    int timeSize = getTimeSpan(g_startTime, g_endTime);
//    int (*scheduleMatrix)[timeSize] = calloc(g_userNum, sizeof *scheduleMatrix);
//
//    //1, set scheduleMatrix & resApArray & rejectApMatrix
//    int rejectIndex = 0;
//    int apIndex;
//    for (apIndex = 0; apIndex < g_apNum; ++apIndex) {
//        if (apValidMap[apIndex] == 1) { //valid appointment -> save time to schedule matrix.
//            saveAppointmentTime(g_appointmentArray[apIndex], timeSize, scheduleMatrix);
//
//        } else { //rejected appointment.
//            //(1) save the appointment information to resApArray
//            resApArray[rejectIndex] = g_appointmentArray[apIndex];
//
//            //(2) save its users to rejectApMatrix.
//            int userIndex;
//            SAppointment* apPtr = &g_appointmentArray[apIndex];
//            userIndex = getUserIndex (apPtr -> caller);
//            rejectApMatrix[rejectIndex][userIndex] = 1;
//            for (i = 0; i < apPtr -> numberOfCallee; ++i) {
//                userIndex = getUserIndex ((apPtr -> callee)[i]);
//                rejectApMatrix[rejectIndex][userIndex] = 1;
//            }
//
//            rejectIndex++;
//        }
//    }
//
//    //2, fit.
//    // input:  scheduleMatrix ;  rejectApMatrix;
//    // output: reschedule, save new time to scheduleMatrix & resApArray.
//
//    //(1) reschedule:  output: start time.
//    for (rejectIndex = 0; rejectIndex < rejApNum; ++rejectIndex) {
//        //1' get appointment information
//        SAppointment* apPtr = resApArray + rejectIndex;
//        int startTimeIndex = getTimeIndex(g_startTime,apPtr -> startTime);
//        int duration = (int) apPtr -> duration;
//        int* participantArray = rejectApMatrix[rejectIndex]; //access ?
//
//
//        //2' rescheduling in two direction.
//        //(1) get newTimeIndex. (three properties)
//        int newTimeIndex = -1;
//
//        int span = 5 - duration; //max span
//        startTimeIndex = (startTimeIndex / 5 )  * 5; // go to start
//        int day = 0;
//        int find = 0, valid = 1;
//        while (find == 0 && valid == 1) {
//            int forward = startTimeIndex + 5 * day;
//            int backward = startTimeIndex - 5 * day;
//            for (i = 0; i < span; ++i) {
//                //not find
//                if ((backward < 0) && (forward >= timeSize)) {
//                    valid = 0;
//                }
//                if (backward >= 0) { //backwards
//                    if (fitHole(backward, duration, participantArray, timeSize, scheduleMatrix)) {
//                        newTimeIndex = backward;
//                        find = 1;
//                    }
//                }
//                if ((forward < timeSize) &&  (fitHole(forward, duration, participantArray, timeSize, scheduleMatrix))) {
//                    newTimeIndex = forward;
//                    find = 1;
//                }
//            }
//
//            backward++; forward++;
//        }
//
//        //(2) input: newTimeIndex (-1 1) ----output: save the result: -> scheduleMatrix,  resApArray
//        if (newTimeIndex == -1) {//invalid (fail to reschedule)
//            STime invalidTime;
//            invalidTime.year = invalidTime.day = invalidTime.hour = invalidTime.month = invalidTime.minute = 0;
//            resApArray[rejectIndex].startTime  = invalidTime; //boundary case.
//
//        } else { //valid
//            //1' res
//            resApArray[rejectIndex].startTime = getTimeFromIndex(g_startTime, newTimeIndex);
//            //2' schedule matrix
//            saveAppointmentTime (resApArray[rejectIndex],timeSize, scheduleMatrix);
//        }
//    }
//
//    //3, return and free up
//    free(rejectApMatrix);
//    free(scheduleMatrix);
//    return rejApNum;
//}
//
////------------------------------------------------------------------------------------------------------------------------//--------------------------------------------------------------------------------------------------------------------------
////tools function:
//
////1, time ~ timeIndex conversion function
//
////assumption: 1, the time period will only in one month; 2, one hour as unit time period 3, time slot from 18 to 23.
////time -> index
//static int getTimeIndex(STime startTime, STime time){
//    return (time.day - startTime.day) * 5 + (time.hour - 18);
//}
////reverse
//static STime getTimeFromIndex (STime startTime, int timeIndex) {
//    STime result = startTime;
//    int daySpan = timeIndex / 5;
//    int hour = timeIndex % 5 + 18;
//    result.day += daySpan;
//    result.hour = hour;
//    return result;
//}
//
//static int getTimeSpan(STime startTime, STime endTime) {
//    return (endTime.day - startTime.day + 1) * 5;
//}
//
////2, user index.
//char g_nameMap[10][50]; //array to store the user name.
//int g_userNum;
//static int getUserIndex (char* userName) {
//    int i;
//    for (i =0; i < g_userNum; ++i) {
//        if (strcmp(g_nameMap[i], userName) == 0) {
//            return i;
//        }
//    }
//    printf("outputModule-- rescheduleAlgorithm -- getUserIndex:  Error:The user not find.\n");
//    exit(1);
//}
//
//
////--------------------------------------------------------------------------------------------------------------------------
////subprocess: save the appointment time to schedule matrix.
////input: appointment (startTime, duration) -> output: schedulematrix set 1.
////assumption: The position is vacant. (0 at start).
////            the location is valid.
//
//static void saveAppointmentTime (SAppointment appointment,int timeSize, int scheduleMatrix[][timeSize]) {
//    int startTimeIndex = getTimeIndex(g_startTime, appointment.startTime);
//    int endTimeIndex = (int) appointment.duration + startTimeIndex;
//
//    int userIndex = getUserIndex(appointment.caller); //must have caller !
//    int timeIndex;
//    for (timeIndex = startTimeIndex; timeIndex < endTimeIndex; ++timeIndex) {
//        if (scheduleMatrix[userIndex][timeIndex] != 0) {
//            printf("reschedule algorithm -- saveAppointmentTime Error: the caller's location is not 0.\n");
//            printf("userIndex %d  timeIndex %d   element %d\n", userIndex, timeIndex, scheduleMatrix[userIndex][timeIndex]);
//            exit(1);
//        }
//        scheduleMatrix[userIndex][timeIndex]  = 1;
//    }
//
//    int i;
//    for (i = 0; i < appointment.numberOfCallee; ++i) {
//        userIndex = getUserIndex(appointment.callee[i]);
//        if (scheduleMatrix[userIndex][timeIndex] != 0) {
//            printf("reschedule algorithm -- saveAppointmentTime Error: the callee's location is not 0.\n");
//            printf("userIndex %d  timeIndex %d   element %d\n", userIndex, timeIndex, scheduleMatrix[userIndex][timeIndex]);
//            exit(1);
//        }
//        scheduleMatrix[userIndex][timeIndex]  = 1;
//    }
//}
//
////check whether can fit hole.
////input: appointment information -> output: fit or not.
////assumption: index in range.
//static int fitHole (int startTimeIndex, int duration, const int participantArray[],int timeSize, int scheduleMatrix[][timeSize]) {
//    int endTimeIndex = startTimeIndex + duration;
//    int userIndex, timeIndex;
//    for (userIndex = 0; userIndex < g_userNum; ++userIndex) {
//        if (participantArray[userIndex] == 1) {
//            for (timeIndex = startTimeIndex; timeIndex < endTimeIndex; ++timeIndex) {
//                if (scheduleMatrix[userIndex][timeIndex] == 1) {
//                    return 0;
//                }
//            }
//        }
//    }
//    return 1;
//}


//--------------------------------------------------------------------------------------------------------------------------
//unit test:




//--------------------------------------------------------------------------------------------------------------------------