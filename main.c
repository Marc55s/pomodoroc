#include <stdio.h>
#include <stdlib.h>
#include "command.h"
#include "save.h"
#include "timer.h"
#include "project.h"

#define debug 1

int simulateargs(int argc, char **argv) {
    if (debug) {
        argv[1] = "rm";
        argc++;
        argv[2] = "aZZ";
        argc++;
    }

    // Execute the command
    struct CommandMap result = executeCMDArgs(argc, argv);
    printf("~ parsing args completed\n");
    if (executeCMD(result) != 0) {
        printf("~ exec failed");
        return EXIT_FAILURE;
    }
    printf("~ executeCMD completed\n");
    return EXIT_SUCCESS;
}

int main(int argc, char **argv) {
    printf("Welcome to Pomodoroc!\n");
    simulateargs(argc, argv);
    return EXIT_SUCCESS;
}
