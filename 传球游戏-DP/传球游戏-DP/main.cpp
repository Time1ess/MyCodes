/*【题目描述】
    上体育课的时候，小蛮的老师经常带着同学们一起做游戏。这次，老师带着同学们一起做传球游戏。
    游戏规则是这样的：n个同学站成一个圆圈，其中的一个同学手里拿着一个球，当老师吹哨子时开始
	传球，每个同学可以把球传给自己左右的两个同学中的一个（左右任意），当老师再次吹哨子时，传
	球停止，此时，拿着球没传出去的那个同学就是败者，要给大家表演一个节目。
    聪明的小蛮提出一个有趣的问题：有多少种不同的传球方法可以使得从小蛮手里开始传的球，传了m次
	以后，又回到小蛮手里。两种传球的方法被视作不同的方法，当且仅当这两种方法中，接到球的同学
	按接球顺序组成的序列是不同的。比如有3个同学1号、2号、3号，并假设小蛮为1号，球传了3次回到
	小蛮手里的方式有1->2->3->1和1->3->2->1，共2种。
	*/

#include <iostream>
#include <cstring>
using namespace std;
#define MAXSIZE 31
int d[MAXSIZE][MAXSIZE];
int R[MAXSIZE], L[MAXSIZE];
int m, n;

int max(int a, int b)
{
	return a > b ? a : b;
}

void dp(int p, int t)
{
	if (t == m)
	{
		if (p == 1)
			d[p][t] = 1;
		else
			d[p][t] = 0;
		return;
	}
	if (d[p][t] != -1)
		return;
	d[p][t] = 0;
	dp(p%n + 1, t + 1);
	d[p][t] += d[p%n + 1][t + 1];
	int p1 = p - 1;
	if (p1 == 0)p1 = n;
	dp(p1, t + 1);
	d[p][t] += d[p1][t + 1];
}

int main()
{
	while (cin >> n >> m)
	{
		memset(d, -1, sizeof(d));
		dp(1, 0);
		cout << d[1][0] << endl;
	}
	return 0;
}