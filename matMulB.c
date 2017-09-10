#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <stdlib.h>
#include <time.h>
 

 struct arg_struct {
    int ac,row,col;
};

int A[1000][1000],B[1000][1000],C[1000][1000];

void *multiply(void *arguments)
{
    


    struct arg_struct *args = (struct arg_struct *)arguments;
    int row=args->row , col=args->col , ac=args->ac;
    int k ;

    C[row][col] = 0;

    for (k = 0; k < ac; k++)
    {
        C[row][col] += A[row][k] * B[k][col];
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
        //printf("Enter Row %d of A: ",i+1);
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

    pthread_t hilo[ar][bc];
    
    struct arg_struct args[ar][bc];

    clock_t t=clock();
    for (i = 0; i < ar; i++)
        {
            for (j = 0; j < bc; j++) 
            {      

            args[i][j].ac = ac;
            args[i][j].row = i;
            args[i][j].col = j;

            pthread_create(&hilo[i][j] , NULL,multiply,  (void *)&args[i][j] );          
            }
        }

    for (i = 0; i < ar; i++)
        {
            for (j = 0; j < bc; j++) 
            {      
                     pthread_join(hilo[i][j],NULL);
  
            }
        }
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