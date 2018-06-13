#include <sys/types.h>
#include <sys/stat.h> 
#include <stdlib.h>
#include <fcntl.h> 
#include <unistd.h> 
#include <stdio.h> 
#include <errno.h>
#include <time.h>
#define NMAX 70

int main(int argc, const char** argv){
	srand(time(NULL));
	int fd, result; size_t size; 
	char resstring[NMAX]; 
	char *name = argv[1];
	struct stat buf;
	if(stat(name, &buf) != 0 && errno == ENOENT){
		if(mknod(name, S_IFIFO | 0666, 0) < 0){
			printf("Can\'t create FIFO\n");
			exit(-1);
		}
	}
	if((fd = open(name, O_WRONLY)) < 0){
			printf("Can\'t open FIFO for writing\n");
		exit(-1); 
	}
	int r_ = rand() % 30 + 1;
	sprintf(resstring, "Hello, collegue! I gave you some random integer = %d", r_);
	size = write(fd, resstring, sizeof(resstring) + 1); 
	if(size != (sizeof(resstring) + 1)){
		printf("Can\'t write all string to FIFO\n");
		exit(-1); 
	}
	close(fd);
	return 0; 
}