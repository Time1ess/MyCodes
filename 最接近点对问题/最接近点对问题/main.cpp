#include <iostream>
#include <cstdlib>
#include <cstring>
#include <cstdio>
#include <ctime>
#pragma warning(disable:4996)
const int SIZE = 1e5;
using namespace std;

float P[SIZE];

struct Pair
{
	float dis;
	float d1, d2;
};

float Min(float *p, int l, int r)
{
	float s = 1 << 30;
	for (int i = l; i <= r;i++)
	if (s > p[i])
		s = p[i];
	return s;
}

float Max(float *p, int l, int r)
{
	float s = -1 << 30;
	for (int i = l; i <= r; i++)
	if (s < p[i])
		s = p[i];
	return s;
}

void swap(float &a, float &b)
{
	float t = a;
	a = b;
	b = t;
}

int partition(float *s, float key, int l, int r)
{
	int i = l - 1, j = r + 1;

	while (true)
	{
		while (s[++i] < key&&i < r);
		while (s[--j]>key);
		if (i >= j)
			break;
		swap(s[i], s[j]);
	}
	return j;
}

Pair cPair(float *s, int l, int r)
{
	Pair min_d = { 1 << 30, 0, 0 };
	if (r - l < 1)return min_d;

	float max = Max(s, l, r), min = Min(s, l, r);
	float m = (max + min) / 2;

	int j = partition(s, m, l, r);	//以m为划分排序，j为分隔点

	Pair d1 = cPair(s, l, j), d2 = cPair(s, j + 1, r);	//分治，对l~j部分和j+1~r部分分别求最近点对
	
	//对分隔点附近最近点对进行判断
	float p = Max(s, l, j), q = Min(s, j + 1, r);	
	if (d1.dis < d2.dis)
	{
		if ((q - p) < d1.dis)
		{
			min_d.dis = q - p;
			min_d.d1 = q;
			min_d.d2 = p;
			return min_d;
		}
		else
			return d1;
	}
	else
	{
		if ((q - p) < d2.dis)
		{
			min_d.dis = q - p;
			min_d.d1 = q;
			min_d.d2 = p;
			return min_d;
		}
		else
			return d2;
	}
}

float Random()
{
	float result = rand() % 10000;
	return result*0.01;
}

int input(float s[])
{
	int length;
	cout << "输入点的数目： ";
	cin >> length;
	cout << "点集在X轴上坐标为：";
	for (int i = 0; i<length; i++)
	{
		s[i] = Random();
		cout << s[i] << " ";
	}

	return length;
}



int main()
{
	srand((unsigned)time(NULL));
	int m;
	Pair d;
	while (true)
	{
		m = input(P);
		d = cPair(P, 0, m - 1);
		cout << endl << "最近点对坐标为： (d1:" << d.d1 << ",d2:" << d.d2 << ")";
		cout << endl << "这两点距离为： " << d.dis << endl;
	}
	return 0;
}