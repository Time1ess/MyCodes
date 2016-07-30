// 二进制中1的个数.cpp : 定义控制台应用程序的入口点。
//
//题目:请实现一个函数，输入一个整数，输出该数二进制表示中
//1的个数，例如把9表示成二进制是1001，有2位是1。因此，如
//果输入9，该函数输出2

#include "stdafx.h"
#include <iostream>
using namespace std;
#define NS  //常规解法
#define SS	//令人惊喜的解法

#ifdef NS
int NumberOf1_Solution1(int n)
{
	int count = 0;

	unsigned int flag = 1;
	while (flag)
	{
		if (n&flag)
			count++;
		flag = flag << 1;
	}
	return count;
}
#endif

#ifdef SS
int NumberOf1_Solution2(int n)
{
	int count=0;
	while (n)
	{
		++count;
		n = (n - 1)&n;	
		//把一个整数减去1，再和原整数做与运算，会把该整数最右边一个1变成0。那么一个
		//整数的二进制表示中有多少个1，就可以进行多少次这样的操作。
	}
	return count;
}
#endif

void Test(int number, unsigned int expected)
{
	int actual = NumberOf1_Solution1(number);
	if (actual == expected)
		printf("Solution1: Test for %p passed.\n", number);
	else
		printf("Solution1: Test for %p failed.\n", number);

	actual = NumberOf1_Solution2(number);
	if (actual == expected)
		printf("Solution2: Test for %p passed.\n", number);
	else
		printf("Solution2: Test for %p failed.\n", number);

	printf("\n");
}

int _tmain(int argc, _TCHAR* argv[])
{    // 输入0，期待的输出是0
	Test(0, 0);

	// 输入1，期待的输出是1
	Test(1, 1);

	// 输入10，期待的输出是2
	Test(10, 2);

	// 输入0x7FFFFFFF，期待的输出是31
	Test(0x7FFFFFFF, 31);

	// 输入0xFFFFFFFF（负数），期待的输出是32
	Test(0xFFFFFFFF, 32);

	// 输入0x80000000（负数），期待的输出是1
	Test(0x80000000, 1);
	cin.get();
	return 0;
}

