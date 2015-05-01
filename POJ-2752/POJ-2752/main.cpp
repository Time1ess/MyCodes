#include <stdio.h>
#include <string.h>
#pragma warning(disable:4996)
#define MAXSIZE 400000

char s[MAXSIZE + 10];
int Next[MAXSIZE + 10];
int ans[MAXSIZE + 10];

void kmpGetNext()
{
	int len = strlen(s);
	if (len <= 0)return;
	int k = 0;
	memset(Next, -1, MAXSIZE + 10);
	Next[1] = 0;
	for (int i = 1; i < len; i++)
	{
		while (k>0 && s[i] != s[k])
			k = Next[k];
		if (s[k] == s[i])k++;
		Next[i + 1] = k;
	}
}

int main()
{
	while (scanf("%s",s)!=EOF)
	{
		kmpGetNext();
		int len = strlen(s);
		int total = 0;
		int tmp = Next[len];
		if (tmp != 0)ans[total++] = tmp;
		while (Next[tmp] > 0)
		{
			tmp = Next[tmp];
			ans[total++] = tmp;
		}
		for (int i = total - 1; i >= 0; i--)
			printf("%d ", ans[i]);
		printf("%d\n", len);
	}
	return 0;
}