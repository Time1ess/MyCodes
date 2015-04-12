// 旋转数组的最小数字.cpp : 定义控制台应用程序的入口点。
//
//题目:把一个数组最开始的若干个元素搬到数组的末尾，我们
//称之为数组的旋转。输入一个递增排序的数组的一个旋转，
//输出旋转数组的最小元素。
//例如数组{3，4，5，1，2}为{1，2，3，4，5}的一个旋转，
//该数组的最小值为1

#include "stdafx.h"
#include <iostream>
using namespace std;


//顺序查找最小的元素
int MinInOrder(int numbers[], int index1, int index2)
{
	int result = numbers[index1];
	for (int i = index1 + 1; i <= index2; i++)
	{
		if (result > numbers[i])
			result = numbers[i];
	}
	return result;
}


//递归解法
int Min(int numbers[], int start, int end)
{
	if (numbers == NULL || start < 0 || end < start)
		throw exception("Wrong Array!");

	if (numbers[start] < numbers[end])return numbers[start];

	if (start == end - 1)return numbers[end];

	int mid = (start + end) / 2;

	if (numbers[start] == numbers[end] &&
		numbers[start] == numbers[mid])
		return MinInOrder(numbers, start, end);

	if (numbers[mid] >= numbers[start])
		return Min(numbers, mid, end);
	else if (numbers[mid] <= numbers[end])
		return Min(numbers, start, mid);
}

//循环解法
int Min(int numbers[], int length)
{
	if (numbers == NULL || length <= 0)
		throw exception("Wrong Array!");

	int index1 = 0;
	int index2 = length - 1;
	int indexMid = index1;

	while (numbers[index1] >= numbers[index2])
	{
		if (index2 - index1 == 1)
		{
			indexMid = index2;
			break;
		}

		indexMid = (index1 + index2) / 2;

		if (numbers[index1] == numbers[index2] &&
			numbers[indexMid] == numbers[index1])
			return MinInOrder(numbers, index1, index2);

		if (numbers[indexMid] >= numbers[index1])
			index1 = indexMid;
		else if (numbers[indexMid] <= numbers[index2])
			index2 = indexMid;
	}
	return numbers[indexMid];
}

//典型输入，单调升序的数组的一个旋转
void Test1()
{
	int a[] = { 3, 4, 5, 1, 2 };
	int fact = Min(a, 0, 4);
	int fact1 = Min(a, 5);
	if (fact == 1&&fact1==1)
		cout << "Test 1 Passed!";
	else
		cout << "Test 1 Failed!";
	cout << endl;
}

//全部为重复数字
void Test2()
{
	int a[] = { 3,3,3,3,3};
	int fact = Min(a, 0, 4);
	int fact1 = Min(a, 5);
	if (fact == 3&&fact1==3)
		cout << "Test 2 Passed!";
	else
		cout << "Test 2 Failed!";
	cout << endl;
}
//输入NULL
void Test3()
{
	int *a = NULL;
	try
	{
		int fact = Min(a, 0, 4);
		int fact1 = Min(a, 5);
	}
	catch (exception e)
	{
		if (!strcmp(e.what(),"Wrong Array!"))
			cout << "Test 3 Passed!";
		else
			cout << "Test 3 Failed!";
	}
	cout << endl;
}
//有重复的数字，并且重复的数字刚好是第一个数字和最后一个数字
void Test4()
{
	int a[] = { 1, 0, 1, 1, 1 };
	int fact = Min(a, 0, 4);
	int fact1 = Min(a, 5);
	if (fact == 0&&fact1==0)
		cout << "Test 4 Passed!";
	else
		cout << "Test 4 Failed!";
	cout << endl;
}
//有重复数字，并且重复的数字刚好的最小的数字
void Test5()
{
	int a[] = { 3, 4, 5, 1, 1, 2 };
	int fact = Min(a, 0, 5);
	int fact1 = Min(a, 6);
	if (fact == 1&&fact1==1)
		cout << "Test 5 Passed!";
	else
		cout << "Test 5 Failed!";
	cout << endl;
}
//有重复数字，但重复的数字不是第一个数字和最后一个数字
void Test6()
{
	int a[] = { 3, 4, 5, 1, 2, 2 };
	int fact = Min(a, 0, 5);
	int fact1 = Min(a, 6);
	if (fact == 1&&fact1==1)
		cout << "Test 6 Passed!";
	else
		cout << "Test 6 Failed!";
	cout << endl;
}
//单调升序数组，旋转0个元素，也就是单调升序数组本身
void Test7()
{
	int a[] = { 1, 2, 3, 4, 5 };
	int fact = Min(a, 0, 4);
	int fact1 = Min(a, 5);
	if (fact == 1&&fact1==1)
		cout << "Test 7 Passed!";
	else
		cout << "Test 7 Failed!";
	cout << endl;
}
//数组中只有一个数字
void Test8()
{
	int a[] = { 2 };
	int fact = Min(a, 0, 0);
	int fact1 = Min(a, 1);
	if (fact == 2&&fact1==2)
		cout << "Test 8 Passed!";
	else
		cout << "Test 8 Failed!";
	cout << endl;
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

