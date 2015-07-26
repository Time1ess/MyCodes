/*
# Author: David - youchen.du@gmail.com
# QQ : 449195172
# Last modified:    2015-07-23 15:01
# Filename:     Stars.cpp
# Description:	POJ-2352 
*/
#include <cstdio>
using namespace std;

int n;
int levels[32001];
int c[32001];
int Lowbit(int x)
{
	return x&(-x);
}
int Sum(int x)
{
	int s=0;
	while(x>0)
	{
		s+=c[x];
		x-=Lowbit(x);
	}
	return s;
}
void Update(int pos)
{
	while(pos<=32001)
	{
		c[pos]++;
		pos+=Lowbit(pos);
	}
}

int main()
{
	scanf("%d",&n);
	int x,y;
	for(int i=1;i<=n;i++)
	{
		scanf("%d %d",&x,&y);	
//为什么不对y进行处理,因为根据题意
//Stars are listed in ascending order of Y coordinate. Stars with equal Y coordinates are listed in ascending order of X coordinate. 
//数据按照X>Y优先级递增，所以在(x,y)之前的坐标，肯定满足纵坐标小于等于y，因此不用对y进行考虑
		levels[Sum(x+1)]++;
		Update(x+1);
	}
	for(int i=0;i<n;i++)
		printf("%d\n",levels[i]);
	return 0;
}
