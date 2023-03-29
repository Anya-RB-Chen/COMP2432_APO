//
// Created by 袁蕴宸 on 20/2/2023.
//

#include "scheduling.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

SCHEDULING_ALGORITHM getSCHEDULING_ALGORITHM (int mode) {
    static const int SCHEDULING_ALGORITHM_COUNT = 2;
    static const SCHEDULING_ALGORITHM SCHEDULING_ALGORITHM_ARRAY[] = {FCFS, Priority,SRT};
    return SCHEDULING_ALGORITHM_ARRAY[mode];
}

char* get_SchedingAlgorithm_name (SCHEDULING_ALGORITHM algorithm) {
    char* message;
    switch (algorithm) {
        case FCFS:
//            return "FCFS"; //?
             message = "FCFS";
             break;
        case Priority:
            message = "Priority";
            break;
        case SRT:
            message = "SRT";
            break;
        default:
            message = "";
    }
    char* result = (char*) (malloc((sizeof(char) *(strlen(message) + 1))));
    strcpy(result, message);
    return result;
}


int ifOverLap(SAppointment ap1, SAppointment ap2){ // return 1 if overlap
    if (ap1.apIndex != ap2.apIndex){
        if (timeComparison(ap1.startTime,ap2.startTime) == 1 &&
            timeComparison(ap2.startTime,ap1.endTime) == 1)
            return 1;
        if (timeComparison(ap2.startTime,ap1.startTime) == 1 &&
            timeComparison(ap1.startTime,ap2.endTime) == 1)
            return 1;
    }
    return 0;
}

void sort_by_startTime(SAppointment appointment[], int size){
    int i,j;
    for (i = 0; i<size-1; i++){
        for (j = 0; j<size-i-1; j++){
            if (timeComparison(appointment[j].startTime,appointment[j+1].startTime) == 1){
                SAppointment temp = appointment[j];
                appointment[j] = appointment[j+1];
                appointment[j+1] = temp;
            }
        }
    }
}

// 按start time(arrival time)排序，若有overlap则reject后来者
void FCFS_schedule_algorithm (SAppointment ap_array[],  int arraySize, int **schduleMap){
    sort_by_startTime(ap_array,arraySize);
    int i = 1, current = 1;
    schduleMap[0][0] = ap_array[0].apIndex;
    schduleMap[1][0] = 1;
    while (i<arraySize){
        if (ifOverLap(ap_array[i],ap_array[current]) == 1){ // overlap
            schduleMap[0][i] = ap_array[i].apIndex;
            schduleMap[1][i] = 0;
            i++;
        } else{ // no overlap
            schduleMap[0][i] = ap_array[i].apIndex;
            schduleMap[1][i] = 1;
            i++;
            current++;
        }
    }
}

// 按start time(arrive time)排序，若有overlap, 则执行priority大的
void Priority_schedule_algorithm (SAppointment ap_array[],  int arraySize, int **schduleMap ){
    sort_by_startTime(ap_array,arraySize);
    int i = 1, current = 0;
    schduleMap[0][0] = ap_array[0].apIndex;
    schduleMap[1][0] = 1;
    while (i<arraySize){
        if (ifOverLap(ap_array[i],ap_array[current]) == 1){
            if (ap_array[current].type<ap_array[i].type){ // current has priority
                schduleMap[0][i] = ap_array[i].apIndex;
                schduleMap[1][i] = 0;
                i++;
            } else{ // i has priority
                schduleMap[1][current] = 0; // change current state
                current = i; // update current
                schduleMap[0][i] = ap_array[i].apIndex;
                schduleMap[1][i] = 1; // accept i
                i++;
            }
        } else{
            schduleMap[0][i] = ap_array[i].apIndex;
            schduleMap[1][i] = 1;
            i++;
            current++;
        }
    }
}

void SRT_schedule_algorithm (SAppointment ap_array[],  int arraySize, int **schduleMap ){
    sort_by_startTime(ap_array,arraySize);
    int i = 1, current = 0;
    schduleMap[0][0] = ap_array[0].apIndex;
    schduleMap[1][0] = 1;
    while (i<arraySize){
        if (ifOverLap(ap_array[i],ap_array[current]) == 1){
            if (ap_array[current].duration<ap_array[i].duration){ // current has shorter duration
                schduleMap[0][i] = ap_array[i].apIndex;
                schduleMap[1][i] = 0;
                i++;
            } else{ // i has shorter duration
                schduleMap[1][current] = 0;
                current = i; // update current
                schduleMap[0][i] = ap_array[i].apIndex;
                schduleMap[1][i] = 1; // accept i
                i++;
            }
        } else{
            schduleMap[0][i] = ap_array[i].apIndex;
            schduleMap[1][i] = 1;
            i++;
            current++;
        }
    }
}
