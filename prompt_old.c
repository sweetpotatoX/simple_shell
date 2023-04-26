#include "functions.h"
/**
 * main - pronts shell prompt, takes input
 * Return: 0 on success
 */

int main(void)
{
	char command[MAXIMUM_LENGTH];
	pid_t pid;
	int status;

	while (1)
	{
		printf("$ ");
		fflush(stdout);

		if (fgets(command, MAXIMUM_LENGTH, stdin) == NULL)
		{
			break;
		}
		command[strcspn(command, "\n")] = '\0';

		if (strcmp(command, "exit") == 0)
		{
			break;
		}

		pid = fork();
		if (pid == -1)
		{
			perror("fork");
			exit(EXIT_FAILURE);
		}
		else if (pid == 0)
		{
			execlp(command, command, NULL);
			perror("hsh");
			exit(EXIT_FAILURE);
		}
		else
		{
			waitpid(pid, &status, 0);
		}
	}
	return (EXIT_SUCCESS);
}
