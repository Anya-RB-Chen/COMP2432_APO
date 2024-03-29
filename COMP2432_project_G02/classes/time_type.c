//
// Created by 袁蕴宸 on 19/2/2023.
//

#include "time_type.h"


char* int2String(int num,char *str)
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

STime getTime (char* date, char* hour){
    STime a;
    int date_i = atol(date);
    int hour_i = atol(hour);
    int year = date_i/10000;
    int month = date_i/100%100;
//    printf("%d\n", month);
    int day = date_i%100;
    int hour_in = hour_i/100%100;
    int min = hour_i%100;
    a.year = year;
    a.month = month;
    a.day = day;
    a.hour = hour_in;
    a.minute = min;
    return a;
}

STime getTimeFromStandardForm (char* str){
    STime a;
    int input_num = atol(str);
    char year_c[5], month_c[3], day_c[3], hour_c[3], min_c[3];
    int len = sizeof(*str)/ sizeof(str[0]);

    //year
    for(int i = 0; i < 4; i++){
        if(str[i] == '\0') break;
        year_c[i] = str[i];
    }
    int year = atol(year_c);

    //month
    for(int i = 0; i < 2; i++){
        if(str[i] == '\0') break;
        month_c[i] = str[i+4];
    }
    int month = atol(month_c);

    //day
    for(int i = 0; i < 2; i++){
        if(str[i] == '\0') break;
        day_c[i] = str[i+6];
    }
    int day = atol(day_c);

    //hour
    for(int i = 0; i < 2; i++){
        if(str[i] == '\0') break;
        hour_c[i] = str[i+8];
    }
    int hour = atol(hour_c);

    //minute
    for(int i = 0; i < 2; i++){
        if(str[i] == '\0') break;
        min_c[i] = str[i+10];
    }
    int min = atol(min_c);

    a.year = year;
    a.month = month;
    a.day = day;
    a.hour = hour;
    a.minute = min;
    return a;
}

int timeComparison (STime time1, STime time2){
    //year
    if(time1.year!= '\0'&&time2.year!= '\0'){
        if(time1.year != time2.year){
            return time1.year > time2.year ? 1 : -1;
        }
    }
    //month
    if(time1.month!= '\0' &&time2.month!= '\0'){
        if(time1.month != time2.month){
            return time1.month > time2.month ? 1 : -1;
        }
    }
    //day
    if(time1.day!= '\0' &&time2.day!= '\0'){
        if(time1.day != time2.day){
            return time1.day > time2.day ? 1 : -1;
        }
    }
    //hour
    if(time1.hour!= '\0' &&time2.hour!='\0'){
        if(time1.hour != time2.hour){
            return time1.hour > time2.hour ? 1 : -1;
        }
    }
    //minute
    if(time1.minute!= '\0' &&time2.minute!= '\0'){
        if(time1.minute != time2.minute){
            return time1.minute > time2.minute ? 1 : -1;
        }
    }
    return 0;
}

char* dateToString(STime time){
    // Used for the output module
    char* str = (char*)calloc(20, sizeof(char));
    char year_c[5], month_c[3], day_c[3];
    sprintf(year_c, "%d", time.year);
    sprintf(month_c, "%d", time.month);
    sprintf(day_c, "%d", time.day);

    strcat(str, "20");
    strcat(str, year_c);
    strcat(str, "-");
    if (time.month < 10) strcat(str, "0");
    strcat(str, month_c);
    strcat(str, "-");
    if (time.day < 10) strcat(str, "0");
    strcat(str, day_c);

    return str;
}

char* timeToString(STime time){
    // Used for the output module
    char *res = (char*)malloc(sizeof (char )*6);
    char buf[3];
    char *hour = int2String(time.hour,buf);
    strcat(res,hour);
    strcat(res,":00");
    printf("inside function %s\n",res);
    return res;
}
