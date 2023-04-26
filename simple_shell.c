#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

#define MAX_CMD_LENGTH 100

int main()
{
    char cmd[MAX_CMD_LENGTH];
    int status;

    while (1) {
        printf("#cisfun$ ");
        if (fgets(cmd, MAX_CMD_LENGTH, stdin) == NULL) {

            break;
        }
        cmd[strcspn(cmd, "\n")] = '\0';
        pid_t pid = fork();
        if (pid < 0) {
            perror("fork failed");
} 
else if (pid == 0)
{
execl(cmd, cmd, (char*)NULL);
perror("exec failed");
exit(EXIT_FAILURE);
}
else
{          
wait(&status);
}
}
return 0;
}
