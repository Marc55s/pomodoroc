#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "save.h"
#define SPLIT_TOK " " 
#define MAX_PROJECTS 100

const char *FILENAME = "project.txt";

struct project loaded[MAX_PROJECTS];
int projectCount = 0;

void add_project(char *name);
void print_project(struct project proj);
int project_exists(struct project proj);

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


void list_projects(){
    load_projects();
    printf("|projects(%d) |time\n",MAX_PROJECTS);
    for(int i = 0;i<MAX_PROJECTS;i++){
        if(strcmp(loaded[i].name,"")!=0){
            printf("----------------------\n");
            print_project(loaded[i]);
        }
    }

}
int project_exists(struct project proj){
    load_projects();
    for(int i = 0;i<MAX_PROJECTS;i++){
        if(strcmp(loaded[i].name,proj.name) != 0){
            return 1;
        }
    }
    return 0;
}

void print_project(struct project proj){
    printf("|%-10s |%.1lfmin\n",proj.name,proj.time);
}

int update_project(struct project proj){
    load_projects();
    if(project_exists(proj) == 0){
        printf("exists\n");
        add_project(proj.name);
    }
    for(int i = 0;i<MAX_PROJECTS;i++){
        if(strcmp(loaded[i].name,proj.name) != 0){
            loaded[i].time += proj.time;
            strcpy(loaded[i].name, proj.name);
            save_project(loaded[i]);
            return 1;
        }  
    }
    return 0;
}


void remove_project(){

}

void add_project(char *name){
    struct project temp;
    strcpy(temp.name,name);
    temp.time = 0;
    save_project(temp);
}
