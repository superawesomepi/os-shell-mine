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

