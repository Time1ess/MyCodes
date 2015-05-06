#include <cstdio>
#include <cstring>
#pragma warning(disable:4996)
using namespace std;
#define MAX 105
char tmp[MAX];
int ans[MAX] = { 0 };

int main()
{
//	freopen("D:\\MyCodes\\ACM-POJ\\Debug\\a.txt", "r", stdin);
//	freopen("D:\\MyCodes\\ACM-POJ\\Debug\\b.txt", "w", stdout);
	int len;
	while (scanf("%s",tmp) &&strcmp(tmp,"0"))
	{
		len = strlen(tmp);
		for (int i = 0; i < len; i++)
			ans[i] += tmp[len - i - 1] - '0';
	}
	for (int i = 0; i < MAX; i++)
	if (ans[i] >= 10)
	{
		ans[i + 1] += ans[i] / 10;
		ans[i] %= 10;
	}
	int k = MAX;
	while (ans[--k] == 0);
	while (k >= 0)
		printf("%d", ans[k--]);
	printf("\n");
	return 0;
}