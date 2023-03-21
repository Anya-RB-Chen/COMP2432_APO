////
//// Created by 袁蕴宸 on 21/2/2023.
////
//
//#include <stdio.h>
//#include <stdlib.h>
//#include <unistd.h>
//#include <sys/wait.h>
//#include <string.h>
//
//
//
////multiple usage pipe
////service: distributed arithmatic computation.
////protocol: message length: 12 byte 1' mode 2' num1 3, num2
//
//
//
//enum OPERATION {
//    ADDITION  = (int)0, SUBSTRACTION =(int) 1, MULTIPLICATION =(int) 2, DIVISION =(int) 3
//};
//static enum OPERATION getOperation (int mode) {
//    static enum OPERATION array[] = {ADDITION, SUBSTRACTION, MULTIPLICATION, DIVISION};
//    return array[mode];
//}
//
////tool method.
//static int little_endian_decoding(char* src);
//static void little_endian_encoding (int num, char* dst);
//
////arithmetic operation service / protocol
////level 1: application layer API
//static int arithematicOperation_protocol_recipientAPI_calculation (enum OPERATION op, int num1, int num2, int rp,  int wp);
//static void arithematicOperation_protocol_serverAPI (int rp, int wp);
//static const int ARITHMETIC_OPERATION_PROTOCOL_REQUEST_MESSAGE_MAXIMUM_LENGTH = 12 + 1;
//static const int ARITHMETIC_OPERATION_PROTOCOL_RESPONSE_MESSAGE_MAXIMUM_LENGTH = 4 + 1;
//
////static void arithematicOperation_protocol_serverAPI_calculation (int rp,  int wp) ;
////static void arithematicOperation_protocol_serverAPI_calculation (enum OPERATION op, int num1, int num2, int rp,  int wp)
////level 2: presentation layer interface
//static char* arithematicOperation_protocol_requestMessage_encoding (enum OPERATION operation, int num1, int num2) ;
//static int* arithematicOperation_protocol_requestMessage_decoding (char* message) ;
//static char* arithematicOperation_protocol_responseMessage_encoding(int num) ;
//static int arithematicOperation_protocol_responseMessage_decoding (char* message) ;
//
////level 0: application program: recipient & server
//int main() {
//    //level -1: process & pipe.
//    int p2c_fd[2];
//    int c2p_fd[2];
//    pipe(p2c_fd);
//    pipe(c2p_fd);
//
//    if (fork() == 0) {
//        close(p2c_fd[1]);
//        close (c2p_fd[0]);
////--------------------------------------------------------------------------------------------------------------------------
//
//        //2, server            (of arithmetic operation protocol)
//        //storage: local memory
//        //process: logic of server program: 0, 1,receive message , 2,provide related service. -- invoke application protocol server API
//        //storage
//        int serviceCount = 0;
//        int localStorage[10];
//        //logic
//        printf("server initializes.\n");
//        //....
//        int port = 1;
//        switch (port) {
//            case 1:
//                arithematicOperation_protocol_serverAPI(p2c_fd[0], c2p_fd[1]);
//                //...
//                break;
//            default:
//                printf("Unknown protocol.\n");
//        }
//        //--------------------------------------------------------------------------------------------------------------------------
//
//        exit(0);
//    }
//
//    close(p2c_fd[0]);
//    close(c2p_fd[1]);
////--------------------------------------------------------------------------------------------------------------------------
//
//    // 1, recipient             (of arithmetic operation protocol)
//    //storage: ...
//    //process: logic of application program  -- need internet service:  invoke application protocol recipient API.
//
//
//    //level 0: application program
//    //program logic: get number -- give calculation result
//    enum OPERATION op;
//    int mode, num1, num2;
//    printf("Enter the mode, num1, num2\n");
//    scanf("%d%d%d", &mode, &num1, &num2);
//
//    op = getOperation(mode);
//    int result = arithematicOperation_protocol_recipientAPI_calculation(op, num1, num2, c2p_fd[0], p2c_fd[1] );
//
//    printf("The result is %d\n", result);
//    //------------------------------------------------------------------------------------------------------------------------//--------------------------------------------------------------------------------------------------------------------------
//
//    wait(NULL);
//    exit(0);
//}
//
////level 1: application layer  API
////recipient:use interface to use internet service
//static int arithematicOperation_protocol_recipientAPI_calculation (enum OPERATION op, int num1, int num2, int rp, int wp) {
//    //1, request:
//    //presentation layer : encode
//    char* requestMessage = arithematicOperation_protocol_requestMessage_encoding(op, num1, num2);
////    //test
////    printf("%d %d %d\n", little_endian_decoding(&requestMessage[0]), little_endian_decoding(&requestMessage[4]),
////           little_endian_decoding(&requestMessage[8]));
//
//    //transport layer: write
//    write(wp, requestMessage, strlen(requestMessage));
//
//    //2, reveive result
//    //(1) transport layer: read resonse message
//    char readBuffer[ARITHMETIC_OPERATION_PROTOCOL_RESPONSE_MESSAGE_MAXIMUM_LENGTH];
//    //single-use buffer: not a good design. ---- it can be defined in application program (level 0)
//    int  n = read(rp, readBuffer, ARITHMETIC_OPERATION_PROTOCOL_RESPONSE_MESSAGE_MAXIMUM_LENGTH);
//    readBuffer[n] = 0;
//
//    char* responseMessage = (char*) malloc(n + 1);
//    strcpy(responseMessage, readBuffer);
//
//    //test: print
//    printf("%d\n", arithematicOperation_protocol_responseMessage_decoding(responseMessage));
//    //(2) presentation layer
//    return (arithematicOperation_protocol_responseMessage_decoding(responseMessage));
//
//    //3, release recourse
//    free(requestMessage); free(requestMessage);
//}
//
//
//////server:
//////server's view of application layer protocol.
//////support internet service: implement of internet service/protocol.
////
//////assumption: next message in rp buffer is arithematicOperation_protocol request message.
//////provide the corresponding service.
//static void arithematicOperation_protocol_serverAPI (int rp, int wp) {
//    //1, request
//    //(1) transport layer: read request message
//    char* requestMessage = (char*) (malloc(ARITHMETIC_OPERATION_PROTOCOL_REQUEST_MESSAGE_MAXIMUM_LENGTH ));
//    //same as read buffer. sorry for this ugly design
//    int n = read(rp, requestMessage, ARITHMETIC_OPERATION_PROTOCOL_REQUEST_MESSAGE_MAXIMUM_LENGTH);
//    requestMessage[n] = 0;
//
//    //(2) persentation layer: decode request message
//    int* requestArray = arithematicOperation_protocol_requestMessage_decoding(requestMessage);
//    enum OPERATION op = getOperation(requestArray[0]);
//    int num1 = requestArray[1], num2 = requestArray[2];
//
//    //(3) application layer: implement of service.
//    int result;
//    switch (op) {
//        case ADDITION:
//            result = num1 + num2;
//            break;
//
//        case SUBSTRACTION:
//            result = num1 - num2;
//            break;
//
//        case MULTIPLICATION:
//            result = num1 * num2;
//            break;
//
//        case DIVISION:
//            result = num1 / num2; //assumption: num2 != 0
//            break;
//    }
//
//    //2, response
//    //(1) presentation layer: encode response message
//    char* responseMessage = arithematicOperation_protocol_responseMessage_encoding(result);
//
//    //(2) transport layer:
//    write(wp, responseMessage, strlen(responseMessage));
//
//    //3, release recourse
//    free(responseMessage); free(requestMessage);
//}
//
//
//
////level 2: presentation layer interface
//static char* arithematicOperation_protocol_requestMessage_encoding (enum OPERATION operation, int num1, int num2) {
//    char* message = (char*) malloc(ARITHMETIC_OPERATION_PROTOCOL_REQUEST_MESSAGE_MAXIMUM_LENGTH); //fixed length;
//    little_endian_encoding(operation, message); //bug: encoding of operation mode.
////    printf("%d %d\n", operation, little_endian_decoding(message)); //bug: operation code != assigned value.
//    //change:
////    int mode = 0;
////    little_endian_encoding(mode, message);
////    printf("%d %d\n", mode, little_endian_decoding(message));
//    little_endian_encoding(num1, message + sizeof(int));
//    little_endian_encoding(num2, message + 8);
//    return message;
//}
//
//static int* arithematicOperation_protocol_requestMessage_decoding (char* message) {
//    int* result = (int*) malloc(sizeof(int) * 3);
//    //format : result[0] mode, result[1] num1 result[2] num2
//    result[0] = little_endian_decoding(message);
//    result[1] = little_endian_decoding(message+4);
//    result[2] = little_endian_decoding(message+8);
//    return result;
//}
//
//static char* arithematicOperation_protocol_responseMessage_encoding(int num) {
//    char* responseMessage = (char*) (malloc(ARITHMETIC_OPERATION_PROTOCOL_RESPONSE_MESSAGE_MAXIMUM_LENGTH));
//    little_endian_encoding(num, responseMessage);
//    return responseMessage;
//}
//
//static int arithematicOperation_protocol_responseMessage_decoding (char* message) {
//    return (little_endian_decoding(message));
//}
//
//static void little_endian_encoding (int num, char* dst) {
//    //clear
//    int i;
//    for (i = 0; i < 4; ++i) {
//        dst[i] &= 0x00;
//    }
//    //write
//    for (i = 0; i < 4; ++i) {
//        dst[i] |= (num >> (sizeof(char) * i))/* & 0xff*/;
//    }
//}
//
//static int little_endian_decoding(char* src) {
//    int res = 0;
//    int i;
//    for (i = 0; i < 4; ++i) {
//        res |= (src[i] << (sizeof(char) * i));
//    }
//    return res;
//}