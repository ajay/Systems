#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main()
{
	// fork();
	// printf("hello\n");

	pid_t id;
	id = fork();
	fork();

	if (id == 0)
	{
		printf("I am the child with pid %d\n", getpid());
		// printf("child\n");
		// printf("The parent's PID is: %d\n", getppid());
		// exit(0);
	}
	else
	{
		printf("I am the parent with pid %d\n", getpid());
		// printf("The child's PID is: %d\n", id);
		// printf("The child's PID is: %d\n", getpid());
		// printf("The parent's PID is: %d\n", getppid());
	}

	// printf("word\n");

	return 0;
}