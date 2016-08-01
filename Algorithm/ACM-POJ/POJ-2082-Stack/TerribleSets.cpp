/*
# Author: David - youchen.du@gmail.com
# QQ : 449195172
# Last modified:	2015-07-18 14:43
# Filename:		TerribleSets.cpp
# Description:紧贴X轴有一些互相挨着的矩形，给定每个矩形的长宽，问他们可以形成的最大矩形面积是多少 
*/
#include <iostream>
#include <stack>
#include <cstdio>
using namespace std;

struct rec
{
	int w;
	int h;
}data;
int main()
{
	int n,ans,i,lasth,totalw,curarea;
	while(scanf("%d",&n)&&n!=-1)
	{
		ans=0;
		stack<rec> s;
		lasth=0;
		for(i=0;i<n;i++)
		{
			scanf("%d %d",&data.w,&data.h);
			if(data.h>lasth)
			{
				s.push(data);
			}
			else
			{
				totalw=0;
				curarea=0;
				while(!s.empty()&&s.top().h>data.h)
				{
					totalw+=s.top().w;
					curarea=totalw*s.top().h;
					if(curarea>ans)
						ans=curarea;
					s.pop();
				}
				totalw+=data.w;
				data.w=totalw;
				s.push(data);
			}
			lasth=data.h;
		}
		totalw=0;
		curarea=0;
		while(!s.empty())
		{
			totalw+=s.top().w;
			curarea=totalw*s.top().h;
			if(curarea>ans)
				ans=curarea;
			s.pop();
		}
		printf("%d\n",ans);
	}
	return 0;
}
