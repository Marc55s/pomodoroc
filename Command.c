#include "command.h"
#include "timer.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void executeCMD(struct CommandMap cmd) {
    cmd.function(cmd.time);
}

struct CommandMap executeCMDArgs(int argc, char **argv) {
    printf("parsing args...\n");
    printf("argc = %d ", argc);
    for (int i = 1; i < argc; i++) {
        printf("argv[%d] = %s\n", i, argv[i]);
    }
    struct CommandMap command;

    if (argc < 2) {
        printf("Usage: %s <command> [params]\n", argv[0]);
        command.function = NULL;
        return command;
    }

    if (strcmp(argv[1], "start") == 0) {
        if(argc == 2){
            command.function = start;
            command.time = DEFAULT_STUDY;
        }else if (argc == 3) {
            if (strcmp(argv[2], "break") == 0) {
                command.function = startbreak;
                command.time = DEFAULT_BREAK; // Default break time is 5 minutes
            } else if (strcmp(argv[2], "study") == 0) {
                command.function = startstudy;
                command.time = DEFAULT_STUDY; // Default study time is 25 minutes
            } else {
                // Parse time if provided
                command.function = start;
                command.time = atoi(argv[2]);
            }
        } else if (argc == 4 && strcmp(argv[2], "study") == 0) {
            command.function = startstudy;
            //command.units = atoi(argv[3]);
        }

    }

    return command;
}

void start(double time) {
    startTimer(time);
}

void startbreak(double time) {
    startTimer(time);
}
void startstudy(double time) {
    startTimer(time);
    startTimer(DEFAULT_BREAK);
    startTimer(time);
}
