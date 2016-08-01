#include <iostream>
#include <cstring>
#include <cmath>
#pragma warning(disable:4996)
using namespace std;
#define MAX 110
int m[MAX];
int band[MAX][MAX];
int price[MAX][MAX];
int dp[MAX][MAX];
int N;


int min(int a, int b)
{
	return a > b ? b : a;
}
int max(int a, int b)
{
	return a > b ? a : b;
}


double DP()
{
}




int main()
{
	freopen("D:\\MyCodes\\ACM-POJ\\Debug\\a.txt","r", stdin);
	int n;
	cin >> n;
	while (n--)
	{
		memset(m, 0, sizeof(m));
		memset(band, 0, sizeof(band));
		memset(price, 0, sizeof(price));
		memset(dp, -1, sizeof(dp));
		cin >> N;
		for (int i = 1; i <= N;i++)
		{
			cin >> m[i];
			for (int j = 1; j <= m[i]; j++)
			{
				cin >> band[i][j];
				cin >> price[i][j];
			}
		}
		double ans = DP();
		printf("%.3f\n", ans);
	}
	return 0;
}