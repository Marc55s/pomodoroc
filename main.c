#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include "command.h"

int main(int argc, char **argv) {
    // Check if there are enough arguments
    printf("Welcome to Pomodoroc!\n");

    //SIMULATE ARGUMENTS
    argv[1] = "add";
    argc++;
    argv[2] = "myproject";
    argc++;

    // Execute the command
    struct CommandMap result = executeCMDArgs(argc,argv);
    printf("~ parsing args completed\n");
    executeCMD(result);
    printf("~ executeCMD completed\n");
    return EXIT_SUCCESS;
}
