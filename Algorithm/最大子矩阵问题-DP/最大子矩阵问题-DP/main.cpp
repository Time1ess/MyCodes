#include <iostream>
#include <cstdlib>
#include <cstring>
#include <cstdio>
#include <ctime>
#pragma warning(disable:4996)
using namespace std;

const int SIZE = 1e3+10;
int A[SIZE][SIZE];


int MaxSum(int *s, int len)
{
	int sum = -1 << 30, b = 0;
	for (int i = 1; i <= len; i++)
	{
		b += s[i];	//此时b代表b[i-1],为i之前最长子串和
		if (b<s[i])	//此时b代表b[i],为i及i之前最长子串和,和s[i]比较大小
			b = s[i];
		if (b > sum)
		{
			sum = b;
		}
	}
	return sum;
}

int MaxSum2(int s[SIZE][SIZE], int n, int m)
{
	int sum = -1 << 30;
	int *b = new int[m+1];
	for (int i = 1; i <= n; i++)	//枚举行
	{
		for (int k = 1; k <= m; k++)
			b[k] = 0;
		for (int j = i; j <= n; j++)	//从第i行开始计算
		{
			for (int k = 1; k <= m; k++)
			{
				b[k] += s[j][k];	//b[k]为从第i行到第j行纵向第k列之和
				//将纵向依次按列相加使用MaxSum求得一维空间上最大值即为二维上最大值
				int max = MaxSum(b, m);
				if (max > sum)
				{
					sum = max;
				}
			}
		}
	}
	return sum;
}

void Input(int s[SIZE][SIZE],int &r,int &c)
{
	int rows,cols;
	cout << "Enter rows:";
	cin >> rows;
	cout << "Enter cols:";
	cin >> cols;
	//len = rand() % 100 + 2;
	for (int i = 1; i <= rows; i++)
		for(int j=1;j<=cols;j++)
			s[i][j] = rand() % 100 - 50;
	//cin >> s[i];
	c = cols;
	r = rows;
}

void Output(int s[SIZE][SIZE], int r,int c)
{
	for (int i = 1; i <= r; i++)
	{
		for (int j = 1; j <= c; j++)
		{
			cout.width(3);
			cout << s[i][j] << " ";
		}
		cout << endl;
	}
}

int main()
{
	srand(time(0));
	int t = 500;
	while (t--)
	{
		int r, c;
		Input(A, r, c);
		if (r <= 0||c<=0)break;
		Output(A, r,c);
		cout << "Max Sum is:" << MaxSum2(A,r,c) << endl;
	}
	return 0;
}

