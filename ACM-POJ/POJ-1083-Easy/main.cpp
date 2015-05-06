#include <cstdio>
#include <cstring>
#pragma warning(disable:4996)
using namespace std;

int room[410];

int main()
{
	int n, t;
	scanf("%d", &n);
	while (n--)
	{
		scanf("%d", &t);
		int low, high;
		memset(room, 0, sizeof(room));
		int total = 0;
		int tmp;
		while (t--)
		{
			scanf("%d %d", &low, &high);
			if (low > high)
			{
				tmp = high;
				high = low;
				low = tmp;
			}
			if (low % 2 == 0)low--;
			if (high % 2 == 1)high++;
			for (int i = low; i <= high; i++)
				room[i]++;
		}
		for (int i = 1; i <= 400;i++)
		if (room[i] > total)
			total = room[i];
		printf("%d\n", total * 10);
	}
	return 0;
}