// POJ-2406.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <stdio.h>
#include <string.h>
#pragma warning(disable:4996)
#define MAXSIZE 1000000
char s[MAXSIZE+10];
int Next[MAXSIZE + 10];

bool kmpGetNext()
{
	int len = strlen(s);
	if (len <= 0)return false;
	int k = 0;
	memset(Next, -1, MAXSIZE + 1);
	Next[1] = 0;
	for (int i = 1; i < len; i++)
	{
		while (k>0 && s[i] != s[k])k = Next[k];
		if (s[i] == s[k])k++;
		Next[i+1] = k;
	}
	return true;
}


int main()
{
	while (scanf("%s", s) != EOF)
	{
		if (s[0] == '.')break;
		kmpGetNext();
		int len = strlen(s);
		if (len % (len - Next[len]) == 0)
			printf("%d\n", len / (len - Next[len]));
		else
			printf("1\n");
	}
	return 0;
}
