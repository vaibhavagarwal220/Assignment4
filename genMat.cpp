#include <bits/stdc++.h>
//#define N 50
using namespace std;

int main(int argc,char *argv[])
{

	int N=atoi(argv[1]);
	cout<<N<<" "<<N<<endl;
	cout<<N<<" "<<N<<endl;
	for(int i=0;i<N;i++)
	{
		for(int j=0;j<N;j++)
		{	
			if(j!=N-1) cout<<1<<" ";//cout<<abs(rand()%10)<<" ";
			else cout<<1;
		}
		cout<<endl;
	}
	for(int i=0;i<N;i++)
	{
		for(int j=0;j<N;j++)
		{	
			if(j!=N-1) cout<<1<<" ";//cout<<abs(rand()%10)<<" ";
			else cout<<1;
		}
		if(i!=N-1)cout<<endl;
	}
}

