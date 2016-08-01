#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
#pragma warning(disable:4996)
using namespace std;

#define MAX 110
char tmp[MAX],ans[MAX];
bool FIND = false;
int tc[26], ac[26];

int main()
{
//	freopen("D:\\MyCodes\\ACM-POJ\\Debug\\a.txt", "r", stdin);
//	freopen("D:\\MyCodes\\ACM-POJ\\Debug\\b.txt", "w", stdout);
	while (scanf("%s", tmp) != EOF)
	{
		scanf("%s", ans);
		if (strlen(tmp) == strlen(ans))
		{
			memset(tc, 0, sizeof(tc));
			memset(ac, 0, sizeof(ac));
			for (int i = 0; i < strlen(tmp); i++)
			{
				tc[tmp[i] - 'A']++;
				ac[ans[i] - 'A']++;
			}
			sort(tc, tc + 26);
			sort(ac, ac + 26);
			int i = 0;
			for (i = 0; i < 26; i++)
			{
				if (tc[i] != ac[i])
					break;
			}
			if (i == 26)
				FIND = true;
		}
		if (FIND)
			printf("YES\n");
		else
			printf("NO\n");
	}
	return 0;
}
