// 两个排序数组的合并.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <iostream>
using namespace std;

void merge(int a[], int n, int b[], int m)
{
	int indexOfa = n-1, indexOfb = m-1;
	int indexOfnew = m + n-1;
	if (a == nullptr || b == nullptr || n <= 0 || m < 0)return;
	while (indexOfa >= 0 && indexOfb >= 0)
	{
		if (a[indexOfa]>b[indexOfb])
		{
			a[indexOfnew--] = a[indexOfa--];
		}
		else
		{
			a[indexOfnew--] = b[indexOfb--];
		}
	}
	while (indexOfa>=0)
		a[indexOfnew--] = a[indexOfa--];
	while (indexOfb>=0)
		a[indexOfnew--] = b[indexOfb--];
}
//正常的合并
void test()
{
	int a[30] = { 1, 3, 6, 8, 11, 15, 16 };
	int b[9] = { 2, 3, 6, 7, 8, 9, 10, 14, 15 };
	merge(a, 7, b, 9);
	for (int i = 0; i < 7 + 9; i++)
		cout << a[i] << " ";
}
//所有数相同
void test1()
{
	int a[30] = { 2,2,2,2,2 };
	int b[9] = { 2,2,2,2 };
	merge(a, 5, b, 4);
	for (int i = 0; i < 5 + 4; i++)
		cout << a[i] << " ";
}
//一个为空指针
void test2()
{
	int a[30] = { 1, 3, 6, 8, 11, 15, 16 };
	merge(a, 7, nullptr, 4);
	for (int i = 0; i < 7; i++)
		cout << a[i] << " ";
}

int _tmain(int argc, _TCHAR* argv[])
{
	test();
	cout << endl;
	test1();
	cout << endl;
	test2();
	cin.get();
	return 0;
}

