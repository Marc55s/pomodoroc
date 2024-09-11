#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include "command.h"
#include "save.h"
#include "timer.h"
#include "project.h"

int executeCMD(struct CommandMap cmd) {
    if(cmd.function != NULL){
        cmd.function(cmd.time);
    }else if(cmd.charfunction != NULL){
        cmd.charfunction(cmd.param);
    }else {
        return -1;
    }
    return EXIT_SUCCESS;
}

struct CommandMap executeCMDArgs(int argc, char **argv) {
    printf("~ parsing args...\n");
    printf("~ argc = %d\n", argc);
    for (int i = 1; i < argc; i++) {
        printf("~ argv[%d] = %s\n", i, argv[i]);
    }
    struct CommandMap command;
    command.function = NULL;
    command.charfunction = NULL;
    command.time = 0;
    command.param = 0;

    if (argc < 2) {
        printf("Usage: %s <command> [params]\n", argv[0]);
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
                //Project case
                command.charfunction = startproject;
                command.param = argv[2];
            }
        } else if (argc == 4 && strcmp(argv[2], "study") == 0) {
            command.function = startstudy;
            //command.units = atoi(argv[3]);
        }

    }else if(strcmp(argv[1], "add") == 0){
        if(argc == 3){
            command.charfunction = add; 
            command.param= argv[2];
        }
    } else if(strcmp(argv[1], "list") == 0){
        command.function = listprojects;
    }else if(strcmp(argv[1], "help") == 0){
        printf("Usage: %s <command> [params]\n", argv[0]);
        printf("commands:\nstart [study,break,PROJECT(can be any name)]\nlist\nadd [PROJECT]\nhelp\n");

    }else if(strcmp(argv[1], "rm") == 0){
        command.charfunction = remove_proj;
        command.param = argv[2];
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


void startproject(char *proj_name){
    //start stop watch
    //create if not existent
    // otherwise update saved time
    double time_spend = 0;
    startstopwatch(&time_spend);
    struct project p;
    strcpy(p.name, proj_name);
    p.time = time_spend;
    update_project(p);
}

void add(char *name){
    add_project(name);
}

void listprojects(){
    list_projects();
}

void remove_proj(char *name){
    struct project temp;
    strcpy(temp.name, name);
    remove_project(temp);
}
