#include <stdio.h>
#include <string.h>
#pragma warning(disable:4996)
char s[20][70];
int Next[70];
char tmp[70];

void kmpGetNext(int m, char *tar)	//生成tar的NEXT数组
{
	char b[70];
	strcpy(b + 1, tar);
	int k = 0;
	Next[1] = 0;
	for (int i = 2; i < m; i++)
	{
		while (k>0 && b[i] != b[k + 1])
			k = Next[k];
		if (b[i] == b[k + 1])
			k++;
		Next[i] = k;
	}
}

bool kmpMatch(char *a1, char *b1, int n, int m)	//使用kmp进行字符串匹配尝试
{
	char a[70], b[70];
	strcpy(a + 1, a1); 
	strcpy(b + 1, b1);
	int i, j = 0, cnt = 0;
	for (i = 1; i <= n; i++)
	{
		while (j>0 && b[j + 1] != a[i])
			j = Next[j];
		if (b[j + 1] == a[i])
			j += 1;
		if (j == m)
			return true;
	}
	return false;
}

bool check(char *s1, int tot)
{
	int i, j;
	for (i = 2; i <= tot; i++)
	{
		int n = strlen(s[i] + 1), m = strlen(s1);
		if (!kmpMatch(s[i] + 1, s1, n, m))
			return false;
	}
	return true;
}

char ans[70];

int main()
{
	int t, n, i, j;
	scanf("%d", &t);
	while (t--)
	{
		scanf("%d", &n);
		for (i = 1; i <= n; i++)  
			scanf("%s", s[i] + 1);
		int len = strlen(s[1] + 1);
		int L = 0;
		for (i = 1; i <= len; i++)
		{
			for (j = 1; j <= len - i + 1; j++)
			{
				strncpy(tmp, s[1] + j, i);//生成子字符串
				memset(Next, 0, sizeof(Next));
				kmpGetNext(i, tmp);//对字符串完成KMP的NEXT数组建立
				if (check(tmp, n))	//在每行中查找tmp字符串
				{
					if (i >= L)
					{
						if (strcmp(tmp, ans)<0 && i == L)//如果当前子字符串的字典序更小而且长度与最近的结果一样长则替换
							strcpy(ans, tmp);
						if (i>L)  //如果当前结果更短，则替换
							strcpy(ans, tmp);
						L = strlen(ans);
					}
				}
				memset(tmp, 0, sizeof(tmp));
			}
		}
		if (L >= 3) 
			printf("%s\n", ans);
		else 
			printf("no significant commonalities\n");
	}
	return 0;
}