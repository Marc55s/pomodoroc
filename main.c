#include "Command.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>

char* catstr(char *one, char *two) {

  char *cat = malloc(strlen(one) + strlen(two) + 1);
  cat[0] = '\0';
  strcat(cat, one);
  strcat(cat, two);
  return cat;
}

int main(int argc, char **argv) {
  printf("args=%d\n", argc);
  if (argc == 2) {
    char *firstarg = strtok(NULL, " ");
    executeCMD(firstarg); // WARN: validate args
  } else {
    // NOTE: only for dev

    char *one = "start";
    char *sec = "break";

    executeCMD(catstr(one, sec));
  }

  return EXIT_SUCCESS;
}
