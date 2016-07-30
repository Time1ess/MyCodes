#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <cstring>
#pragma warning(disable:4996)
using namespace std;



int devide(int n,int m)
{
	if (n < 1 || m < 1)
		return 0;
	if (n == 1 && m == 1)
		return 1;
	if (m == n)
		return 1 + devide(n, n - 1);
	if (n < m)
		return devide(n, n);
	if (m >= 1 && n >= m)
		return devide(n, m - 1) + devide(n - m, m);
}


int main()
{
	int T;
	scanf("%d", &T);
	for (int i = 1; i <= T; i++)
	{
		int n;
		scanf("%d", &n);
		int ans = devide(n,n);
		printf("Case $%d:\n%d\n", i, ans);
	}
	return 0;
}