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
	int n;
	while (scanf("%d", &n) && n != 0)
	{
		for (int i = 3; i <= n/2; i += 2)	//注意6 = 3 + 3的情况，判定应该为i<=n/2
		{
			if (isPrime(i) && isPrime(n - i))
			{
				printf("%d = %d + %d\n", n, i, n - i);
				break;
			}
		}
	}
	return 0;
}