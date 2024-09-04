#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include "command.h"
#include "save.h"
#include "timer.h"

int simulateargs(int argc, char **argv){
    argv[1] = "add";
    argc++;
    argv[2] = "myproject";
    
    argc++;
    // Execute the command
    struct CommandMap result = executeCMDArgs(argc,argv);
    printf("~ parsing args completed\n");
    if(executeCMD(result) != 0)
        return EXIT_FAILURE;
    printf("~ executeCMD completed\n");
    return EXIT_SUCCESS;
}

int main(int argc, char **argv) {
    // Check if there are enough arguments
    printf("Welcome to Pomodoroc!\n");
    startstopwatch();
    return EXIT_SUCCESS;
}
