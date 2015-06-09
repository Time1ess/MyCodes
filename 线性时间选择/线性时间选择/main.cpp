#include <iostream>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#pragma warning(disable:4996)
using namespace std;

const int MAX = 1e2;
int s[MAX];


//给定排序后的数组，在线性时间内寻找第k小的元素

int quicksort(int *a, int s, int e)
{
	int i = s, j = e;
	int key = a[s];
	while (i < j)
	{
		while (i<j&&a[j]>=key)j--;
		a[i] = a[j];
		while (i < j&&a[i] <= key)i++;
		a[j] = a[i];
	}
	a[i] = key;
	return i;
}

int LinearTimeSelect(int *a, int s,int e, int k)
{
	if (s==e)
		return a[s];
	int kth=quicksort(a, s, e);
	int j = kth - s + 1;
	if (k<=j)
		LinearTimeSelect(a, s, kth,k);
	else
		LinearTimeSelect(a, kth+1, e, k - j);
}	

int main()
{
	freopen("in.txt", "r", stdin);
	int n;
	while (cin >> n&&n > 0)
	{
		int k;
		cin >> k;
		for (int i = 0; i < n; i++)
			cin >> s[i];
		int ans = LinearTimeSelect(s,0,n-1, k);
		cout << ans << endl;
	}
	return 0;
}