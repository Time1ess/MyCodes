// 斐波那契数列.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <iostream>
using namespace std;

//递归实现斐波那契数列
long long Fibonacci_Solution1(unsigned int n)
{
	if (n == 0)return 0;
	else if (n == 1)return 1;
	else return Fibonacci_Solution1(n - 1) + Fibonacci_Solution1(n - 2);
}

long long Fibonacci_Solution2(unsigned int n)
{
	if (n < 0)
		throw exception("Invalid Parameters.");
	int result[2] = { 0, 1 };
	if (n < 2)
		return result[n];
	long long fibNMinusTwo = 0, fibNMinusOne = 1;
	long long fibN = 0;
	for (int i = 2; i <= n; i++)
	{
		fibN = fibNMinusOne + fibNMinusTwo;
		fibNMinusTwo = fibNMinusOne;
		fibNMinusOne = fibN;
	}
	return fibN;
}
void Test(int n, int expected)
{
	if (Fibonacci_Solution1(n) == expected)
		printf("Test for %d in solution1 passed.\n", n);
	else
		printf("Test for %d in solution1 failed.\n", n);

	if (Fibonacci_Solution2(n) == expected)
		printf("Test for %d in solution2 passed.\n", n);
	else
		printf("Test for %d in solution2 failed.\n", n);
}

int _tmain(int argc, _TCHAR* argv[])
{
	Test(0, 0);
	Test(1, 1);
	Test(2, 1);
	Test(3, 2);
	Test(4, 3);
	Test(5, 5);
	Test(6, 8);
	Test(7, 13);
	Test(8, 21);
	Test(9, 34);
	Test(10, 55);
	Test(40, 102334155);
	cin.get();
	return 0;
}

