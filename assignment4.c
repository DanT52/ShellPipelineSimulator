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
    while(argv[i] && strcmp(argv[i],":") != 0) i++; //find :

    char **cmd1 = (i > 1) ? &argv[1] : NULL;                //if i > 1 (meaning first command is given) set to it otherwize null     
    char **cmd2 = (i < argc - 1) ? &argv[i + 1] : NULL;     //if i < argc -1 meaning the : is not at the very end, there is a second command
    if (argv[i]) argv[i] = NULL;      // split the argv array at ':'

    int fd[2];      //create pipe check for errors.
    if (pipe(fd) == -1){
        fprintf(stderr, "%s\n", strerror(errno));
        exit(1);
    }

    int pid = fork();
    if (pid == -1){     //create fork check errors
        close(fd[0]);
        close(fd[1]);
        fprintf(stderr, "%s\n", strerror(errno));
        exit(1);
    }

    if (pid == 0){ //child process
        close(fd[0]);
        if (cmd2) dup2(fd[1], STDOUT_FILENO);   //if the second command is there
        close(fd[1]);                           //redirect stdout to the pipe

        if(cmd1){ //if command 1 present the run it
            execvp(cmd1[0], cmd1);
            fprintf(stderr, "%s\n", strerror(errno)); // only returns from execvp if error
            exit(1);
        }
    }else{ //parent process
        close(fd[1]);
        if (cmd1) dup2(fd[0], STDIN_FILENO); //if command 1 is there redirect sdin to be from pipe
        close(fd[0]);
        
        if(cmd2){
            execvp(cmd2[0], cmd2);
            fprintf(stderr, "%s\n", strerror(errno));
            exit(1);
        }

        int status; //only gets to this point if command 1 was present and 2 was not if there
        waitpid(pid, &status, 0);   //if there was an error in command 1 the proper status is returned.
        return WIFEXITED(status) ? WEXITSTATUS(status) : 0;
    }

    return 0;


}