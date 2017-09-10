#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>

void *func(void *a){

         //printf("thread %lld\n", (long long int)pthread_self());
         pthread_exit(0);
}

void *funcproc(pid_t mypid)
{
	     int stat;
         waitpid(mypid,&stat,0);
         //printf("process %ld\n", (long)mypid);
}


int main(int argc, char *argv[])
{
  int i,n=10000;
  pid_t pids[n];
  pthread_t hilo[n];


  if(argc==1) {printf("Invalid number of arguments");return 0;}

  if(argv[1][0] == '1') goto forking;
  else goto threading;

forking:

  for (i = 0; i < n; ++i) 
  {
    if ((pids[i] = fork()) < 0) 
	  {
    	perror("fork");
    	abort();
  	  } 
    else if (pids[i] == 0) 
      {
        funcproc(getpid());
        exit(0);
      }
	  }
	  return 0;
threading:

   for(i=0;i<n;i++)
	   pthread_create(&hilo[i],NULL, func, NULL);

   for(i=0;i<n;i++)   
	   pthread_join(hilo[i],NULL);

   //pthread_create(&hilo2,NULL, func, NULL);
   return 0;

		//printf("Main thread finished");


}