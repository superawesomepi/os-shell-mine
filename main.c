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
		char *cmdline1 = (char*) malloc(MAXBUF); // stores user input from commmand line
		char *cmdline = (char*) malloc(MAXBUF);
		printf("%s\n", getenv("PATH"));
		char **paths = split(getenv("PATH"), ":");
		printf("dsh> ");
		// reads up to 256 characters into the buffer
 		if (fgets(cmdline1, MAXBUF, stdin) == NULL) {
   			exit(0);  // exit the program if EOF is input
 		}
        cmdline1[strlen(cmdline1) - 1] = '\0'; // remove the newline character
		removeSpaces(cmdline1, cmdline);
		//printf("User entered %s %ld\n", cmdline, strlen(cmdline));
		if(strlen(cmdline) > 0) {
			char **terms = split(cmdline, " ");			
			//printf("split finished\n");
			// print out all the tokens
			// int counts = 0;
			// while (terms[counts] != NULL) {
			// 	//printf("%s\n", terms[i]);
			// 	counts++;
			// }
			// // create array of arguments
			// char **args = (char**) malloc((counts) * sizeof(char*)); // create array of strings
			// for (int i = 0; i < counts - 1; i++) { // add empty strings
        	// 	args[i] = (char*) malloc(CAPACITY * sizeof(char));
    		// }
			// for(int j = 1; j < counts - 2; j++) { // fills args array with terms except the filepath
			// 	args[j] = terms[j+1];
			// }
			// args[counts - 1] = NULL; //null terminate args
			// check for starting /
			if(terms[0][0] == '/') {
				modeOne(terms);
			}
			else {
				if(strcmp(terms[0], "exit") == 0) {
					//printf("checking built-in: %s\n",terms[0]);
					exit(0);
					int i = 0;
					while(terms[i] != NULL) free(terms[i++]);
					free(terms);
					int j = 0;
					while(paths[j] != NULL) free(paths[j++]);
					free(paths);
					free(cmdline1);
					free(cmdline);
					exit(0); // exit command
				} 
				else if(strcmp(terms[0], "pwd") == 0) { // pwd command
					char cwd[MAXBUF];
					getcwd(cwd, MAXBUF - 1);
					printf("%s\n", cwd);
				}
				else if(strcmp(terms[0], "cd") == 0) { // cd command
					if(terms[1] != NULL) { // if a directory is given, go there
						chdir(terms[1]);
						printf("changed directory to %s\n", terms[1]);
					} else {
						chdir(getenv("HOME")); // if no directory is given, send to home directory
						printf("changed directory to home directory\n");
					}
				}
				else {	
					modeTwo(terms, paths);					
				}
			}
			int i = 0;
			while(terms[i] != NULL) free(terms[i++]);
			free(terms);
		}
		free(cmdline);
		free(cmdline1);
		int j = 0;
		while(paths[j] != NULL) free(paths[j++]);
		free(paths);
	}
	return 0;
}
