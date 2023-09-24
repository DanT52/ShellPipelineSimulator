take in two programs

split argv into two strings which each program

execvp will take in execvp(char *file, char *argv[]);

I'll have to use dup2 in order to redirect stdout into the pipe on one end
and stdin out of pip on other end.


do not use reads or writes

execvp is what i wanna be using basically.



tbl:

0,stin
1,stdout
2,stderr

ls wtires to stdout
sort reads stdin

basically we wanna connect theses using pipe like i wrote on line 7.