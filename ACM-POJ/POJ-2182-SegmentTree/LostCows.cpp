/*
# Author: David - youchen.du@gmail.com
# QQ : 449195172
# Last modified:    2015-07-20 15:41
# Filename:     LostCows.cpp
# Description: 
*/
#include <cstdlib>
#include <cstdio>
using namespace std;


int small[10000],ans[10000];
struct segment
{
	int rc,lc,len;
};

segment s[30000];

void build(int v,int lc,int rc)
{
	s[v].lc=lc;
	s[v].rc=rc;
	s[v].len=rc-lc+1;
	if(lc==rc)
		return;
	int mid=(lc+rc)/2;
	build(2*v,lc,mid);
	build(2*v+1,mid+1,rc);
}

int query(int v,int k)
{
	s[v].len--;
	if(s[v].lc==s[v].rc)
		return s[v].lc;
	else if(k<=s[2*v].len)
	{
		return query(2*v,k);
	}
	else
	{
		return query(2*v+1,k-s[v*2].len);
	}
}
int main()
{
	int n,i;
	scanf("%d",&n);
	for(i=2;i<=n;i++)
		scanf("%d",&small[i]);
	small[1]=0;
	build(1,1,n);
	for(i=n;i>=1;i--)
	{
		ans[i]=query(1,small[i]+1);
	}
	for(i=1;i<=n;i++)
		printf("%d\n",ans[i]);
	return 0;
}
