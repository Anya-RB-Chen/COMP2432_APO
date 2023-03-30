//
// Created by 袁蕴宸 on 25/3/2023.
//

#ifndef COMP2432_APO_PROTOCOL_H
#define COMP2432_APO_PROTOCOL_H

//#include "../classes/appointment.h"
//#include "../classes/scheduling.h"
//#include "../../G02_prototype/classes/appointment.h"
#include "../main.h"

//--------------------------------------------------------------------------------------------------------------------------
//1, appointment Notification protocol

void  appointmentNotification_protocol_API_(SAppointment ap,  int wp);

//新加的接口：
//输入： read pointer (read pointer 指向的pipe 队列头为request message （不含port number) ）
//输出： SAppointment
//process : read,  decoding, return.
SAppointment appointmentNotification_protocol_interpret_request (int rp);


//2, schudule requring protocol

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
void scheduleRequering_protocol_deliverScheduleMap (int **scheduleMap, int length, int wp);
//schedule map encode完了之后把message写给parent
//

//recipient API
//------------------------------------------------------------------------------------------------------------------------//--------------------------------------------------------------------------------------------------------------------------
//original:
//return value: 2d array
//int**  scheduleRequering_protocol_recipientAPI(SCHEDULING_ALGORITHM algorithm, int rp, int wp);

//new:
//return value: length of array,   + write the content of array to personalSchedule
int  scheduleRequering_protocol_recipientAPI(SCHEDULING_ALGORITHM algorithm, int rp, int wp,int **personalSchedule);
//--------------------------------------------------------------------------------------------------------------------------
// 先把algorithm写给child，等child传回来schedule信息之后decode，二维数组写给指针，长度作为返回值返回
// 保证上层函数能访问到数组长度（schedule的数量）

// 上层函数对schedule map的定义：
// let k be a large number
//int ** test = (int **) malloc(sizeof(int **) * 2);
//test[0] = (int *) malloc(sizeof (int *)*k);
//test[1] = (int *) malloc(sizeof (int *)*k);

// free (test)


#endif //COMP2432_APO_PROTOCOL_H
