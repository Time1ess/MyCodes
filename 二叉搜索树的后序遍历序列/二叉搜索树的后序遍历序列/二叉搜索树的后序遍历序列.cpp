// 二叉搜索树的后序遍历序列.cpp : 定义控制台应用程序的入口点。
//
//题目:输入一个整数数组，判断该数组是不是某二叉搜索树的后序遍历序列
//如果是则返回true，否则返回false。假设输入的数组的任意两个数字都互不相同
#include "stdafx.h"
#include <iostream>
using namespace std;

bool VerifySquenceOfBST(int sequence[], int length)
{
	if (sequence == NULL || length <= 0)
		return false;
	int root = sequence[length - 1];

	int i = 0;
	for (; i < length-1; i++)
	{
		if (sequence[i]>root)
			break;
	}
	int j = i;
	for (; j < length-1; j++)
	{
		if (sequence[j] < root)
			return false;
	}

	bool left = true;
	if (i>0)
		left = VerifySquenceOfBST(sequence, i);
	bool right = true;
	if (j < length-1)
		right = VerifySquenceOfBST(sequence + j, length - i - 1);

	return (left&&right);
}

// ====================测试代码====================
void Test(char* testName, int sequence[], int length, bool expected)
{
	if (testName != NULL)
		printf("%s begins: ", testName);
	for (int i = 0; i < length; i++)
		cout << sequence[i] << " ";
	cout << endl;
	if (VerifySquenceOfBST(sequence, length) == expected)
		printf("passed.\n");
	else
		printf("failed.\n");
}

//            10
//         /      \
//        6        14
//       /\        /\
//      4  8     12  16
void Test1()
{
	int data[] = { 4, 8, 6, 12, 16, 14, 10 };
	Test("Test1", data, sizeof(data) / sizeof(int), true);
}

//           5
//          / \
//         4   7
//            /
//           6
void Test2()
{
	int data[] = { 4, 6, 7, 5 };
	Test("Test2", data, sizeof(data) / sizeof(int), true);
}

//               5
//              /
//             4
//            /
//           3
//          /
//         2
//        /
//       1
void Test3()
{
	int data[] = { 1, 2, 3, 4, 5 };
	Test("Test3", data, sizeof(data) / sizeof(int), true);
}

// 1
//  \
//   2
//    \
//     3
//      \
//       4
//        \
//         5
void Test4()
{
	int data[] = { 5, 4, 3, 2, 1 };
	Test("Test4", data, sizeof(data) / sizeof(int), true);
}

// 树中只有1个结点
void Test5()
{
	int data[] = { 5 };
	Test("Test5", data, sizeof(data) / sizeof(int), true);
}

void Test6()
{
	int data[] = { 7, 4, 6, 5 };
	Test("Test6", data, sizeof(data) / sizeof(int), false);
}

void Test7()
{
	int data[] = { 4, 6, 12, 8, 16, 14, 10 };
	Test("Test7", data, sizeof(data) / sizeof(int), false);
}

void Test8()
{
	Test("Test8", NULL, 0, false);
}

int _tmain(int argc, _TCHAR* argv[])
{
	Test1();
	Test2();
	Test3();
	Test4();
	Test5();
	Test6();
	Test7();
	Test8();
	cin.get();
	return 0;
}

