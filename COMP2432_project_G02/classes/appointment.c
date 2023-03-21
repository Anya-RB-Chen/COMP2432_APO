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
    char* result = (char*) (malloc((sizeof(char) *(strlen(message) + 1))));
    strcpy(result, message);
    return result;
}