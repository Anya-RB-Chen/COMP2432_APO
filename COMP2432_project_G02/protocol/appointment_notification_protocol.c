//
// Created by 袁蕴宸 on 21/2/2023.
//

#include <stdio.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "appointment_notification_protocol.h"
#include "../classes/scheduling.h"

const int APPOINTMENT_NOTIFICATION_PROTOCOL_REQUEST_MESSAGE_MAXIMUM_LENGTH = 800;

char* Int2String(int num,char *str)
{
    int i = 0;
    do
    {
        str[i++] = num%10+48;
        num /= 10;
    }while(num);
    str[i] = '\0';
    int j = 0;
    for(;j<i/2;j++)
    {
        str[j] = str[j] + str[i-1-j];
        str[i-1-j] = str[j] - str[i-1-j];
        str[j] = str[j] - str[i-1-j];
    }
    return str;
}

//level 1: application layer API
//deliver the appointment message to user process.
char *appointmentNotification_protocol_requestMessage_encoding(SAppointment ap) {
    // Assumption: each field of appointment won't be null. If type is privateTime which only includes caller,
    // we have to assign callee a value. eg: "0";
    int i;
    static char res[100] = "|";
    char buffer[10];
    char *seperate = "|";
    char *sepCallee = "&";
    char *none = "@";
    char *type = Int2String(ap.type,buffer);
    strcat(res,type);
    strcat(res,seperate);
    char *year = Int2String(ap.startTime.year,buffer);
    strcat(res,year);
    strcat(res,seperate);
    char *month = Int2String(ap.startTime.month,buffer);
    strcat(res,month);
    strcat(res,seperate);
    char *date = Int2String(ap.startTime.day,buffer);
    strcat(res,date);
    strcat(res,seperate);
    char *hour = Int2String(ap.startTime.hour,buffer);
    strcat(res,hour);
    strcat(res,seperate);
    char *minute = Int2String(ap.startTime.minute,buffer);
    strcat(res,minute);
    strcat(res,seperate);
    char dura[10];
    sprintf(dura,"%.1f",ap.duration);
    strcat(res,dura);
    strcat(res,seperate);
    char *caller = ap.caller;
    strcat(res,caller);
    strcat(res,seperate);
    char *idx = Int2String(ap.apIndex,buffer);
    strcat(res,idx);
    strcat(res,seperate);
    for(i = 0; i<ap.numberOfCallee; i++){
        strcat(res,ap.callee[i]);
        strcat(res,sepCallee);
    }
    strcat(res,seperate);
    char *numCallee = Int2String(ap.numberOfCallee,buffer);
    strcat(res,numCallee);
    strcat(res,seperate);
    return res;
}


SAppointment *appointmentNotification_protocol_requestMessage_decoding(char *message) {
    SAppointment *a = (SAppointment*) malloc(sizeof (SAppointment));
    int i = 1, j = 0, k;
    a->type = message[i] - 48;
    i += 2;
    char year[10];
    while (message[i] != '|'){
        year[j] = message[i];
        i++;
        j++;
    }
    j = 0;
    i++;
    a->startTime.year = atoi(year);
    printf("%d\n",a->startTime.year);

    // get month
    char month[2];
    while (message[i] != '|'){
        month[j] = message[i];
        i++;
        j++;
    }
    char res[j];
    for (k = 0; k<j; k++) res[k] = month[k];
    j = 0;
    i++;
    a->startTime.month = atoi(res);


    // get date
    char day[2];
    while (message[i] != '|'){
        day[j] = message[i];
        i++;
        j++;
    }
    char res1[j];
    for (k = 0; k<j; k++) res1[k] = day[k];
    j = 0;
    i++;
    a->startTime.day = atoi(res1);

    // get start hour
    char hour[2];
    while (message[i] != '|'){
        hour[j] = message[i];
        i++;
        j++;
    }
    char res2[j];
    for (k = 0; k<j; k++) res2[k] = hour[k];
    j = 0;
    i++;
    a->startTime.hour = atoi(res2);

    // get start minute
    char minute[2];
    while (message[i] != '|'){
        minute[j] = message[i];
        i++;
        j++;
    }
    char res3[j];
    for (k = 0; k<j; k++) res3[k] = minute[k];
    j = 0;
    i++;
    a->startTime.minute = atoi(res3);


    // get duration
    char dura[10];
    while (message[i] != '|'){
        dura[j] = message[i];
        i++;
        j++;
    }
    j = 0;
    i++;
    a->duration = atof(dura);


    // get caller
    char caller[10];
    int m;
    for (m = 0; m<10; m++){
        caller[m] = '\0';
    }
    while (message[i] != '|'){
        caller[j] = message[i];
        i++;
        j++;
    }
    printf("%s\n",caller);
    strcpy(a->caller,caller);
    printf("%s\n",a->caller);
    j = 0;
    i++;


    // get appointment index
    char idx[3];
    while (message[i] != '|'){
        idx[j] = message[i];
        i++;
        j++;
    }
    j = 0;
    i++;
    a->apIndex = atoi(idx);

    char temp[10];
    for (m = 0; m<10; m++){
        temp[m] = '\0';
    }
    while (message[i] != '|'){
        k = 0;
        while (message[i] != '&'){
            temp[k] = message[i];
            i++;
            k++;
        }
        i++;
        strcpy(a->callee[j],temp);
        printf("%s\n",a->callee[j]);
        for (m = k-1; m<10; m++){
            temp[m] = '\0';
        }
        j++;
    }
    a->numberOfCallee = j;

    return a;
}


void  appointmentNotification_protocol_API_(SAppointment ap,  int wp) {
    char* msg = appointmentNotification_protocol_requestMessage_encoding(ap);
    write(wp,msg,sizeof (msg));
}
