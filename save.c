#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "save.h"

const char *FILENAME = "project.txt";

struct project loaded[MAX_PROJECTS];
int projectCount = 0;

int save_override(struct project proj);
void save_loaded(){
    for(int i = 0;strcmp(loaded[i].name,"") !=0;i++){
        save_override(loaded[i]);
    }
}

int save_override(struct project proj){
    FILE *file;
    errno_t err;

    err = fopen_s(&file, FILENAME, "w");
    if (err != 0) {
        // Handle error, err contains the error code
        perror("fopen_s");
        return -1;
    }

    // convert long into string
    int maxdigits = 4 * sizeof(double);
    char str[maxdigits + sizeof(char)];
    sprintf(str, "%fl", proj.time);
    char in[64];
    in[0] = '\0';
    strcat(in, proj.name);
    strcat(in, " ");
    strcat(in, str);
    strcat(in, "\n");

    printf("~ saving %s", in);

    // Write to the file
    if (fputs(in, file) == EOF) {
        perror("fputs");
        fclose(file);
        return -1;
    }

    // Close the file
    if (fclose(file) != 0) {
        perror("fclose");
        return -1;
    }

    return 0;
}

int save_project(struct project proj){
    FILE *file;
    errno_t err;

    err = fopen_s(&file, FILENAME, "a+");
    if (err != 0) {
        // Handle error, err contains the error code
        perror("fopen_s");
        return -1;
    }

    // convert long into string
    int maxdigits = 4 * sizeof(double);
    char str[maxdigits + sizeof(char)];
    sprintf(str, "%fl", proj.time);
    char in[64];
    in[0] = '\0';
    strcat(in, proj.name);
    strcat(in, " ");
    strcat(in, str);
    strcat(in, "\n");

    printf("~ saving %s", in);

    // Write to the file
    if (fputs(in, file) == EOF) {
        perror("fputs");
        fclose(file);
        return -1;
    }

    // Close the file
    if (fclose(file) != 0) {
        perror("fclose");
        return -1;
    }

    return 0;
}

int load_projects(){
    FILE *file;
    errno_t err;

    err = fopen_s(&file, FILENAME, "a+");
    if (err != 0) {
        // Handle error, err contains the error code
        perror("fopen_s");
        return -1;
    }
    char buf[1024];
    int count = 0;

    char *tokenized[3];
    // Read file
    while(fgets(buf, 1024, file)){
        tokenized[0] = strtok(buf, SPLIT_TOK);
        tokenized[1] = strtok(NULL, SPLIT_TOK);
        strcpy(loaded[count].name,tokenized[0]);
        sscanf(tokenized[1], "%lf", &loaded[count].time);
        count++;

    }
    projectCount = count;

    // Close the file
    if (fclose(file) != 0) {
        perror("fclose");
        return -1;
    }

    return 0;
}


