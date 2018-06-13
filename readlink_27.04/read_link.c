#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#define BUF_SIZE 50

int main(int argc, const char** argv)
{
	if(argc < 3)
	{
		perror("You didn\'t input path to file and symbolic link!");
		exit(-1);
	}
	char* fpath = argv[1];
	char* slpath = argv[2];
	if(symlink(fpath, slpath) < 0)
	{
		printf("Can not create symbolic link for %s\n", fpath);
		exit(-1);
	}
	char sbuf[BUF_SIZE];
	if(readlink(slpath, sbuf, BUF_SIZE) < 0)
	{
		printf("Can not read symbolic link %s\n", slpath);
		exit(-1);
	}
	printf("From symbolic link: %s\n", sbuf);
	int fileDescriptor;
	if((fileDescriptor = open(sbuf, O_RDONLY)) < 0)
	{
		printf("Can not open file %s\n", fpath);
		exit(-1);
	}
	if(read(fileDescriptor, sbuf, BUF_SIZE) < 0)
	{
		printf("Can not read file %s\n", fpath);
		exit(-1);
	}
	printf("From file: %s\n", sbuf);
	if(close(fileDescriptor) < 0)
	{
		printf("Can not close file %s\n", fpath);
		exit(-1);
	}
	return 0;
}