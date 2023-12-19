# README for Assignment 4 Code

## Overview
This program allows the execution of one or two command-line programs, optionally connected by a pipe. It accepts up to two arguments, representing the programs to be executed. If only one argument is provided, the program will execute it as a standalone process. If two arguments are provided, separated by a colon (`:`), the program will execute them as connected processes, where the output of the first program is piped into the input of the second.

## Requirements
- GCC or any standard C compiler
- Standard Unix/Linux environment

## Compilation
To compile the program, use the following command:

```
gcc -o assignment4 assignment4.c
```

## Usage
```
./assignment4 <arg1> : <arg2>
```

- `<arg1>` and `<arg2>` are the command-line programs to be executed.
- If only `<arg1>` is provided, it is executed independently.
- If both `<arg1>` and `<arg2>` are provided, separated by a colon, the output of `<arg1>` is piped as the input to `<arg2>`.

## Examples
1. To run a single program:
   ```
   ./assignment4 ls
   ```

2. To pipe the output of one program to another:
   ```
   ./assignment4 ls : wc -l
   ```

## Implementation Details
- The program searches for the colon (`:`) to determine if two commands are provided.
- It uses `fork()` to create a child process and `pipe()` for inter-process communication.
- `dup2()` is used to redirect standard output and input for the piping mechanism.
- `execvp()` is used to execute the commands.
- The parent process waits for the child process to finish execution using `waitpid()` and returns the appropriate exit status.

## Error Handling
- The program includes basic error handling for system calls like `pipe()`, `fork()`, and `execvp()`.
- In case of an error, it outputs an error message and exits with a status of 1.

## Limitations
- The program assumes a Unix/Linux environment and may not work in non-Unix environments.
- It does not support commands that require complex argument parsing or shell-specific features.
