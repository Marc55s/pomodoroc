#include <stdio.h>
#include <string.h>
#include "save.h"
#include "project.h"

extern struct project loaded[MAX_PROJECTS];

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
        //printf("%s %s=%d\n",loaded[i].name,proj.name,strcmp(loaded[i].name,proj.name));
        if(strcmp(loaded[i].name,proj.name) == 0){
            //equal
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
        add_project(proj.name);
    }
    load_projects();
    for(int i = 0;i<MAX_PROJECTS;i++){
        printf("%s %s =%d\n",loaded[i].name,proj.name,strcmp(loaded[i].name,proj.name));
        if(strcmp(loaded[i].name,proj.name) == 0){
            loaded[i].time += proj.time;
            strcpy(loaded[i].name, proj.name);
            //save_project(loaded[i]); //TODO change
            save_loaded();
            return 1;
        }  
    }
    return 0;
}


void remove_project(struct project proj){
    load_projects();
    if(project_exists(proj) != 0){

        for(int i = 0;i<MAX_PROJECTS;i++){
            if(strcmp(loaded[i].name,proj.name) == 0){
                //remove item at it and shift i + j items -1 
                for(int j = i;j<MAX_PROJECTS-1;j++){
                    strcpy(loaded[j].name,loaded[j+1].name);
                    loaded[j].time = loaded[j+1].time;
                }
                save_loaded();
                return;
            }
        }
    }
    printf("~ Project does not exist\n");
}

void add_project(char *name){
    struct project temp;
    strcpy(temp.name,name);
    temp.time = 0;
    if(project_exists(temp) != 0){
        printf("project already exists\n");
    }else{
        save_project(temp);
    }
}
