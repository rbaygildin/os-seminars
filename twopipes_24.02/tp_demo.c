#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/types.h>

#define NMAX 50

int main(int argc, const char** argv){

	int fd1[2], fd2[2], id_;
	size_t size;
	char buf[NMAX];
	if(pipe(fd1) < 0){
		printf("Can\'t create pipe #1\n");
		exit(-1);
	}
	if(pipe(fd2) < 0){
		printf("Can\'t create pipe #2\n");
		exit(-1);
	}
	id_ = fork();
	if(id_ < 0){
		printf("Can not fork process!\n");
		exit(-1);
	} 
	if(id_ > 0){
		close(fd1[1]);
		strcpy(buf, "Hello, child!");
		size = write(fd1[0], buf, NMAX + 1);
		close(fd1[0]);
		close(fd2[1]);
		size = read(fd2[0], buf, NMAX);
		if(size < 0){
			printf("Can not read message from parent!\n");
			exit(-1);
		}
		printf("Message from child: %s\n", buf);
		close(fd2[0]);
	}
	if(id_ == 0){
		close(fd1[0]);
		strcpy(buf, "Hello, child!");
		size = read(fd1[1], buf, NMAX);
		if(size < 0){
			printf("Can not read message from parent!\n");
			exit(-1);
		}
		printf("Message from parent: %s\n", buf);
		memset(buf, 0, NMAX);
		close(fd1[1]);
		close(fd2[0]);
		strcpy(buf, "Hello, parent!");
		size = write(fd2[1], buf, NMAX + 1);
		if(size != NMAX + 1){
			printf("Can not write to parent!\n");
			exit(-1);
		}
		close(fd2[1]);
	}
	return 0;
}