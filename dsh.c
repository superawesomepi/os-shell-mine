/*
 * dsh.c
 *
 *  Created on: Aug 2, 2013
 *      Author: chiu
 */
#include "dsh.h"

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <wait.h>
#include <sys/types.h>
#include <errno.h>
#include <err.h>
#include <sys/stat.h>
#include <string.h>


// TODO: Your function definitions below (declarations in dsh.h)

char** split(char *str, char *delim) {
    int numTokens = 1;
    for (int i = 0; str[i] != '\0'; ++i) { // determine the delimiter count
        if (*delim == str[i]) ++numTokens;
    }
//    printf("the number of tokens is %d\n", numTokens);
     // this creates num pointers to strings
    char **array = (char**) malloc((numTokens + 1) * sizeof(char*));
    // this loops through each array element and instantiates
    // an array of chars of length CAPACITY
    for (int i = 0; i < numTokens; i++) {
        array[i] = (char*) malloc(CAPACITY * sizeof(char));
    }
    char* token = strtok(str, delim);
    // now I can assign strings to individual array elements
    for (int i = 0; i < numTokens; i++) {
        strcpy(array[i], token);
        token = strtok(NULL, delim);
    }
    array[numTokens] = NULL; // set the last value to null
    return array;
}
void modeOne(char **filepath) {
    if (access(filepath[0], F_OK | X_OK) == 0) {
        int len = 0;
        while(filepath[len] != NULL) len++; // find length of filepath array
        int concurrent = 0;
        if(strcmp(filepath[len-1], "&") == 0) { // if there is an & at the end of the array
            filepath[len-1] = NULL; // set it to null, then set to run concurrently
            concurrent = 1;
        }
        if(0 != fork()) { // parent
            if(concurrent) return; // concurrent execution
            else wait(NULL); // waiting
        }
        else execv(filepath[0], filepath); // child        
    } else {
        printf("could not run requested file");
    }
    return;
}

void modeTwo(char **filepath, char **paths) {
    char filename[32];
    if (filepath[0][0] == '.')
        strcpy(filename, &filepath[0][1]);
    int path = 0;
    int found = 1;
    while(paths[path] != NULL && found) {
        printf("%s ::: %s\n", paths[path], filename);
        strcat(paths[path], filename);
        printf("%s ::: %s\n", paths[path], filename);
        if (access(paths[path], F_OK | X_OK) == 0) {
            printf("correct filepath found\n");   
            strcpy(filepath[0], paths[path]);
            int counts = 0;
			while (filepath[counts] != NULL) {
			    printf("%s\n", filepath[counts]);
			    counts++;
			}
            modeOne(filepath);
            found = 0; 
        } else {
            printf("filepath not found\n");
            path++;
        }
    }
    return;
}

char* removeSpaces(char *input, char *output) {
    int idx = 0;
    int i;
    int j = 0;
    int k = 0;
    // go through string until last leading space
    while(input[idx] == ' ' || input[idx] == '\t') idx++;
    for(i = idx; input[i] != '\0'; i++) { // copy into new str
        if(input[i] != ' ') k = i;
        output[j] = input[i];
        j++;
    }
    output[k + 1 - idx] = '\0';
    //printf("Input with no white spaces is: %sEND%d\n", output, k);
    return output;
}
