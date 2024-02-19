/*
 * main.c
 *
 *  Created on: Mar 17 2017
 *      Author: david
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/resource.h>
#include <sys/stat.h>
#include <string.h>
#include "dsh.h"

#define MAX_PROC 250

int main(int argc, char *argv[]) {

	// DO NOT REMOVE THE BLOCK BELOW (FORK BOMB PREVENTION) //
	struct rlimit limit;
	limit.rlim_cur = MAX_PROC;
	limit.rlim_max = MAX_PROC;
	setrlimit(RLIMIT_NPROC, &limit);
	// DO NOT REMOVE THE BLOCK ABOVE THIS LINE //

	while(1) {
		char *cmdline = (char*) malloc(MAXBUF); // stores user input from commmand line
		printf("dsh> ");
		// reads up to 256 characters into the buffer
 		if (fgets(cmdline, MAXBUF, stdin) == NULL) {
   			exit(0);  // exit the program if EOF is input
 		}
        cmdline[strlen(cmdline) - 1] = '\0'; // remove the newline character
//		printf("User entered %s", cmdline);
		char **terms = split(cmdline, " ");
//		printf("split finished\n");
		// print out all the tokens
		int i = 0;
		while (terms[i] != NULL) {
  			printf("%s\n", terms[i]);
  			i++;
		}
		// check for starting /
		if(terms[0][0] == '/') printf("Search for full program\n");
		else {
			printf("checking built-in\n");
			if(strcmp(terms[0], "exit") == 0) return 0; // exit command
    		if(strcmp(terms[0], "pwd") == 0) { // pwd command
				char cwd[MAXBUF];
				getcwd(cwd, MAXBUF - 1);
				printf("%s\n", cwd);
			}
			if(strcmp(terms[0], "cd") == 0) { // cd command
				if(terms[1] != NULL) { // this doesn't appear to work
					chdir(terms[1]);
					printf("changed directory to %s\n", terms[1]);
				} else printf("directory could not be found\n");
				
			}
			else; // not a built-in command
		}
	}

	return 0;
}
