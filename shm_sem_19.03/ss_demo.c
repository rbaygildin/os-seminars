#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/sem.h>
#include <string.h>
#include <stdio.h>
#include <errno.h>

#define NMAX 1

int main()
{
      int *array; 
      int semid;
      int shmid;
      struct sembuf sb;
      int new = 1; 
      int id_;
      char pathname[] = "ss_demo.c"; 
      char sempath[] = "Makefile";
      key_t skey; 
      key_t semkey;

      if((skey = ftok(pathname,0)) < 0)
      {
           printf("Can't generate keyn");
           exit(-1);
      }
      if((semkey = ftok(sempath,0)) < 0)
      {
           printf("Can't generate keyn");
           exit(-1);
      }

      if((semid = semget(semkey, 1, 0666 | IPC_CREAT)) < 0){
        printf("Can\'t get semid\n");
        exit(-1); 
      }

      if((shmid = shmget(skey, NMAX * sizeof(int), 0666 |IPC_CREAT | IPC_EXCL)) < 0)
      {
            if(errno != EEXIST)
            {       
              printf("Can't create shared memoryn");
              exit(-1);
            }
            else
            {

                if((shmid = shmget(skey, NMAX * sizeof(int), 0)) < 0)
                {
                    printf("Can't find shared memoryn");
                    exit(-1);
                }
                new = 0;
            }
      }
      sb.sem_op = -1;
      sb.sem_flg = SEM_UNDO;
      sb.sem_num = 0;
      id_ = fork();
      if(id_ < 0){
        printf("Can not fork process!\n");
        exit(-1);
      } 
      if(id_ > 0){
        if((array = (int *) shmat(shmid, NULL, 0)) == (void*)(-1)){
          printf("Can't attach shared memoryn");
          exit(-1);
        }
        int i = 1;
        array[0] = 1;
        while(i <= 6){
          sb.sem_op = -1;
          sb.sem_flg = SEM_UNDO;
          sb.sem_num = 0;
          printf("Parent: %d\n", i);
          if(semop(semid, &sb, 1) < 0){
            printf("Can wait!\n");
          }
          i = array[0];
          usleep(20);
        } 
      }
      if(id_ == 0){
        if((array = (int *) shmat(shmid, NULL, 0)) == (void *)(-1)){
          printf("Can't attach shared memoryn");
          exit(-1);
        }
        sb.sem_op = 1;
        sb.sem_flg = SEM_UNDO;
        sb.sem_num = 0;
        int i = 1;
        while(i <= 6){
          array[0]++;
          i = array[0];
          printf("Child: %d\n", i);
          if(semop(semid, &sb, 1) < 0){
            printf("Can wait!\n");
          }
          usleep(20);
        } 
      }
      if(shmdt(array) < 0){
          printf("Can't detach shared memoryn");
          exit(-1);
      }
      return 0;
} 