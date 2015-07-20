/*
# Author: David - youchen.du@gmail.com
# QQ : 449195172
# Last modified:    2015-07-20 15:41
# Filename:     Mayor'sPosters.cpp
# Description: 
*/
#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <cstring>
#pragma warning(disable:4996)
using namespace std;
#define N 10005

int result;
int l[N],r[N];
bool mark[N];

struct line
{
	int kind;
	int left,right;
}lines[10*N];

struct item
{
	int coord;
	int id;
}poster[2*N];

void Build(int l,int r,int v)
{
	lines[v].left=l;
	lines[v].right=r;
	if(l==r)return;
	int mid=(l+r)/2;
	Build(l,mid,v*2);
	Build(mid+1,r,v*2+1);
}

void Update(int l,int r,int v,int cover)
{
	if(lines[v].left==l&&lines[v].right==r)
	{
		lines[v].kind=cover;
		return;
	}
	if(lines[v].kind!=0&&lines[v].kind!=cover)
	{
		lines[v*2].kind=lines[v].kind;
		lines[v*2+1].kind=lines[v].kind;
		lines[v].kind=0;
	}
	int mid=(lines[v].left+lines[v].right)/2;

	if(r<=mid)
	{
		Update(l,r,v*2,cover);
	}
	else if(l>mid)
	{
		Update(l,r,v*2+1,cover);
	}
	else
	{
		Update(l,mid,v*2,cover);
		Update(mid+1,r,v*2+1,cover);
	}
}

void Cal(int v)
{
	if(lines[v].kind!=0)
	{
		if(mark[lines[v].kind]==false)
		{
			mark[lines[v].kind]=true;
			result++;
		}
	}
	else
	{
		Cal(2*v);
		Cal(2*v+1);
	}
}

int Cmp(const void *p1,const void *p2)
{
	return ((item *)p1)->coord-((item *)p2)->coord;
}

int main()
{
	int t,n,i,j;
	struct item *templ,*tempr,tl,tr;
	scanf("%d",&t);
	while(t--)
	{
		memset(lines,0,sizeof(lines));
		memset(poster,0,sizeof(poster));
		memset(mark,false,sizeof(mark));
		scanf("%d",&n);
		for(i=j=1;i<=n;i++)
		{
			scanf("%d %d",&l[i],&r[i]);
			poster[j++].coord=l[i];
			poster[j++].coord=r[i];
		}
		qsort(poster+1,n*2,sizeof(item),Cmp);
		for(i=j=1;i<=2*n;i++,j++)
		{
			poster[j].coord=poster[i].coord;
			poster[j].id=j;
			while(poster[i].coord==poster[i+1].coord)
				i++;
		}
		Build(1,j-1,1);
		for(i=1;i<=n;i++)
		{
			tl.coord=l[i];
			tr.coord=r[i];
			templ=(item *)bsearch(&tl,poster+1,j,sizeof(item),Cmp);
			tempr=(item *)bsearch(&tr,poster+1,j,sizeof(item),Cmp);
			Update(templ->id,tempr->id,1,i);
		}
		result=0;
		Cal(1);
		printf("%d\n",result);
	}
	return 0;
}
