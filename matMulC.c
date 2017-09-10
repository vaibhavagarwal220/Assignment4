#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <stdlib.h>
#define MAX 1000
int curRow,curCol; 

int ar , ac , br , bc;

 struct arg_struct {
    int row,col;
};

int A[MAX][MAX],B[MAX][MAX],C[MAX][MAX];

void nextTask();

void *multiply(void *arguments)
{
    
    

    struct arg_struct *args = (struct arg_struct *)arguments;
    int row=args->row , col=args->col ;
    int k ;

    C[row][col] = 0;

    for (k = 0; k < ac; k++)
    {
        C[row][col] += A[row][k] * B[k][col];
    }

    nextTask();
    pthread_exit(0);   
}



void nextTask()
{
    
    
    if(curRow==(ar-1)&&curCol==(bc-1))
    {
        pthread_exit(0);
    }
    else if(curRow==(ar-1))
    {
    static pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
    pthread_mutex_lock(&mutex);
        curRow=0;
        curCol++;
    pthread_mutex_unlock(&mutex);
    }
    else
    {   
    static pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
    pthread_mutex_lock(&mutex);
        curRow++;
    pthread_mutex_unlock(&mutex);
    }

    struct arg_struct argms;
    argms.row=curRow;
    argms.col=curCol;
    //printf("%d %d\n",curRow, curCol);
    multiply((void *)&argms);
       
}

 
int main()
{
    int i,j;
    scanf("%d %d",&ar,&ac);
    scanf("%d %d",&br,&bc);

    if(ac!=br) 
        {
            printf("Incompatible Matrices\n"); 
            return 0;
        }

    for (i = 0; i < ar; i++)
    {
        for (j = 0; j < ac; j++)
        {
           scanf("%d", &A[i][j]);
        }
       
    }
    for (i = 0; i < ac; i++)
    {
        for (j = 0; j < bc; j++)
        {
           scanf("%d", &B[i][j]);
        }  
    }

    pthread_t hilo[ar];
    
    struct arg_struct args[ar];

    curRow=9;
    curCol=0;



    for (i = 0; i < 10; i++)
        {
            args[i].row = i;
            args[i].col = 0;

            //printf("Incompatible Matrices\n"); 

            pthread_create(&hilo[i] , NULL,multiply,  (void *)&args[i]);          
        }

        


    for (i = 0; i < ar; i++)
         pthread_join(hilo[i],NULL);
    for (i = 0; i < ar; i++)
    {
        for (j = 0; j < bc; j++)
           printf("\t%d\t ", C[i][j]);
        printf("\n");
    }

    

 
    return 0;
}