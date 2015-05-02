#include<iostream>
#include<cstring>
#pragma warning(disable:4996)
using namespace std;

char s[4010][210];
char tmp[210];
int n, ma, length[4010], tmpLen;
int Next[210];

void get_next()
{
	int k = 0;
	Next[1] = 0;
	for (int i = 2; i <= tmpLen; i++)
	{
		while (k > 0 && tmp[i] != tmp[k + 1])
			k = Next[k];
		if (tmp[i] == tmp[k + 1])
			k++;
		Next[i] = k;
	}
}

bool kmpMatch(char *source,char *target,int n,int m)//要求传入的字符串第一个字符为'\0',长度n,m为有效字符串长度
{
	int k = 0;
	for (int i = 1; i <= n; i++)
	{
		while (k > 0 && source[i] != target[k + 1])
			k = Next[k];
		if (source[i] == target[k+1])
			k++;
		if (k == m)
			return true;
	}
	return false;
}

bool check(char *tmp)//待比较的字符串tmp
{
	for (int i = 1; i <= n; i++)	
	{
		int length = strlen(tmp + 1);
		int slength = strlen(s[i] + 1);
		if (!kmpMatch(s[i], tmp, slength, length))
			return false;
	}
	return true;
}

int main(){
	int i;

	freopen("D:\\MyCodes\\ACM-POJ\\Debug\\a.txt", "r", stdin);
	freopen("D:\\MyCodes\\ACM-POJ\\Debug\\b.txt", "w", stdout);
	while (scanf("%d", &n) && n)
	{
		char result[210] = { 0 };
		int resultLen=0;
		for (i = 1; i <= n; i++)
		{
			scanf("%s", s[i]+1);
			length[i] = strlen(s[i]+1);
		}

		for (i = 1; i <= length[1]; i++)
		{
			for (int len = 1; len + i - 1 < length[1]; len++)
			{
				//strcpy(tmp + 1, s[1] + i);
				memset(tmp, 0, sizeof(tmp));
				strncpy(tmp + 1, s[1] + i, len);
				if (check(tmp))
				{
					if (len == resultLen)
					{
						if (strcmp(result, tmp + 1) > 0)
							strcpy(result, tmp + 1);
					}
					else if (len > resultLen)
					{
						strcpy(result, tmp + 1);
						resultLen = len;
					}

				}
			}
		}
		if (result[0]=='\0') printf("IDENTITY LOST\n");
		else printf("%s\n", result);
	}
	return 0;
}