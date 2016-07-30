#include <iostream>
#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <algorithm>
#include <queue>
#pragma warning(disable:4996)
using namespace std;
const int SIZE = 10;

queue<char> qs;

void LCSLength(char *a, char *b,int n,int m,int c[SIZE][SIZE])
{
	int i, j;
	for (i = 1; i <= n; i++)
		c[i][0] = 0;
	for (i = 1; i <= m; i++)
		c[0][i] = 0;
	for (int i = 1; i <= n; i++)
	{
		for (int j = 1; j <= m; j++)
		{
			if (a[i] == b[j])
			{
				c[i][j] = c[i - 1][j - 1] + 1;
			}
			else if (c[i - 1][j]>c[i][j - 1])
			{
				c[i][j] = c[i - 1][j];
			}
			else
			{
				c[i][j] = c[i][j - 1];
			}
		}
	}
}

void LCS(int i, int j, char *x, int c[SIZE][SIZE])
{
	if (i == 0 || j == 0)
		return;
	if (c[i][j] == c[i - 1][j - 1] + 1)
	{
		LCS(i - 1, j - 1, x, c);
		cout << x[i] << " ";
	}
	else if (c[i - 1][j] > c[i][j - 1])
	{
		LCS(i - 1, j, x, c);
	}
	else
	{
		LCS(i, j - 1, x, c);
	}
}

int main()
{
	char x[] = { ' ', 'A', 'B', 'C', 'B', 'D', 'A', 'B' };
	char y[] = { ' ', 'B', 'D', 'C', 'A', 'B', 'A' };
	int c[SIZE][SIZE];
	int n = 7, m = 6;
	memset(c, 0, sizeof(c));
	LCSLength(x, y, n,m,c);
	while (!qs.empty())
	{
		cout << qs.front() << " ";
		qs.pop();
	}
	cout << endl;
	LCS(n, m, x, c);
	return 0;
}