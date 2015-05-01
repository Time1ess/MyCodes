#include <string.h>
#include <stdio.h>
#pragma warning(disable:4996)

#define MAXSIZE 1000000
#define MAXSIZE2 10000
int s_len;
int t_len;
char t[MAXSIZE + 100];
char s[MAXSIZE2 + 100];
int Next[MAXSIZE2 + 100];


void kmpGetNext()
{
	int k = 0;
	int i = 1;
	Next[1] = 0;
	for (i = 2; i<=s_len;i++)
	{
		while (k>0 && s[i] != s[k+1])
			k = Next[k];
		if (s[k+1] == s[i])
			k++;
		Next[i] = k;
	}
}

int kmpMatch()
{
	int i=1, k=0;
	int count = 0;
	for (i = 1; i<=t_len;i++)
	{
		while (k>0 && t[i] != s[k+1])
			k = Next[k];
		if (s[k+1] == t[i])
			k++;
		if (k == s_len)
		{
			count++;
			k = Next[k];
		}
	}
	return count;
}

int main()
{
	int n;
	scanf("%d", &n);
	while (n--)
	{
		scanf("%s%s", s + 1, t + 1);
		s_len = strlen(s+1);
		t_len = strlen(t+1);
		kmpGetNext();
		//for (int i = 0; i < strlen(s)+2; i++)
		//	printf("[%d]:%d  ", i,Next[i]);
		//printf("\n");
		printf("%d\n", kmpMatch());
	}
	return 0;
}

//#include<cstdio>
//#include<cstring>
//#pragma warning(disable:4996)
//int n, m;
//char a[1000010], b[10010];
//int p[11111];
//void getp(){
//	memset(p, -1, 11111);
//	p[1] = 0;
//	int i, j = 0;
//	for (i = 2; i <= m; i++){
//		while (j>0 && b[j + 1] != b[i]) j = p[j];
//		if (b[j + 1] == b[i]) j += 1;
//		p[i] = j;
//	}
//}
//int kmp()
//{
//	int i, j = 0, cnt = 0;
//	for (i = 1; i <= n; i++){
//		while (j>0 && b[j + 1] != a[i]) j = p[j];
//		if (b[j + 1] == a[i]) j += 1;
//		if (j == m){
//			cnt++;
//			j = p[j];
//
//		}
//	}
//	return cnt;
//}
//int main()
//{
//	int t;
//	scanf("%d", &t);
//	while (t--)
//	{
//		scanf("%s%s", b + 1, a + 1);
//		m = strlen(b + 1);
//		n = strlen(a + 1);
//		getp();
//		for (int i = 0; i < m+4; i++)
//			printf("%d ", p[i]);
//		printf("\n");
//		printf("%d\n", kmp());
//	}
//}