#include <sys/types.h>
#include <unistd.h> 
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define NMAX 50

int main(int argc, const char** argv)
{
	int fd = atoi(argv[1]);
	printf("%d\n", fd);
	size_t size;
	int ri_ = rand() % 20;
	int sq_ = ri_ * ri_;
	char buf[NMAX];
	printf("Third-party: %d\n", fd);
	sprintf(buf, "Square of %d is %d", ri_, sq_);
	size = write(fd, buf, NMAX + 1); 
	if(size != NMAX)
	{
		printf("Can\'t write all string\n"); 
		exit(-1);
	}
	printf("Third-party app exit\n");
	exit(0);
}