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

	int fileDescriptor;
	struct stat fileInfo;
	off_t fileOffset;
	char* path = argv[1];

	printf("Please, input a length to what file should be extended\n");
	scanf("%lld", &fileOffset);

	fileDescriptor = open(path, 0666);
	fstat(fileDescriptor, &fileInfo);
	printf("File %s has size = %lld bytes\n", path, fileInfo.st_size);
	ftruncate(fileDescriptor, fileOffset);
	fstat(fileDescriptor, &fileInfo);
	printf("Now file %s has size = %lld bytes\n", path, fileInfo.st_size);

	if(close(fileDescriptor) < 0)
	{
		perror("Can not close a file!");
		exit(-1);
	}

	return 0;
}
