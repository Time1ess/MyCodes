#include <iostream>
#include <cstdlib>
#include <cstring>
#include <cstdio>
#include <cmath>
#include <algorithm>
#pragma warning(disable:4996)

using namespace std;

const int SIZE = 7;

int s[SIZE][SIZE], m[SIZE][SIZE];

int MatrixChain(int n, int m[SIZE][SIZE], int s[SIZE][SIZE], int *p)
{
	for (int i = 1; i <= n; i++)
		m[i][i] = 0;

	for (int r = 2; r <= n; r++)//r为当前计算的链长（子问题规模） 
	{
		for (int i = 1; i <= n - r + 1; i++)//n-r+1为最后一个r链的前边界 
		{
			int j = i + r - 1; // 计算前边界为r，链长为r的链的后边界

			m[i][j] = m[i][i] + m[i + 1][j] + p[i - 1] * p[i] * p[j];//将链A[i:j]划分为A(i) * ( A[i+1:j] )  

			s[i][j] = i;//链从i处断开

			for (int k = i + 1; k < j; k++)
			{
				int t = m[i][k] + m[k + 1][j] + p[i - 1] * p[k] * p[j];
				if (t < m[i][j])
				{
					m[i][j] = t;
					s[i][j] = k;
				}
			}
		}
	}
	return m[1][SIZE - 1];
}

void Traceback(int i, int j, int s[SIZE][SIZE])
{
	if (i == j) return;
	Traceback(i, s[i][j], s);
	Traceback(s[i][j] + 1, j, s);
	cout << "Multiply A" << i << "," << s[i][j];	//A2,2 and A3,3表示A2*A3
	cout << " and A" << (s[i][j] + 1) << "," << j << endl;	//A1,1 and A2,3表示A1*(A2*A3)
}

int main()
{
	int p[SIZE] = { 30, 35, 15, 5, 10, 20, 25 };

	cout << "矩阵的最少计算次数为：" << MatrixChain(6, m, s, p) << endl;
	cout << "矩阵最优计算次序为：" << endl;
	Traceback(1, 6, s);
	return 0;

}