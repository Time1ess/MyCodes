//#define LOCAL
#include <cstring>
#include <cstdio>
//#pragma warning(disable:4996)

int n, k, m;
int a[25];
int Left;

int go(int p, int d, int t)
{
	while (t--)
	{
		do
		{
			p = (p + d + n - 1) % n + 1;
		} while (a[p] == 0);
	}
	return p;
}

int main()
{
#ifdef LOCAL
	freopen("data.txt", "r", stdin);
	freopen("out.txt", "w", stdout);
#endif
	while (scanf("%d%d%d", &n, &k, &m) == 3 && n)
	{
		int cnt = 0;
		for (int i = 0; i <= n; i++)a[i] = i;
		int Left = n;
		int p1 = n, p2 = 1;
		while (Left)
		{
			p1 = go(p1, 1, k);
			p2 = go(p2, -1, m);
			if (cnt++)printf(",");
			printf("%3d", p1); Left--;
			if (p2 != p1)
			{
				printf("%3d", p2);
				Left--;
			}
			a[p1] = a[p2] = 0;
		}
		printf("\n");
	}
	return 0;
}
