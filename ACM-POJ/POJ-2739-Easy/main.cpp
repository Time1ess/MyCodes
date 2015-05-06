#include <iostream>
#include <cstdio>
#pragma warning(disable:4996)
using namespace std;

int primes[1229];
int cnt = 0;
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

void findans(int index, int target)
{
	if (target < 2)
		return;
	if (primes[index] == target)
		cnt++;
	else if (primes[index] < target)
	{
		findans(index + 1, target - primes[index]);
	}
	else
		return;
}



int main()
{
//	freopen("D:\\MyCodes\\ACM-POJ\\Debug\\a.txt", "r", stdin);
//	freopen("D:\\MyCodes\\ACM-POJ\\Debug\\b.txt", "w", stdout);
	for (int i = 2; i <= 10000; i++)
	{
		if (isPrime(i))
		{
			primes[cnt] = i;
			cnt++;
		}
	}

	int tar;
	while (scanf("%d", &tar)&&tar!=0)
	{
		cnt = 0;
		for (int i = 0; primes[i] <= tar; i++)
			findans(i, tar);
		printf("%d\n", cnt);
	}
	return 0;
}