#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

int main(int argc, const char** argv)
{
		printf("Child pid = %d\n", getpid());
		printf("Child groupd id = %d\n", getpgid(getpid()));
		printf("Parent pid = %d\n", getppid());
		printf("Parent groupd id = %d\n", getpgid(getppid()));
		setpgid(getpid(), getpgid(getppid()));
		printf("Child new groupd id = %d\n", getpgrp());
		printf("Child session id = %d\n", getsid(getpid()));
	return 0;
}