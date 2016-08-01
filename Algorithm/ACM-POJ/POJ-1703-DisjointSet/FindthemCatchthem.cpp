/*
# Author: David - youchen.du@gmail.com
# QQ : 449195172
# Last modified:    2015-07-19 16:43
# Filename:     FindthemCatchthem.cpp
# Description: 
*/
#include <iostream>
#include <cstdio>
using namespace std;
#define SIZE 100010
int father[SIZE],relative[SIZE];
int M,N,T,a,b;
char flag;
void MakeSet()
{
	for(int i=1;i<=N;i++)
	{
		father[i]=i;
		relative[i]=0;	
	}
}

int FindFather(int x)
{
	if(x==father[x])
		return father[x];
	int tmp=father[x];
	father[x]=FindFather(father[x]);
	relative[x]=(relative[x]==relative[tmp])?0:1;	//relative[x]=0 means that x and father[x] is the same group
	return father[x];
}
void UnionSet(int x,int y,int fx,int fy)
{
	father[fx]=fy;
	relative[fx]=(relative[x]==relative[y])?1:0;	//if relative[x]==relative[y],then x and father[x] is not the same group 
}

int main()
{
	scanf("%d",&T);
	while(T--)
	{
		scanf("%d %d",&N,&M);
		MakeSet();
		while(M--)
		{
			scanf("\n%c %d %d",&flag,&a,&b);
			int fa=FindFather(a),fb=FindFather(b);
			if(flag=='A')
			{
				if(fa!=fb)
				{
					printf("Not sure yet.\n");
					continue;
				}
				if(relative[a]==relative[b])
				{
					printf("In the same gang.\n");
					continue;
				}
				printf("In different gangs.\n");
				continue;
			}
			if(flag=='D')
			{
				if(fa!=fb)
					UnionSet(a,b,fa,fb);
			}
		}
	}
	return 0;
}

