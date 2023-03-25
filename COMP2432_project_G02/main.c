
//system header file
#include <stdio.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//program header file
#include "classes/time_type.h"
#include "modules/modules.h"
#include "classes/appointment.h"
#include "main.h"
#include "tools.h"
#include "protocol/coding_tools.h"



//global variable definition
//(0) DS
const int DEFAULT_CAPACITY_OF_VECTOR = 128;  //default capacity of vector in this program.

//（1）time
STime g_startTime, g_endTime; //define valid time range

//(2) name
char g_nameMap[10][50]; //array to store the user name.
int g_userNum;
//related function

//(3) IPC
int* g_p2c_fd; //pointer of pipe from parent to child
int* g_c2p_fd; //pointer of pipe from child to parent;
//const int P2C_BUFFER_SIZE = 800;
//const int C2P_BUFFER_SIZE = 800;

//(4) appointment
int g_apNum = 0;
SAppointment g_appointmentArray[DEFAULT_CAPACITY_OF_VECTOR];  //assumption: not exceed the capacity
//!security problem: visible to the user process

//static function/ variable declaration.
static void initialize(int argc, char* argv[]);
static int getInstructionMode (char* instruction);
static void freeUpProgram ();

//--------------------------------------implement---------------------------------------------------------------------

//function implement.

//level 0:
int main(int argc, char* argv[]) {
   //(1) initialize
   initialize(argc, argv);

   //(2) interpreter
   //...file input !
   //....
   char instruction[100];

    int endProgram = 0;
    while (endProgram != 1) {

        printf("Please enter appointment:\n");
        scanf("%s", instruction);
        instructionMode = getInstructionMode(instruction);

        switch (instructionMode) {
            case 0:
                endProgram = 1;
                break;
            case 1:
                appointmentModule(instruction); // interprete the instruction
                break;
            case 2:
                scheduleModule(instruction);
                break;
            default:
                printf("Invalid instruction format. Input again !\n");
        }

    }
    //(3) exit the program
    freeUpProgram();
    exit(0);
}

//level 1: initialize global variable | create child process.
static void initialize(int argc, char* argv[]) { //!!! pass array of string to function.
//--------------------------------------------------------------------------------------------------------------------------
    //(1) initialize global variable.
    //1' time
    g_startTime = getTimeFromStandardForm(argv[1]);
    g_endTime = getTimeFromStandardForm(argv[2]);

    //2' user
    g_userNum = argc - 3;
    //boundary case: error handling
    if (g_userNum < 3 || g_userNum > 10) {
        printf("The number of users is not valid.\n");
        exit(0);
    }

    int i;
    for (i = 3; i < argc; ++i) {
        strcpy(g_nameMap[i - 3], argv[i]);
    }

    //3' IPC pointer
    g_p2c_fd = (int*) (malloc(sizeof(int) * (2 * g_userNum + 1)));
    g_c2p_fd = (int*) (malloc(sizeof(int) * (2 * g_userNum + 1)));


    //(2) create child process.
    //fork
    int childid, userIndex;
    for (userIndex = 0; userIndex < g_userNum; ++userIndex) {
        if ((childid = fork()) < 0) { //error
            perror("fork");
            exit(1);
        } else if (childid == 0) { // child process
            userProcess (userIndex);
        }
        //parent: close pipe
        close(g_p2c_fd[userIndex * 2]);
        close(g_c2p_fd[userIndex * 2 + 1]);
    }
}

//--------------------------------------------------------------------------------------------------------------------------
//input: instruction string
//output: [endProgram] -> 0,  [appointment instruction] -> 1,  [printSchd] -> 2
//       boudary case: invalid format -> -1
static int getInstructionMode (char* instruction) {
    return 0;
}
//--------------------------------------------------------------------------------------------------------------------------




//level 1 from main
//free up: pipe, child process, dynamic allocation.
static void freeUpProgram() {

    //(1) end the child process
    char message[4];
    integer_little_endian_encoding(0, message);

    int wp, i;
    for (i = 0; i < g_userNum; i ++) {
        //end signal
        wp = g_p2c_fd[2 * i + 1];
        if (write(wp, message, 4) < 0) {
            printf(" %s  : freeUpProgram -- write end message", g_prompt);
            exit(1);
        }

        //close pipe
        close(g_p2c_fd[2 * i + 1]);
        close(g_c2p_fd[2 * i]);
    }

    //(2) collect child process
    int childid, status;
    childid = wait(&status);
    while (childid != -1) {
        childid = wait(&status);
    }
}
