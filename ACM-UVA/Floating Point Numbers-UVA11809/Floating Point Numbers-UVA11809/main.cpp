#include <math.h>
#include <stdio.h>
#include <string.h>
#pragma warning(disable:4996)

double C[10][31];

void init()
{
	int i, j, v;
	double f[10] = { 0.5 }, g[31], t;

	for (i = 1, t = 0.5; i < 10; i++)
	{
		f[i] = f[i - 1] + t / 2;
		t /= 2;
	}
	for (i = 0; i < 10; i++) f[i] = log10(f[i]);
	for (i = 1, v = 2; i <= 30; i++)
	{
		g[i] = (v - 1.0)*log10(2.0);
		v <<= 1;
	}
	for (i = 0; i < 10; i++) for (j = 1; j <= 30; j++)
		C[i][j] = f[i] + g[j];
}

int main()
{
	freopen("data.txt", "r", stdin);
	freopen("out.txt", "w", stdout);
	int i, j;
	char s[100], *p;
	double A, B;

	init();

	while (scanf("%s", s), strcmp(s, "0e0"))
	{
		p = strchr(s, 'e');
		*p = 0;                 
		sscanf(s, "%lf", &A);
		sscanf(p + 1, "%lf", &B);

		int pi = 0, pj = 1;
		B = A = log10(A) + B;   
		for (i = 0; i < 10; i++)
			for (j = 1; j <= 30; j++)
				if (fabs(A - C[i][j]) < B) pi = i, pj = j, B = fabs(A - C[i][j]);
		printf("%d %d\n", pi, pj);
	}
	return 0;
}