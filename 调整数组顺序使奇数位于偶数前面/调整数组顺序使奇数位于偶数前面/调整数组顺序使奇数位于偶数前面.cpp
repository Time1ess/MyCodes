// 调整数组顺序使奇数位于偶数前面.cpp : 定义控制台应用程序的入口点。
//
//题目:输入一个整数数组，实现一个函数来调整该数组中数字的顺序
//使得所有奇数位于数组的前半部分，所有偶数位于数组的后半部分
#include "stdafx.h"
#include <iostream>
using namespace std;

//仅仅能满足题意的算法，没有良好的可扩展性
void ReorderOddEven(int *numbers, unsigned int length)
{
	if (numbers == NULL || length == 0)
		return;
	int oddIndex=0, evenIndex=length-1;
	while (oddIndex < evenIndex)
	{
		while ((oddIndex<evenIndex)&&((numbers[oddIndex] & 1) == 1))oddIndex++;
		while ((oddIndex<evenIndex) && ((numbers[evenIndex] & 1) == 0))evenIndex--;
		if (oddIndex <= evenIndex)
		{
			int tmp = numbers[oddIndex];
			numbers[oddIndex] = numbers[evenIndex];
			numbers[evenIndex] = tmp;
		}
	}
}

//具有良好扩展性的算法,较高的重用性
void Reorder(int *numbers, unsigned int length, bool(*func)(int))
{
	if (numbers == NULL || length == 0)
		return;
	int *start = numbers, *end = numbers + length - 1;

	while (start < end)
	{
		while (start < end&&!func(*start))
			start++;
		while (start < end&&func(*end))
			end--;

		if (start < end)
		{
			int tmp = *start;
			*start = *end;
			*end = tmp;
		}
	}
}

bool isEven(int n)
{
	return (n & 1) == 0;
}

void Test(int *original, int *expected, unsigned int length)
{
	cout << "Test For:"<<endl;
	if (original!=NULL)
	for (int i = 0; i < length; i++)
	{
		cout << original[i] << " ";
	}
	cout << endl;
	if (expected!=NULL)
	for (int i = 0; i < length; i++)
	{
		cout << expected[i] << " ";
	}
	cout << endl;
//	ReorderOddEven(original, length);
	Reorder(original, length, isEven);
	cout << "now:" << endl;
	if (original != NULL)
	for (int i = 0; i < length; i++)
	{
		cout << original[i] << " ";
	}
	cout << endl;
	if ((original == NULL&&expected == NULL)|| memcmp(original, expected, sizeof(int)*length) == 0)
		cout << "Test Passed." << endl;
	else
		cout << "Test Failed." << endl;
}

void Test1()
{
	int original[] = { 3, 2, 1, 5, 4 };
	int expected[] = { 3, 5, 1, 2, 4 };
	Test(original, expected, 5);
}

void Test2()
{
	int original[] = { 1, 2, 3, 4, 5 };
	int expected[] = { 1, 5, 3, 4, 2 };
	Test(original, expected, 5);
}

void Test3()
{
	int original[] = { 2, 2, 2, 2, 4 };
	int expected[] = { 2, 2, 2, 2, 4 };
	Test(original, expected, 5);
}

void Test4()
{
	int original[] = { 1, 1, 1, 3, 1 };
	int expected[] = { 1, 1, 1, 3, 1 };
	Test(original, expected, 5);
}

void Test5()
{
	Test(NULL, NULL, 4);
}



int _tmain(int argc, _TCHAR* argv[])
{
	Test1();
	Test2();
	Test3();
	Test4();
	Test5();
	cin.get();
	return 0;
}

