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

    
    int i = 0;
    while(argv[i] && strcmp(argv[i],":") != 0) i++;

    if (!argv[i]) {  // if ":" was not found
        printf("':' not found in arguments.\n");
        exit(1);
    }

    argv[i] = NULL;  // split the argv array at ':'
    char **cmd1 = &argv[1];
    char **cmd2;

    if(argc -1 == i){
        cmd2 = NULL;
    } else{
        cmd2 = &argv[i+1];
    }

    int fd[2];
    if (pipe(fd) == -1){
        fprintf(stderr, "%s", strerror(errno));
        exit(1);
    }

    int pid = fork();
    if (pid == -1){
        close(fd[0]);
        close(fd[1]);
        fprintf(stderr, "%s", strerror(errno));
        exit(1);
    }

    if (pid == 0){ //child process

        close(fd[0]);
        if(cmd2)dup2(fd[1], STDOUT_FILENO);
        close(fd[1]);

        if(cmd1)execvp(cmd1[0], cmd1);

        if(cmd1){
            fprintf(stderr, "%s", strerror(errno));
            exit(1);
        }

    }
    else{

        close(fd[1]);
        dup2(fd[0], STDIN_FILENO);
        close(fd[0]);
        
        if(cmd2)(execvp(cmd2[0], cmd2));
        if(cmd2){
            fprintf(stderr, "%s", strerror(errno));
            exit(1);
        }

    }

    return 0;


}