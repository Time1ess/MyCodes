#include <cstdio>
#pragma warning(disable:4996)
using namespace std;

bool isPrime(unsigned long n)
{
	if (n <= 3)
	{
		return n > 1;
	}
	else if (n % 2 == 0 || n % 3 == 0)
	{
		return false;
	}
	else
	{
		for (unsigned short i = 5; i * i <= n; i += 6)
		{
			if (n % i == 0 || n % (i + 2) == 0)
			{
				return false;
			}
		}
		return true;
	}
}

int main()
{
	int a, d, n;
	while (scanf("%d %d %d", &a, &d, &n) && !(a == 0 && d == 0 && n == 0))
	{
		int index = 0;
		int num = 0;
		while (index < n)
		{
			if (isPrime(a + num*d))
				index++;
			num++;
		}
		printf("%d\n", a + (num-1)*d);
	}
	return 0;
}