#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define MAX_LEN 600

int main(int argc, const char** argv)
{    
    int msqid;
    char pathname[] = "server.c";

    key_t  key;
    int i,len,maxlen;

    struct mymsgbuf
    {
       long mtype;
       int id;
       char mtext[MAX_LEN];
    } mybuf;

    /* Create or attach message queue  */
    
    key = ftok(pathname, 0);
    
    if ((msqid = msgget(key, 0666)) < 0)
    {
       printf("Can\'t get msqid\n");
       exit(-1);
    }

  	mybuf.mtype = 1;
  	mybuf.id = getpid();
    char sbuf[MAX_LEN];
    sprintf(sbuf, "Client [pid = %d]", getpid());
    strcpy(mybuf.mtext, sbuf);
    if (msgsnd(msqid, (struct msgbuf *) &mybuf, sizeof(mybuf), 0) < 0)
    {
         printf("Can\'t send message to queue\n");
         msgctl(msqid, IPC_RMID, (struct msqid_ds *) NULL);
         exit(-1);
    }
    maxlen = 100;
    if (( len = msgrcv(msqid, (struct msgbuf *) &mybuf, sizeof(mybuf), getpid(), MSG_NOERROR)) < 0)
    {
         printf("Can\'t receive message from queue\n");
         exit(-1);
    }
    printf("Message type = %ld, Message = %s\n", mybuf.mtype, mybuf.mtext);
    return 0;    
}
