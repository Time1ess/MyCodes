// EXCEL中列的进制转换.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <iostream>
using namespace std;
int AbcToDec(char *s, int size)
{
	if (s == NULL || size <= 0)
		throw exception("Invalid Parameters.");

	int result = 0;
	for (int i = 0; i < size; i++)
	{
		if ( s[i]>'Z' || s[i] < 'A')
			throw exception("Invalid Parameters.");
			result = result * 26 + s[i] - 'A' + 1;
	}
	return result;
}

void Test(int testnum,char *original, int size, int expect)
{
	try
	{
		int fact = AbcToDec(original, size);
		if (expect == fact)
			cout << "Test " << testnum << " :Passed." << endl;
		else
			cout << "Test " << testnum << " :Failed." << endl;
	}
	catch (exception e)
	{
		cout << "Test " << testnum << " :Passed.(Catch Exception.)" << endl;
	}
}

int _tmain(int argc, _TCHAR* argv[])
{
	Test(1, NULL, 0, 0);
	Test(2, "B", 1, 2);
	Test(3, "A", 1, 1);
	Test(4, "AB", 2, 28);
	Test(5, "AA", 2, 27);
	Test(6, "Z", 2, 27);
	cin.get();
	return 0;
}

