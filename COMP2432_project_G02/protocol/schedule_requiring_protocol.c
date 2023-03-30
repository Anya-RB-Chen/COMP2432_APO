//
// Created by 袁蕴宸 on 25/2/2023.
//

#include <stdio.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#include "protocol.h"
#include "appointment_notification_protocol.c"

const int SCHHEDULE_REQUERING_PROTOCOL_REQUEST_MESSAGE_MAXIMUM_LENGTH = 800 ;
const int SCHEDULE_REQUERING_PROTOCOL_RESPONSE_MESSAGE_MAXIMUM_LENGTH  = 800;

void scheduleRequering_protocol_requestMessage_encoding(SCHEDULING_ALGORITHM algorithm, char* dst);

SCHEDULING_ALGORITHM scheduleRequering_protocol_requestMessage_decoding(char *message);

//level 1: application layer API
//recipient:  parent process / APO
//server: child process / user

SCHEDULING_ALGORITHM scheduleRequering_protocol_interpret_request (int rp){
    char buffer[4];
    int n;
    n = read(rp,buffer,3);
//    printf("%c%c%c\n", buffer[0], buffer[1], buffer[2]);
    if (strcmp(buffer,"FCF") == 0) {
        return FCFS;
    } else if (strcmp(buffer,"PRI") == 0){
        return Priority;
    } else if (strcmp(buffer,"SRT") == 0){
        return SRT;
    }
    return ALL;
}



//level 2: presentation layer interface
void  scheduleRequering_protocol_requestMessage_encoding(SCHEDULING_ALGORITHM algorithm, char* dst) {
    if (algorithm == FCFS) {
        strcpy(dst,"FCF");
    } else if (algorithm == Priority){
        strcpy(dst,"PRI");
    } else if (algorithm == SRT){
        strcpy(dst,"SRT");
    } else if (algorithm == ALL){
        strcpy(dst,"ALL");
    }
}


SCHEDULING_ALGORITHM scheduleRequering_protocol_requestMessage_decoding(char *message) {
    if (strcmp(message,"FCF") == 0) {
        return FCFS;
    } else if (strcmp(message,"PRI") == 0){
        return Priority;
    } else if (strcmp(message,"SRT") == 0){
        return SRT;
    }
    return ALL;
}



void scheduleRequering_protocol_deliverScheduleMap (int **scheduleMap, int scheduleNum, int wp){
    //schedule map encode完了之后把message写给parent，加上port number和length of schedule map
    int i, j;
    char encode[256] = "|";
    char *seperate = "|";
    char buffer[10];
//    // add port number
//    strcpy(encode,"2");
 //   strcat(encode,seperate);
    // add schedule number(length of array)
    char *len = Int2String(scheduleNum,buffer);
    strcat(encode,len);
    strcat(encode,seperate);

    // encode the personal schedule
    // encode format: port_number|num_of_schedule|schedule i|acceptance i
    for (i = 0; i<2; i++) {
        for (j = 0; j < scheduleNum; j++){
            char *temp = Int2String(scheduleMap[i][j],buffer);
            strcat(encode,temp);
            strcat(encode,seperate);
        }
    }
    // pass message to parent
    write(wp,encode, strlen(encode));

}


int  scheduleRequering_protocol_recipientAPI(SCHEDULING_ALGORITHM algorithm, int rp, int wp,int **schedule){



    // 先把algorithm写给child，等child传回来schedule信息之后decode，二维数组写给指针，长度作为返回值返回
    // 保证上层函数能访问到数组长度（schedule的数量）
    // write schedule algotithm to child
    char scheduAlgo[4];
    scheduleRequering_protocol_requestMessage_encoding(algorithm,scheduAlgo);
    write(wp,scheduAlgo,3);

    // read port number
//    char port_buffer[1];
//    int n = read(rp,port_buffer,1);
//    int port = atoi(port_buffer);
//    printf("pid %d, recipient read port %s\n",getpid(),port_buffer);
    int n;
    // read the message passed by child;
    char message[256];
    n = read(rp,message,256);

    // decode the message passed by child
    // decode the number of schedules
    int i = 1, j, k = 0, m, scheduleNum;
    char temp[5] = "\0";
    while (message[i] != '|'){
        temp[k] = message[i];
        i++;
        k++;
    }
    int res = atoi(temp);
    scheduleNum = res;
    k = 0;
    i++;

    // write the schedule back to schedule
    // appointment index
    for (j = 0; j<scheduleNum; j++){
        char temp[5] = "\0";
        while (message[i] != '|'){
            temp[k] = message[i];
            i++;
            k++;
        }
        int res = atoi(temp);
        schedule[0][j] = res;
        k = 0;
        i++;
    }
    // decision
    for (j = 0; j<scheduleNum; j++){
        while (message[i] != '|'){
            schedule[1][j] = message[i] - 48;
            i++;
        }
        i++;
    }

    // return the schedule number
    return scheduleNum;
}
