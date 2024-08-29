#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Command.h"
#include "Timer.h"


void executeCMD(char *command) {
  CommandMap_t commands[] = {{"start", start},{"startbreak",startbreak},{
    "startstudy",startstudy}, {NULL, NULL}};
  for (int i = 0; commands[i].command != NULL; i++) {
    if(commands[i].command == NULL || command == NULL) continue;
    if (strcmp(commands[i].command, command) == 0) {
      commands[i].function();
    }
  }
}

void start() {
  printf("start");
  startTimer(DEFAULT_STUDY);
}

void startbreak(){
  printf("start:break");
  startTimer(DEFAULT_BREAK);
}
void startstudy(){
  printf("start:study");
  start();
  startbreak();
  start();
}
