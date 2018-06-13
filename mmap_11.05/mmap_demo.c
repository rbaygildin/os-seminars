#include <stdio.h>
#include <fcntl.h>
#include <sys/mman.h>

typedef struct{
double x;
double sq;
} sqs;

const int SQ_NUM = 100000;

int main(int argc, const char** argv)
{
	if(argc < 2)
	{
		perror("You didn\'t input a path to file!");
		exit(-1);
	}
	int fd;
	if((fd = open(argv[1], O_RDWR | O_CREAT, 0666)) < 0)
	{
		printf("Can not open file %s\n", argv[1]);
		exit(-1);
	}
	sqs *p, *tmpp;
	int len = SQ_NUM * sizeof(sqs);
	ftruncate(fd, len);
	p = (sqs*) mmap(NULL, len, PROT_WRITE | PROT_READ, MAP_SHARED, fd, 0);
	if(close(fd) < 0)
	{
		printf("Can not close %s\n", argv[1]);
		exit(-1);
	}
	if(p == MAP_FAILED)
	{
		printf("Memory mapping failed!\n");
		exit(-1);
	}
	tmpp = p;
	sqs *prev = tmpp;
	long long sum = 0;
	for(int i = 0; i < SQ_NUM; i++)
	{
		sum += prev->sq;
		tmpp->x = i + 1;
		tmpp->sq = i;
		prev = tmpp;
		tmpp++;
	}
	printf("Sum of ints = %llu\n", sum);
	if(munmap(p, len) < 0)
	{
		perror("Can not unmap!");
		exit(-1);
	}
	return 0;
}