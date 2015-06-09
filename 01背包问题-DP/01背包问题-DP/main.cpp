/*
有n个重量和价值分别为vector<int> weight, vector<int> value的物品；背包最大负重为W，求能用背包装下的物品的最大价值？
输入：n =4
weight=2, 1, 3, 2
value =3, 2, 4, 2
W=5
输出=7
*/
#include <iostream>
#include <vector>
#pragma warning(disable:4996)
using namespace std;


vector<int> w, v;
int n;
int W;
int dp[10][10];

int max(int a, int b)
{
	return a > b ? a : b;
}

int rec(int i, int j)	//递归算法，O(n)=(2^n)
{
	//从i到n号物品，选择重量不大于j的物品的最大价值  
	int res;
	if (i == n)
	{
		res = 0;
	}
	else if (j< w[i])
	{
		res = rec(i + 1, j);	//当前物品价值超过上限，从剩余物品中选择
	}
	else
	{
		res = max(rec(i + 1, j), rec(i + 1, j - w[i]) + v[i]);
		//选择（不选择当前物品在剩余物品中价值最大的）和
		//（选择当前物品并从剩余物品中选择其他的里面)的最大值
	}
	return res;
}

void DP()	//dp[i][j]表示剩余前i个物品待选且重量在j之内的最大价值
{
	for (int i = n-1; i >=0;i--)
	for (int j = 0; j <= W; j++)
	{
		if (j < w[i])
			dp[i][j] = dp[i + 1][j];
		else
			dp[i][j] = max(dp[i + 1][j], dp[i + 1][j - w[i]] + v[i]);
	}
}

void DP2()	//dp[i][j]表示在选择了前i个物品且重量在j之内的最大价值
{
	for (int i = 1; i <= n;i++)
	for (int j = 1; j <= W; j++)
	{
		if (j < w[i-1])
			dp[i][j] = dp[i - 1][j];
		else
			dp[i][j] = max(dp[i - 1][j], dp[i - 1][j - w[i-1]] + v[i-1]);
	}
}



int main()
{
	freopen("in.txt", "r", stdin);
	cin >> n;
	memset(dp, 0, sizeof(dp));
	int weight, value;
	for (int i = 1; i <= n; i++)
	{
		cin >> weight;
		w.push_back(weight);
	}
	for (int i = 1; i <= n; i++)
	{
		cin >> value;
		v.push_back(value);
	}
	cin >> W;
	int ans;
	DP2();
	ans = dp[n][W];
	cout << ans << endl;
	cin.get();
	return 0;
}
