#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "save.h"


const char* FILENAME = "project.txt";



int add_project(char *projname, double minutes){
    FILE *file;
    errno_t err;

    err = fopen_s(&file, FILENAME, "a+");
    if (err != 0) {
        // Handle error, err contains the error code
        perror("fopen_s");
        return -1;
    }

    //convert long into string
    int maxdigits = (int) pow(2,sizeof(long)) % 10;
    char str[maxdigits + sizeof(char)]; 
    sprintf(str, "%fl", minutes);
    char in[80];
    in[0] = '\0';
    strcat(in,projname);
    strcat(in," ");
    strcat(in,str);
    strcat(in,"\n");

    printf("~ saving %s",in);


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
