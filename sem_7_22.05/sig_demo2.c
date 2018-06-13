#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

void handleSig(int sig)
{
	printf("We catched signal = %d\n", sig);
	if(sig == SIGINT)
	{
		printf("We used ctrl-c\n");
	}
	else if(sig == 3)
	{
		printf("We used ctlr-f4\n");
	}
}
int main(int argc, const char** argv)
{
	signal(SIGINT, handleSig);
	signal(SIGQUIT, handleSig);
	(void)fork();
	while(1);
	return 0;
}