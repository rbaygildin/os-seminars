#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#define MAX_LEN 14
int pready = 0;
int    fd[2], result;
size_t size;
char  resstring[MAX_LEN];

void handlesSIG(int sig)
{
    pready++;
}

int main()
{
   signal(SIGUSR1, handlesSIG);
   if(pipe(fd) < 0){
     printf("Can\'t open pipe\n");
     exit(-1);
   }
   result = fork();
   if(result < 0) {
      printf("Can\'t fork child\n");
      exit(-1);
   } else if (result > 0) {
     /* Parent process */
      close(fd[0]);
      size = write(fd[1], "Hello, world!", MAX_LEN);
      if(size != 14){
        printf("Can\'t write all string to pipe\n");
        exit(-1);
      }
      kill(result, SIGUSR1);
      while(!pready){
      }
      close(fd[1]);
      printf("Parent exit after catching signal\n");
   } 
   else 
   {
      /* Child process */
      close(fd[1]);
      size = read(fd[0], resstring, MAX_LEN);
      if(size < 0){
         printf("Can\'t read string from pipe\n");
         exit(-1);
      }
      while(!pready){
      }
      printf("Child exit, resstring: %s\n", resstring);
      close(fd[0]);
      kill(getppid(), SIGUSR1);
      printf("Child exit after catching signal\n");
   }
   return 0;
}





