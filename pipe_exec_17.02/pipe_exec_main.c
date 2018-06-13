#include <sys/types.h>
#include <unistd.h> 
#include <stdio.h>

#define NMAX 14

int main(int argc, const char** argv, const char** envp){

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
	} 
	else if (cid > 0) {
		close(fd[0]);
		size = read(fd[1], resstring, NMAX); 
		if(size < 0){
			printf("Can\'t read string\n"); 
			exit(-1);
		}
		printf("%s\n", resstring);
		close(fd[1]);
		printf("Parent exit\n");
	} else if(cid == 0){
		close(fd[1]);
		char *buf;
		printf("Child: %d\n", fd[0]);
		sprintf(buf, "%d", fd[0]);
		printf("%s\n", buf);
		if(execl("/bin/echo", "echo", buf, NULL) < 0){
			printf("Can not execute other programm!\n");
			exit(-1);
		}
		close(fd[0]);
		printf("Child exit\n");
	}
	return 0; 
}