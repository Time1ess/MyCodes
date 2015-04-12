// 计算m和n的二进制表示相差位数.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <iostream>
using namespace std;

int CountDifferentBit(int m, int n)
{
	int c = m^n;
	int count = 0;
	while (c)
	{
		++count;
		c = (c - 1)&c;
	}
	return count;
}

void Test(int m, int n, int expected)
{
	int fact = CountDifferentBit(m, n);
	if (fact == expected)
		cout << "Test for " << m << " and " << n << " Passed."<<endl;
	else
		cout << "Test for " << m << " and " << n << " Failed."<<endl;
}

int _tmain(int argc, _TCHAR* argv[])
{
	Test(10, 13, 3);
	Test(15, 0, 4);
	Test(1, 8, 2);
	cout << sizeof(int) << endl;
	cout << sizeof(long) << endl;
	cout << sizeof(long long) << endl;

	cout << INT_MAX << endl;
	cout << LONG_MAX << endl;
	cout << LLONG_MAX << endl;
	cout << ULLONG_MAX << endl;
	cin.get();
	return 0;
}

