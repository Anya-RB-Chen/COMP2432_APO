
//system header file
#include <stdio.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//program header file
#include "main.h"



//global variable definition
//(0) DS


//（1）time
STime g_startTime, g_endTime; //define valid time range

//(2) name
char g_nameMap[10][50]; //array to store the user name.
int g_userNum;
//related function

//(3) IPC
//int* g_p2c_fd; //pointer of pipe from parent to child
//int* g_c2p_fd; //pointer of pipe from child to parent;
//const int P2C_BUFFER_SIZE = 800;
//const int C2P_BUFFER_SIZE = 800;

//(4) appointment
int g_apNum;

void fileInput();
//!security problem: visible to the user process

//static function/ variable declaration.


//--------------------------------------implement---------------------------------------------------------------------

//function implement.

//level 0:
int main(int argc, char* argv[]) {

   //(1) initialize
   initialize(argc, argv);

   //(2) interpreter
   //...file input !
   //....
    printf("Please choose your input mode(input 1 or 2):\n1) Batch input(input a file);\n2) Command-line input.\n");
    int choice;
    scanf("%d",&choice);
    while (!(choice == 1 || choice== 2)){
        printf("Invalid input. Please input again. (1 or 2)\n");
        fflush(stdin);
        scanf("%d",&choice);
    }

    if (choice == 1){
        fflush(stdin);
        fileInput();
    } else {
        int endProgram = 0;
        while (endProgram != 1) {
            fflush(stdin);
            char *instruction = (char *) malloc((sizeof(char)) * 100);
            printf("Please enter appointment:\n");
            scanf("%[^\n]", instruction);

            int instructionMode = getInstructionMode(instruction);

            switch (instructionMode) {
                case 0:
                    endProgram = 1;
                    break;
                case 1:
                    appointmentModule(instruction); // interpret the instruction
                    break;
                case 2:
                    scheduleModule(instruction);
                    break;
                default:
                    printf("Invalid instruction format. Input again !\n");
            }
            free(instruction);
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

    // 为了测试comment掉
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
        if (g_nameMap[i-3][0] >= 97 && g_nameMap[i-3][0] <= 122){
            g_nameMap[i-3][0] -= 32;
        }
    }

    //3' IPC pointer
    g_p2c_fd = (int*) (malloc(sizeof(int) * (2 * g_userNum + 1)));
    g_c2p_fd = (int*) (malloc(sizeof(int) * (2 * g_userNum + 1)));
    for (i = 0; i<2*g_userNum+1; i+=2){
        if (pipe(&g_p2c_fd[i])<0 || pipe(&g_c2p_fd[i])<0) {
            perror("pipe creation error\n");
            exit(1);
        }
    }

    //(2) create child process.
    //fork
    pid_t childid, userIndex;
    for (userIndex = 0; userIndex < g_userNum; ++userIndex) {
        childid = fork();
        if (childid < 0) { //error
            perror("fork");
            exit(1);
        } else if (childid == 0) { // child process
            // close p2c write and c2p read
            close(g_p2c_fd[userIndex*2+1]);
            close(g_c2p_fd[userIndex*2]);
            userProcess (userIndex);
        }
        else
        //parent: close p2c read and c2p write
        {
            close(g_p2c_fd[userIndex * 2]);
            close(g_c2p_fd[userIndex * 2 + 1]);
        }
    }

}


//--------------------------------------------------------------------------------------------------------------------------
//input: instruction string
//output: [endProgram] -> 0,  [appointment instruction] -> 1,  [printSchd] -> 2
//       boudary case: invalid format -> -1
int getInstructionMode (char* full_instruction) {
    char instruction[20] = "\0";
    int i;
    for (i = 0; i< strlen(full_instruction); i++){
        if(full_instruction[i] == ' '){
            break;
        }
        instruction[i] = full_instruction[i];
    }

    if(strcmp(instruction, "endProgram") == 0){
        return 0;
    }
    else if(strcmp(instruction, "privateTime") == 0 || strcmp(instruction, "gathering") == 0 ||
            strcmp(instruction, "groupStudy") == 0  || strcmp(instruction, "projectMeeting") == 0){
        return 1;
    }
    else if(strcmp(instruction, "printSchd") == 0){
        return 2;
    }
    else{
        return -1;
    }
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
      //      printf(" %s  : freeUpProgram -- write end message", g_prompt);
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

void fileInput(){
    printf("Please input the file name: (complete directory are needed)\n");
    char file[100];
    char *path = (char *) malloc(sizeof (char )*50);
    strcat(path,"../");
    scanf("%s",file);
    strcat(path,file);
    FILE *fp;
    fp = fopen(path,"r");
    if (fp == NULL){
        perror("Cannot open the file. Please check the file directory.\n");
        exit(1);
    }
    int i;
    // read the file line by line
    while (!feof(fp)){
        char instruction[1000];
        fgets(instruction,1000,fp);
        i = 0;
        while (instruction[i] != '\n' && instruction[i] != EOF){
            i++;
        }
        instruction[i] = '\0';

        int instructionMode = getInstructionMode(instruction);

        switch (instructionMode) {
            case 0:
                break;
            case 1:
                appointmentModule(instruction); // interpret the instruction
                break;
            case 2:
                scheduleModule(instruction);
                break;
            default:
                printf("Invalid instruction format. Input again !\n");
        }
        usleep(100);
    }
    fclose(fp);
}