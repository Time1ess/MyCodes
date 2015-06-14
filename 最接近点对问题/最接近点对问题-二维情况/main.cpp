#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <ctime>
#include <algorithm>
#pragma warning(disable:4996)
using namespace std;
const double INF = 1e20;
const int N = 100005;

struct Point
{
	double x;
	double y;
}point[N];
int n;
int tmpt[N];

bool cmpxy(const Point& a, const Point& b)
{
	if (a.x != b.x)
		return a.x < b.x;
	return a.y < b.y;
}

bool cmpy(const int& a, const int& b)
{
	return point[a].y < point[b].y;
}

double min(double a, double b)
{
	return a < b ? a : b;
}

double dis(int i, int j)
{
	return sqrt((point[i].x - point[j].x)*(point[i].x - point[j].x)
		+ (point[i].y - point[j].y)*(point[i].y - point[j].y));
}

double Closest_Pair(int left, int right,int &p1,int &p2)
{
	double d = INF;
	if (left == right)
	{
		p1 = p2 = -1;
		return d;
	}
	if (left + 1 == right)
	{
		p1 = left;
		p2 = right;
		return dis(left, right);
	}

	int mid = (left + right) >> 1;

	double d1 = Closest_Pair(left, mid,p1,p2);

	int rp1, rp2;
	double d2 = Closest_Pair(mid + 1, right,rp1,rp2);

	d = min(d1, d2);
	
	if (d == d2)
	{
		p1 = rp1;
		p2 = rp2;
	}

	int i, j, k = 0;

	//分离出宽度为d的区间
	//将所有x方向距离分隔线m的距离小于d的点挑选出来
	for (i = left; i <= right; i++)
	{
		if (fabs(point[mid].x - point[i].x) <= d)
			tmpt[k++] = i;
	}
	//按y升序排序
	sort(tmpt, tmpt + k, cmpy);

	//线性扫描
	for (i = 0; i < k; i++)
	{
		for (j = i + 1; j < k && point[tmpt[j]].y - point[tmpt[i]].y<d; j++)
		{
			double d3 = dis(tmpt[i], tmpt[j]);
			if (d > d3)
			{
				p1 = i;
				p2 = j;
				d = d3;
			}
		}
	}
	return d;
}


int main()
{
	while (true)
	{
		srand((unsigned)time(NULL));
		cout << "输入点对个数:";
		cin >> n;
		if (n < 1)break;
		for (int i = 0; i < n; i++)
		{
			point[i].x = (rand() % 1000) * 0.1;
			point[i].y = (rand() % 1000) * 0.1;
			printf("(%.1lf,%.1lf)", point[i].x, point[i].y);
		}
		cout << endl;
		int p1, p2;
		sort(point, point + n, cmpxy);
		printf("最接近点对为:(%.1lf,%.1lf)和(%.1lf,%.1lf),距离为%.1lf\n",point[p1].x
			,point[p1].y,point[p2].x,point[p2].y,Closest_Pair(0, n - 1,p1,p2) / 2);
	}
	return 0;
}
