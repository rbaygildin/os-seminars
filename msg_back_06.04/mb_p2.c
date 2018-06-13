#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAXLEN 60

int main(int argc, const char** argv){

	srand(time(NULL));

	int msqid; key_t key; 
	int i, len; 

	struct mymsgbuf {
		long mtype;
		int res; 
	} mybuf;

	if((key = ftok(argv[1], 0)) < 0){
		printf("Can\'t generate key\n");
		exit(-1); 
	}

	if((msqid = msgget(key, 0666)) < 0){ 
		printf("Can\'t get msqid\n");
		exit(-1);
	}
	while(1){
		if(msgrcv(msqid, (struct msgbuf *) &mybuf, MAXLEN, 2, MSG_NOERROR) < 0){
			printf("Can\'t receive message from queue\n"); 
			msgctl(msqid, IPC_RMID, (struct msqid_ds *) NULL);
			exit(-1);
		}
		mybuf.res *= mybuf.res;
		mybuf.mtype = 1;

		if (msgsnd(msqid, (struct msgbuf *) &mybuf, sizeof(mybuf), MSG_NOERROR) < 0){
			printf("Can\'t send message to queue\n"); 
			msgctl(msqid, IPC_RMID, (struct msqid_ds *) NULL);
			exit(-1); 
		}
		break;
	}

	return 0; 
}