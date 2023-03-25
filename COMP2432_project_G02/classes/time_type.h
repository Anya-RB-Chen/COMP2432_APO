//
// Created by 袁蕴宸 on 19/2/2023.
//

#ifndef COMP2432_PROJECT_G02_TIME_TYPE_H
#define COMP2432_PROJECT_G02_TIME_TYPE_H

typedef struct STime {
//    char standardForm[]; //one choice
    int year, month, day;
//    float hour;
    int hour, minute;
} STime ;


//--------------------------------------------------------------------------------------------------------------------------
//methods to manipulate time
//input: 202304, 02
STime getTime (char* date, char* hour);

//input: format like "20230402"
STime getTimeFromStandardForm (char* str);

//input:
//output: [same] -> 0, [time1 before time2] -> -1, [later] -> 1.
int timeComparison (STime time1, STime time2);
//--------------------------------------------------------------------------------------------------------------------------


#endif //COMP2432_PROJECT_G02_TIME_TYPE_H


