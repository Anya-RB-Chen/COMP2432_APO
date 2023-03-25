//
// Created by 袁蕴宸 on 25/3/2023.
//

#ifndef COMP2432_APO_PROTOCOL_H
#define COMP2432_APO_PROTOCOL_H

#include "../classes/appointment.h"
#include "../classes/scheduling.h"


//--------------------------------------------------------------------------------------------------------------------------
//1, appointment Notification protocol

extern const int APPOINTMENT_NOTIFICATION_PROTOCOL_PORT_NUMBER;

void  appointmentNotification_protocol_API_(SAppointment ap,  int wp);
//新加的接口：
//输入： read pointer (read pointer 指向的pipe 队列头为request message （不含port number) ）
//输出： Scard
//process : read,  decoding, return.
SCard appointmentNotification_protocol_interpret_request (int rp)


//2, schudule requring protocol
extern const int SCHEDULE_REQUERING_PROTOCOL_PORT_NUMBER;

//server API
//------------------------------------------------------------------------------------------------------------------------//--------------------------------------------------------------------------------------------------------------------------
//original
//void  scheduleRequering_protocol_serverAPI(char* requestMessage, int wp, SAppointment ap_array[], int arraySize);

//now
//input： read pointer.
//output： 用 rp 读取出 request message， 解码后返回scheduling算法。
//boundary case: 无法识别算法 -> 返回ALL。
SCHEDULING_ALGORITHM scheduleRequering_protocol_interpret_request (int rp);

//input: schedule map (length * 2 array)  ， write pointer.
//output: 通过wp， 把schedule map 写给parent。  和下面的 scheduleRequering_protocol_recipientAPI 统一起来
void scheduleRequering_protocol_deliverScheduleMap (int scheduleMap[][2], int length, int wp);


//recipient API
//------------------------------------------------------------------------------------------------------------------------//--------------------------------------------------------------------------------------------------------------------------
//original:
//return value: 2d array
//int**  scheduleRequering_protocol_recipientAPI(SCHEDULING_ALGORITHM algorithm, int rp, int wp);

//new:
//return value: length of array,   + write the content of array to personalSchedule
int  scheduleRequering_protocol_recipientAPI(SCHEDULING_ALGORITHM algorithm, int rp, int wp,int (*personalSchedule)[2]);
//--------------------------------------------------------------------------------------------------------------------------



#endif //COMP2432_APO_PROTOCOL_H
