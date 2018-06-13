#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/types.h>

#define NMAX 50

int main(int argc, const char** argv){

	int fd[2], id_;
	int semid;
	key_t key;
	struct sembuf sb;
	size_t size;
	char buf[NMAX];

	if((key = ftok("sem.txt", 0)) < 0){
		printf("Can\'t generate key\n");
		exit(-1); 
	}

	if((semid = semget(key, 1, 0666 | IPC_CREAT)) < 0){
		printf("Can\'t get semid\n");
		exit(-1); 
	}

	if(pipe(fd) < 0){
		printf("Can\'t create pipe #1\n");
		exit(-1);
	}

	sb.sem_op = -1;
	sb.sem_flg = 0;
	sb.sem_num = 0;

	id_ = fork();
	if(id_ < 0){
		printf("Can not fork process!\n");
		exit(-1);
	} 
	if(id_ > 0){
		close(fd[1]);
		if(semop(semid, &sb, 1) < 0){
			printf("Can wait!\n");
		}
		printf("Lets say hello to child!\n");
		strcpy(buf, "Hello, child!");
		size = write(fd[0], buf, NMAX + 1);
		size = read(fd[0], buf, NMAX);
		if(size < 0){
			printf("Can not read message from child!\n");
			exit(-1);
		}
		printf("Message from child: %s\n", buf);
		close(fd[0]);
	}
	if(id_ == 0){
		close(fd[0]);
		sb.sem_op = 1;
		sb.sem_flg = 0;
		sb.sem_num = 0;
		if(semop(semid, &sb, 1) < 0){
			printf("Can wait!\n");
		}
		printf("Lets see my parent!\n");
		memset(buf, 0, NMAX);
		strcpy(buf, "Hello, parent!");
		size = write(fd[1], buf, NMAX + 1);
		if(size != NMAX + 1){
			printf("Can not write to parent!\n");
			exit(-1);
		}
		close(fd[1]);
	}
	return 0;
}