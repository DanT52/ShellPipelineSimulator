take in two programs

split argv into two strings which each program

execvp will take in execvp(char *file, char *argv[]);

I'll have to use dup2 in order to redirect stdout into the pipe on one end
and stdin out of pip on other end.