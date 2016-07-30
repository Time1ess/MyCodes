#include <iostream>
#include <cstring>
#include <cstdio>
#include <cmath>
#include <cstdlib>
#pragma warning(disable:4996)
using namespace std;

const int size = 8;

int a[size+1][size+1];


void Table()
{
	int n = size;
	for (int i = 1; i <= n; i++)
		a[1][i] = i;
	
	int m = 1;
	int c = log(n)/log(2);
	for (int s = 1; s <= c; s++)		//共填写log(n)次
	{
		n >>= 1;
		for (int k = 1; k <= n; k++)	//填写第k块	
		{
			for (int i = m + 1; i <= m * 2; i++)	
			{
				for (int j = m + 1; j <= m * 2; j++)
				{
					a[i][j + (k - 1)*m*2] = a[i - m][j + (k - 1)*m*2 - m];//用左上填写右下
					a[i][j + (k - 1)*m*2 - m] = a[i - m][j + (k - 1)*m*2];//用右上填写左下
				}
			}
		}
		m <<= 1;
	}
}

void output(int n)
{
	for (int i = 1; i <= n; i++)
	{
		for (int j = 1; j <= n; j++)
		{
			cout << a[i][j] << " ";
		}
		cout << endl;
	}
}


int main()
{
	Table();
	output(size);
	return 0;
}