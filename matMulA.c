#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <stdlib.h>
#include <time.h>
 

 struct arg_struct {
    int ar,ac,j;
};

int A[1000][1000],B[1000][1000],C[1000][1000];

void *multiply(void *arguments)
{
    
    struct arg_struct *args = (struct arg_struct *)arguments;
    
    int j=args->j , ar=args->ar , ac=args->ac;

       // printf("\n\n%d %d\n",j,ar);

    int i , k ;
    for (i = 0; i < ar; i++)
    {
            C[i][j] = 0;            
            for (k = 0; k < ac; k++)
            {
                C[i][j] += A[i][k] * B[k][j];
            }
    }
    pthread_exit(0);
}
 
int main()
{
    int ar , ac , br , bc , i , j;
    //printf("Enter Row and Column for A : ");
    scanf("%d %d",&ar,&ac);
    //printf("Enter Row and Column for B : ");
    scanf("%d %d",&br,&bc);

    if(ac!=br) 
        {
            printf("Incompatible Matrices\n"); 
            return 0;
        }

    for (i = 0; i < ar; i++)
    {
      //  printf("Enter Row %d of A: ",i+1);
        for (j = 0; j < ac; j++)
        {

           scanf("%d", &A[i][j]);
        }
       
    }
    for (i = 0; i < ac; i++)
    {
        //printf("Enter Row %d of B: ",i+1);
        for (j = 0; j < bc; j++)
        {
           scanf("%d", &B[i][j]);
        }  
    }

    pthread_t hilo[bc];    
    struct arg_struct args[bc];

    clock_t t=clock();
    for (i = 0; i < bc; i++) 
        {      

            args[i].ar = ar;
            args[i].ac = ac;
            args[i].j = i;
         pthread_create(&hilo[i],NULL,multiply,  (void *)&args[i] );          
       }

    for(i=0;i<bc;i++)   
         pthread_join(hilo[i],NULL);

             t=clock()-t;
        double time_taken=(double)t/(double)CLOCKS_PER_SEC;
        printf("Time Taken : %lf\n",time_taken);

    

    //printf("Result matrix is \n");
    for (i = 0; i < ar; i++)
    {
//        for (j = 0; j < bc; j++)
           //printf("%d ", C[i][j]);
        //printf("\n");
    }

    

 
    return 0;
}