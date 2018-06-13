#include <sys/types.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <unistd.h>

int main(int argc, char * argv[])
{
	if(argc < 2)
	{
		perror("You didn\'t input a path to file!");
		exit(-1);
	}

	char* path = argv[1];
	int fileDescriptor;
	struct stat myfile;

	char line[100];
	char buf[]= "Stairway to Heaven";
	off_t cursor;

	if((fileDescriptor = open(path, 0666)) < 0)
	{
		printf("File %s can not opened!\n", path);
		exit(-1);
	}

	/*
	Set seek from beginning 
	*/
	printf("Please, input offset (SEEK_SET)\n");
	scanf("%lld", &cursor);

	if((cursor = lseek(fileDescriptor, cursor, SEEK_SET)) == -1L)
	{
		perror("Setting offset error!");
		exit(-1);
	}

	write(fileDescriptor, buf, sizeof(buf));

	/*
	Set seek from current position
	*/
	printf("Please, input new offset (SEEK_CUR)\n");
	scanf("%lld", &cursor);

	if((cursor = lseek(fileDescriptor, cursor, SEEK_CUR)) == -1L)
	{
		perror("Setting offset error!");
		exit(-1);
	}

	write(fileDescriptor, buf, sizeof(buf));

	/*
	Set seek from end
	*/
	printf("Please, input new offset (SEEK_CUR)\n");
	scanf("%lld", &cursor);

	if((cursor = lseek(fileDescriptor, cursor, SEEK_CUR)) == -1L)
	{
		perror("Setting offset error!");
		exit(-1);
	}

	write(fileDescriptor, buf, sizeof(buf));

	if(close(fileDescriptor) < 0)
	{
		printf("Can not close file %s\n", path);
		exit(-1);
	}

	return 0;
}
