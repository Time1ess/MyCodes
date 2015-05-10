#include <cstdio>
#include <cstring>
#include <cstdlib>
#pragma warning(disable:4996)
using namespace std;

char s[4010][210];
int slen[4010];
char tmp[210];
char ans[210];
int Next[210];
int anslen;

void kmpGetNext(char *s1, int len)
{
	int k = -1, i = 0;
	Next[0] = -1;
	while (i < len)
	{
		if (k == -1 || s1[k] == s1[i])
		{
			i++;
			k++;
			Next[i] = k;
		}
		else
			k = Next[k];
	}
}

bool KMP(char *s1,char *t1, int s1len,int t1len)
{
	int i = 0, j = 0;
	while (i<s1len)
	{
		if (j==-1||s1[i] == t1[j])
		{
			i++;
			j++;
		}
		else
			j = Next[j];
		if (j == t1len)
			return true;
	}
	return false;
}

bool check(char *t1,int t1len,int n)
{
	for (int i = 1; i < n; i++)
	{
		if (!KMP(s[i], t1, slen[i], t1len))
			return false;
	}
	return true;
}

bool smaller(char *t1, char *ans1,int len)//
{
	for (int i = 0; i < len; i++)
	{
		if (ans1[i]>t1[i])
			return true;
		else if (ans1[i] < t1[i])
			return false;
	}
	return false;
}

int main()
{
	int n;
//	freopen("D:\\MyCodes\\ACM-POJ\\Debug\\a.txt", "r", stdin);
//	freopen("D:\\MyCodes\\ACM-POJ\\Debug\\b.txt", "w", stdout);
	while (scanf("%d", &n) && n)
	{
		memset(ans, 0, sizeof(ans));
		anslen = 0;
		for (int i = 0; i < n; i++)
		{
			scanf("%s", s[i]);
			slen[i] = strlen(s[i]);
		}

		for (int j = 1; j <= slen[0] - 1; j++)	//take j chars to make a substring
		{
			for (int i = 0; i <= slen[0] - j; i++)	//from the i-th char
			{
				memset(tmp, 0, sizeof(tmp));
				strncpy(tmp, s[0] + i, j);
				kmpGetNext(tmp, j);
				if (check(tmp, j, n))
				{
					if (j > anslen)
					{
						strcpy(ans, tmp);
						anslen = j;
					}
					else if (j == anslen)
					{
						if (smaller(tmp, ans, j))
						{
							strcpy(ans, tmp);
						}
					}
				}

			}
		}
		if (anslen == 0)
			printf("IDENTITY LOST\n");
		else
			printf("%s\n", ans);
	}
	return 0;
}