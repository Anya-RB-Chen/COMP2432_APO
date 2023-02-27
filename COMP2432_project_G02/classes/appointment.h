//
// Created by 袁蕴宸 on 19/2/2023.
//

#ifndef COMP2432_PROJECT_G02_APPOINTMENT_H
#define COMP2432_PROJECT_G02_APPOINTMENT_H

#include "time_type.h"

enum AP_TYPE {
    PrivateTime = 0, ProjectMeeting = 1, GroupStudy = 2, Gathering = 3//... descending order by priority.
};

enum AP_TYPE getAP_TYPE (int mode);
char* get_AP_TYPE_name (enum AP_TYPE type);

struct SAppointment {
    enum AP_TYPE type;
    struct STime startTime, endTime;
    float duration; //0.5
    int apIndex;
    char* caller;
    char** callee;
    int numberOfCallee;
};



#endif //COMP2432_PROJECT_G02_APPOINTMENT_H


