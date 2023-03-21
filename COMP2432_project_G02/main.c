
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



//global variable definition
//(0) DS
const int DEFAULT_CAPACITY_OF_VECTOR = 128;  //default capacity of vector in this program.

//（1）time
STime g_startTime, g_endTime; //define valid time range

//(2) name
char** g_nameMap; //array to store the user name.
int g_userNum;
//related function

//(3) IPC
int* g_p2c_fd; //pointer of pipe from parent to child
int* g_c2p_fd; //pointer of pipe from child to parent;
const int P2C_BUFFER_SIZE = 800;
const int C2P_BUFFER_SIZE = 800;

//(4) appointment
int g_apNum = 0;
SAppointment *g_appointmentArray = NULL;  //assumption: not exceed the capacity
//!security problem: visible to the user process

//static function/ variable declaration.
static void initialize(int argc, char* argv[]);
static int getInstructionMode (char* instruction);
static void freeUpProgram ();

//--------------------------------------implement---------------------------------------------------------------------

//function implement.

//level 0:
int main(int argc, char* argv[]) {
//------------------------------------------------------------------------------------------------------------------------//--------------------------------------------------------------------------------------------------------------------------
//This part is only used for the demonstration in stage 1.
    printModuleIn();
    sleep(1);

   //(1) initialize
    printf("(pid: %d)  Parent process: Parent process has been created.\n", getpid());
    printf("--------------------------------------------------------------------------------------------------------------------------\n");
    //1' initialize the global variable, create child process
   initialize(argc, argv);
   //2' collect the child process
   sleep(2);
    printf("--------------------------------------------------------------------------------------------------------------------------\n");
    int returnValue, status;
   int childid = wait(&status);
   while (childid != -1) {
       if (WIFEXITED(status) != 0) {
           returnValue = WEXITSTATUS(status);
           printf("(pid: %d)  Parent process:  collect child process %d.\n",getpid(), returnValue);
       } else {
           printf("(pid: %d)  Parent process: child process %d is interrupted.\n",getpid(), childid);
       }

       childid = wait(&status);
   }
   //3' exit
    printf("\n(pid: %d)  Parent process: Parent process terminated.\n\n", getpid());


   printModuleOut();
   exit(0);
//--------------------------------------------------------------------------------------------------------------------------


   //(2) interpreter
   //...file input !
   //....
   char instruction[100];
    printf("Please enter appointment:\n");
    scanf("%s", instruction);
    int instructionMode = getInstructionMode(instruction);
    while (instructionMode != 0) {
        if (instructionMode == 1) {
            appointmentModule(instruction);
        } else {
            scheduleModule(instruction);
        }

        printf("Please enter appointment:\n");
        scanf("%s", instruction);
        instructionMode = getInstructionMode(instruction);
    }
    //(3) exit the program
    freeUpProgram(); //now is dangerous
    exit(0);
}

//level 1: initialize global variable | create child process.
static void initialize(int argc, char* argv[]) {
//--------------------------------------------------------------------------------------------------------------------------
    //(1) initialize global variable.
    //1' time
//    g_startTime;
//    g_endTime =  ;

    //2' user
    g_userNum = argc - 3;
    //boundary case: error handling
    g_appointmentArray = (SAppointment*) (malloc(sizeof(SAppointment) * DEFAULT_CAPACITY_OF_VECTOR + 1));
    if (g_userNum < 3 || g_userNum > 10) {
        printf("The number of users is not valid.\n");
        exit(0);
    }
    g_nameMap = (char**) (malloc(sizeof(char*) * g_userNum));
    int i, size;
    for (i = 3; i < argc; ++i) {
        size = strlen(argv[i]);
        g_nameMap[i - 3] = malloc(sizeof(char*) * size);
        strcpy(g_nameMap[i - 3], argv[i]);
    }

    //3' IPC pointer
    g_p2c_fd = (int*) (malloc(sizeof(int) * (2 * g_userNum + 1)));
    g_c2p_fd = (int*) (malloc(sizeof(int) * (2 * g_userNum + 1)));
    //close pointer for parent process
    int userIndex;
    for (userIndex = 0; userIndex < g_userNum; ++userIndex) {
        close(g_p2c_fd[userIndex << 1]);
        close(g_c2p_fd[(userIndex << 1) + 1]);
    }

    //(2) create child process.
    int childid;
    for (userIndex = 0; userIndex < g_userNum; ++userIndex) {
        if ((childid = fork()) < 0) {
            perror("fork");
            exit(1);
        } else if (childid == 0) {
            userProcess (userIndex);
        }
    }
//--------------------------------------------------------------------------------------------------------------------------
}

//input: instruction string
//output:
static int getInstructionMode (char* instruction) {
    return 0;
}

static void freeUpProgram () {
    //1, collect the child process.
}