#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

#define MAX_LENGTH 1024
int main(int argc, char **argv);
void prompt_loop(void);
char prompt_read_line(void);


#endif
