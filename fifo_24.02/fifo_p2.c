#include <sys/types.h>
#include <sys/stat.h> 
#include <fcntl.h> 
#include <stdlib.h>
#include <unistd.h> 
#include <stdio.h> 
#include <errno.h>
#define NMAX 70

int main(int argc, const char** argv){
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
	if((fd = open(name, O_RDONLY)) < 0){
		printf("Can\'t open FIFO for writing\n");
		exit(-1); 
	}
	size = read(fd, resstring, sizeof(resstring));
	if(size < 0){
		printf("Can\'t read string\n");
		exit(-1);
	}
	printf("Caught message from collegue: %s\n", resstring);
	close(fd);
	return 0; 
}