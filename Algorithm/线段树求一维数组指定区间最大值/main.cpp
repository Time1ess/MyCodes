/*
# Author: David - youchen.du@gmail.com
# QQ : 449195172
# Last modified:    2015-07-23 14:06
# Filename:     main.cpp
# Description: 使用线段树求一维数组中指定区间的最大元素 
*/
#include <iostream>
#define max(a,b) ((a)>(b))?(a):(b);
#pragma warning(disable:4996)
using namespace std;

#define N 100
struct segment
{
	int l,r,len;
	int maxval;
};
segment s[N*2];
int vals[N];
int build(int root,int l,int r)
{
	s[root].l=l;
	s[root].r=r;
	s[root].len=r-l+1;
	if(l==r)
	{
		s[root].maxval=vals[l];
		return s[root].maxval;
	}
	int mid=(l+r)/2;
	s[root].maxval=max(build(root*2,l,mid),build(root*2+1,mid+1,r));
	return s[root].maxval;
}

int query(int root, int l, int r)
{
	if (s[root].l == l&&s[root].r == r)
	{
		return s[root].maxval;
	}
	int mid = (s[root].l+s[root].r) / 2;
	if (r <= mid)
		return query(root * 2, l, r);
	else if (l > mid)
		return query(root * 2 + 1, l, r);
	else
		return max(query(root * 2, l, mid), query(root * 2 + 1, mid + 1, r));
}

int main()
{
//	freopen("input.txt", "r", stdin);
	int cnt=1;
	while(cnt<=20)
		cin>>vals[cnt++];
	cout<<cnt<<endl;
	cnt-=1;
	build(1,1,cnt);
	for(int i=1;i<=cnt;i++)
		cout<<vals[i]<<" ";
	cout<<endl;
	int l, r;
	while (cin >> l >> r)
	{
		cout << "Input l and r:";
		cout << l << " "<<r << endl;
		cout<<"The Max is "<<query(1,l,r)<<endl;
	}
	return 0;
}
