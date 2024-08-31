#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include "command.h"

int main(int argc, char **argv) {
    // Check if there are enough arguments
    printf("Welcome to Pomodoroc!\n");

    //SIMULATE ARGUMENTS
    /*
    argv[1] = "start";
    argc++;
    */

    // Execute the command
    struct CommandMap result = executeCMDArgs(argc,argv);
    if(result.function == NULL) return EXIT_FAILURE;
    executeCMD(result);
    return EXIT_SUCCESS;
}
