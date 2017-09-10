#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <stdlib.h>
#include <dirent.h>
#include <string.h>


struct arg_struct {
    char pattern[10000];
    char file[10000];
    int procNum;
};

struct arg_str {
    char comm[100];
    char fileName[100];
};


void *dumf(void *argms)
{
    struct arg_str *args = (struct arg_str *)argms;
    char comm[100];
    char fileName[100];
    strcpy(comm,args->comm) ;
    strcpy(fileName,args->fileName);
    strcpy(comm,"cat ");
    strcat(comm,fileName);
    char* arg[] = {"cat", fileName,NULL};
    //printf("%s\n",fileName);
    system(comm);
}

void tostring(char str[], int num)
{
    int i, rem, len = 0, n;
 
    n = num;
    while (n != 0)
    {
        len++;
        n /= 10;
    }
    for (i = 0; i < len; i++)
    {
        rem = num % 10;
        num = num / 10;
        str[len - (i + 1)] = rem + '0';
    }
    str[len] = '\0';
}

int matchques(char left[],char right[],char line[])
{
  int i;
  char a[1000]="";
  strcat(a,left);
  strcat(a,right);
  if(strstr(line,a)!=NULL)
    {
      return 1;
    }
  for(i=0;i<=255;i++)
  {
    memset(a,0,1000);
    strcat(a,left);
    a[strlen(a)]=i;
    strcat(a,right);
    //printf("%s\n",a);
    if(strstr(line,a)!=NULL)
    {
      return 1;
    }
  }
  return 0;
}
void *byfile(void *arguments)
{
  struct arg_struct *args = (struct arg_struct *)arguments;

  char file[10000];
  char pattern[10000];
  int procNum;

  strcpy(file,args->file);
  strcpy(pattern,args->pattern);
  procNum=args->procNum;

//printf("File Name is %s \n",file);

  FILE *fp;
  int n=0;
  fp=fopen(file,"r");
  char a[10000],b[10000];
  //itoa (procNum,a,10);
  tostring(a,procNum+1);
  strcpy(b,"output/file");
  strcat(b,a);
  strcat(b,".txt");
  FILE *fp2=fopen(b,"w");
  if(fp==NULL)
  {
    printf("Invalid File %s\n",file);
  } 
  else
  { fprintf(fp2,"File Name is %s \n",file);
    char *line,ques[]="?",bef[1000],aft[1000];
    size_t buf_size=1000;
    int num=1;

    if(strstr(pattern,ques)!=NULL)
    {
      strcpy(bef,pattern);
      *(strstr(bef,ques))='\0';
      strncpy(aft,strstr(pattern,ques)+1,sizeof(strstr(pattern,ques))-1);
    }

    while(getline(&line,&buf_size,fp)!=-1)
    {
      if(strstr(pattern,ques)!=NULL)
      { 
        if(matchques(bef,aft,line))
        {
          fprintf(fp2,"%d : %s",num,line); 
          n++;        
        }
      }
      else if(strstr(line,pattern)!=NULL)
      {       
        fprintf(fp2,"%d : %s",num,line);
        n++;            
      }
      num++;
    }
    fprintf(fp2,"Number of lines matched : %d \n",n);
  }
  pthread_exit(0);
}
int main(int argc,char *argv[])
{
      int a,j;

      char str1[10000],str2[10000];
      strcpy(str1,"ls -l ");
      strcpy(str2,"| wc -l > numF");
      strcat(str1,argv[2]);
      strcat(str1,str2);
      system(str1);
      
      FILE *fp=fopen("numF","r");
      fscanf(fp,"%d",&a);
      a--;

      fclose(fp);
      system("rm numF");

      DIR *directory;
      struct dirent* file;

      char files[a][1000];
      
      char ch;

      if (argc != 3) {
          printf("Error %s\n", argv[0]);
          exit(1);
      }

      directory = opendir(argv[2]);
      if (directory == NULL) {
          printf("Error\n");
          exit(2);
      }

      char s[100000];
      j=0;
      while ((file=readdir(directory)) != NULL) 
      {
        strcpy(s,argv[2]);
        strcat(s,"/");
        strcat(s,file->d_name);
        if(j>=2) strcpy(files[j-2],s);  
        j++;
          }

          closedir(directory);

        //printf("File Name is %d \n",a);
        
        pthread_t hilo[a],new_thr;
        int i;
        int n = a;

        struct arg_struct args[n];
        
        /* Start children. */
        for (i = 0; i < n; ++i) 
        {
          
          strcpy(args[i].pattern,argv[1]);
          strcpy(args[i].file,files[i]);
          args[i].procNum = i;
          pthread_create(&hilo[i],NULL,byfile,  (void *)&args[i] );          
       }
      for(i=0;i<n;i++)   
         pthread_join(hilo[i],NULL);


    struct arg_str argms[n];

        int status;
        char num[10000],fName[10000];
      //printf("%d\n",N);
       for(i=1;i<=n;i++)
       {
        tostring(num,i);
        strcpy(fName,"./output/file");
        strcat(fName,num);
        strcat(fName,".txt");
        strcpy(argms[i].comm,"cat");
        strcpy(argms[i].fileName,fName);

        //char* arg[] = {"cat", fName,NULL};
        pthread_create(&new_thr,NULL,dumf,  (void *)&argms[i]);  
        pthread_join(new_thr,NULL);
       }


}