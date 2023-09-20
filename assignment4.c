/***********************************************************************
name:
	assignment4 -- acts as a pipe using ":" to seperate programs.
description:	
	See CS 360 Processes and Exec/Pipes lecture for helpful tips.
***********************************************************************/

/* Includes and definitions */
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include <errno.h>

/**********************************************************************
./assignment4 <arg1> : <arg2>

    Where: <arg1> and <arg2> are optional parameters that specify the programs
    to be run. If <arg1> is specified but <arg2> is not, then <arg1> should be
    run as though there was not a colon. Same for if <arg2> is specified but
    <arg1> is not.
**********************************************************************/


int main(int argc, char *argv[]){

    char **cmd1;
    char **cmd2;

    int i = 0;

    while(argv[i] && strcmp(argv[i],":") != 0) i++;

    if (!argv[i]) {  // if ":" was not found
        printf("':' not found in arguments.\n");
        return 1;
    }

    argv[i] = NULL;  // split the argv array at ':'

    cmd1 = &argv[1];
    cmd2 = &argv[i+1];

    printf("cmd1: ");
    for (i = 0; cmd1[i] != NULL; i++) {
        printf("%s ", cmd1[i]);
    }
    printf("\ncmd2: ");
    for (i = 0; cmd2[i] != NULL; i++) {
        printf("%s ", cmd2[i]);
    }
    printf("\n");


    int fd[2];
    pipe(fd);

    if (fork() == 0){ //child process
        
        dup2(fd[0], STDIN_FILENO);

        exec
        close(fd[1]);

        char buffer[256];

        read(fd[0], buffer, 255);

        printf("child read: %s \n", buffer);

        close(fd[0]);
        
    }
    else{
        close(fd[0]);

        write(fd[1], "Hello from parent!", 18);
        printf("parent wrote to pipe. \n");

        close(fd[1]);

        wait(NULL);

    }
        


	return 0;
}