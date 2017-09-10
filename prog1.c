#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main()
{
	int level=2,i,stat,stat2;
	pid_t paid,paid2,ppid;
	for(i=0;i<level;i++)
	{
		paid=fork();
		if(paid!=0) paid2=fork();
		if(paid&&paid2)
			{
				ppid=getpid();
				printf("Parent : %ld\n",(long)ppid);
				printf("Child 1 : %ld  Child 2 : %ld \n",(long)paid,(long)paid2);
				break;
			}
	}
	waitpid(paid,&stat,0);
    waitpid(paid2,&stat2,0);
	//wait(10000000);

	return 0;
}