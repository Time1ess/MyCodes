/*
# Author: David - youchen.du@gmail.com
# QQ : 449195172
# Last modified:    2015-07-18 13:28
# Filename:     main.cpp
# Description: 
*/
#include <iostream>
#include <cstdio>
using namespace std;

void merge(int a[],int b[],int low,int mid,int high)
{
	int s=low,t=mid+1,k=low;
	while(s<=mid&&t<=high)
	{
		if(a[s]<a[t])
		{
			b[k]=a[s];
			s++;
		}
		else
		{
			b[k]=a[t];
			t++;
		}
		k++;
	}
	if(s==mid+1)
	{
		for(int i=k;i<=high;i++)
			b[i]=a[t++];
	}
	else
	{
		for(int i=k;i<=high;i++)
			b[i]=a[s++];
	}
	for(int i=low;i<=high;i++)
		a[i]=b[i];
}
void MergeSort(int a[],int b[],int low,int high)
{
	if(low<high)
	{
		int mid=(low+high)/2;
		MergeSort(a,b,low,mid);
		MergeSort(a,b,mid+1,high);
		merge(a,b,low,mid,high);
	}
}
int main()
{
	int n;
	while(~scanf("%d",&n)&&n>0)
	{
		
		int *in=new int[n];
		int *tmp=new int[n];
		int i;
		for(i=0;i<n;i++)
			scanf("%d",&in[i]);
		printf("Ori:");
		for(i=0;i<n;i++)
			printf("%d ",in[i]);
		printf("\n");
		MergeSort(in,tmp,0,n-1);
		printf("Merge:");
		for(i=0;i<n;i++)
			printf("%d ",in[i]);
		printf("\n");
		delete[] in;
		delete[] tmp;
	}
	return 0;
}
