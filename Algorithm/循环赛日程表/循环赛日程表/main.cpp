//2d11 分治法，循环赛事日程表
#include <iostream>    
#include <math.h>
using namespace std;

void Table(int k, int n, int **a);
void input(int &k);
void output(int **a, int n);

int main()
{
	int k;
	input(k);

	int n = 1;
	//n=2k(k>=1)个选手参加比赛
	for (int i = 1; i <= k; i++)
		n *= 2;

	//根据n动态分配二维数组a
	int **a = new int *[n + 1];
	for (int i = 0; i <= n; i++)
	{
		a[i] = new int[n + 1];
	}


	Table(k, n, a);

	cout << "循环赛事日程表为：" << endl;
	output(a, n);

	//释放空间
	for (int i = 0; i <= n; i++)
	{
		delete[] a[i];
	}
	delete[] a;
	cin.get();
	cin.get();
	return 0;
}

void input(int &k)
{
	cout << "请输入k值：" << endl;
	cin >> k;
}

void output(int **a, int n)
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

void Table(int k, int n, int **a)
{
	for (int i = 1; i <= n; i++)
		a[1][i] = i;//设置日程表第一行

	int m = 1;//每次填充时，起始填充位置
	for (int s = 1; s <= k; s++)
	{
		n /= 2;
		for (int t = 1; t <= n; t++)
		{
			for (int i = m + 1; i <= 2 * m; i++)//控制行
			{
				for (int j = m + 1; j <= 2 * m; j++)//控制列
				{
					a[i][j + (t - 1)*m * 2] = a[i - m][j + (t - 1)*m * 2 - m];//右下角等于左上角的值
					a[i][j + (t - 1)*m * 2 - m] = a[i - m][j + (t - 1)*m * 2];//左下角等于右上角的值
				}

			}
		}
		m *= 2;
	}
}