#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <time.h>
#include <unistd.h>

#define MAX_LEN 600

int msqid;

void handleTermination(int sign)
{
    msgctl(msqid, IPC_RMID, (struct msqid_ds *) NULL);
    printf("Server closed\n");
    exit(0);
}

int main(int argc, const char** argv)
{

    if(signal(SIGINT, handleTermination) == SIG_ERR)
    {
        printf("Can\'t bind handler function to signal!\n");
        exit(-1);
    }

    char pathname[] = "server.c";
    key_t  key;
    int len, maxlen;

    struct mymsgbuf
    {
       long mtype;
       int id;
       char mtext[MAX_LEN];
    } mybuf;
    
    key = ftok(pathname, 0);
    
    if ((msqid = msgget(key, 0666 | IPC_CREAT)) < 0)
    {
       printf("Can\'t get message queue\n");
       exit(-1);
    }
    
    while (1) 
    {
       if (msgrcv(msqid, (struct msgbuf *) &mybuf, sizeof(mybuf), 1, MSG_NOERROR) < 0)
       {
         printf("Can\'t receive message from queue\n");
         exit(-1);
       }
       printf("Message type = %ld, Message = %s\n", mybuf.mtype, mybuf.mtext);
       mybuf.mtype = mybuf.id;
       char buf[MAX_LEN];
       time_t rawTime;
       time(&rawTime);
       struct tm *timeInfo = localtime(&rawTime);
       sprintf(buf, "Response from server [Server pid = %d, Date = %s]", getpid(), asctime(timeInfo));
       strcpy(mybuf.mtext, buf);
       
       if (msgsnd(msqid, (struct msgbuf *) &mybuf, sizeof(mybuf), 0) < 0)
       {
         printf("Can\'t send message to queue\n");
         msgctl(msqid, IPC_RMID, (struct msqid_ds *) NULL);
         exit(-1);
       }
    }    
    return 0;       
}
