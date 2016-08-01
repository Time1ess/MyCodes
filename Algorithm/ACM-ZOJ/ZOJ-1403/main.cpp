/*
# Author: David - youchen.du@gmail.com
# QQ : 449195172
# Last modified:    2015-07-18 12:36
# Filename:     main.cpp
# Description: 
*/
#include <iostream>
#include <cstring>
#include <algorithm>
#include <cstdio>
#include <cmath>
using namespace std;

bool cmp(int a,int b)
{
	return a>b;
}
char letters[15];
int values[15],target;

void process(int len)
{
	int v,w,x,y,z;
	for(v=0;v<len;v++)
	{
		for(w=0;w<len;w++)
		{
			if(v!=w)
			{
				for(x=0;x<len;x++)
				{
					if(v!=x&&w!=x)
					{
						for(y=0;y<len;y++)
						{
							if(v!=y&&w!=y&&x!=y)
							{
								for(z=0;z<len;z++)
								{
									if(v!=z&&w!=z&&x!=z&&y!=z)
									{
										double ans=values[v]-pow(values[w],2.0)+pow(values[x],3.0)-pow(values[y],4.0)+pow(values[z],5.0);
										if(abs(ans-target)<1e-5)
										{
											printf("%c%c%c%c%c\n",values[v]-1+'A',values[w]-1+'A',
													values[x]-1+'A',values[y]-1+'A',values[z]-1+'A');
											return;
										}
									}
								}
							}
						}
					}
				}
			}
		}
	}
	printf("no solution\n");
}

int main()
{
	while(~scanf("%d %s",&target,letters))
	{
		if(target==0&&strcmp(letters,"END")==0)
		{
			return 0;
		}
		int i=0;
		while(letters[i])
		{
			values[i]=letters[i]-'A'+1;
			i++;
		}
		sort(values,values+i,cmp);
		process(i);
	}
	return 0;
}
