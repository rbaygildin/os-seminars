#include <sys/types.h>
#include <unistd.h> 
#include <stdio.h>

#define NMAX 50

int main(int argc, const char** argv){

	int fd[2], cid;
	size_t size;
	char resstring[NMAX];
	if(pipe(fd) < 0){
		printf("Can\'t create pipe\n");
		exit(-1);
	}
	cid = fork();
	if(cid < 0){
		printf("Can\'t fork child\n");
		exit(-1);
	} else if (cid > 0) {
		close(fd[0]);
		size = read(fd[0], resstring, NMAX); 
		if(size < 0){
			printf("Can\'t read string\n"); 
			exit(-1);
		}
		printf("%s\n", resstring);
		close(fd[1]);
		printf("Parent exit\n");
	} else {
		close(fd[1]);
		char *buf;
		sprintf(buf, "%d", fd[0]);
		if(execl(argv[1], argv[1], buf) < 0){
			printf("Can not execute other programm!\n");
			exit(-1);
		}
		close(fd[0]);
	}
	return 0; 
}