//
// Created by 袁蕴宸 on 25/2/2023.
//

#include <stdlib.h>
#include <string.h>

#include "appointment.h"



AP_TYPE getAP_TYPE (int mode) {

    static const AP_TYPE apTypeArray[] = {PrivateTime, ProjectMeeting, GroupStudy, Gathering};
    return apTypeArray[mode];
} 


char* get_AP_TYPE_name (AP_TYPE type) {
    char* message;
    switch (type) {
        case PrivateTime:
            message =  "Private Time";
            break;
        case ProjectMeeting:
            message ="Project Meeting";
            break;
        case GroupStudy:
            message = "Group Study";
            break;
        case Gathering:
            message = "Gathering";
            break;
        default:
            message = "";
    }
    return message;
}

AP_TYPE getTypeByString(char *input){
    if (strcmp(input,"privateTime") == 0) return PrivateTime;
    else if (strcmp(input,"projectMeeting") == 0) return ProjectMeeting;
    else if (strcmp(input,"groupStudy") == 0) return GroupStudy;
    else return GroupStudy;
}