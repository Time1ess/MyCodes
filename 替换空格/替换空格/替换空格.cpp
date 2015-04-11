// 替换空格.cpp : 定义控制台应用程序的入口点。
//
//请实现一个函数，把字符串中的每个空格替换成"%20"
//例如输入"We are happy.",则输出"We%20are%20happy."
#include "stdafx.h"
#include <iostream>
using namespace std;
#pragma warning(disable:4996)

//#define NEW_STR		//采用申请新字符串的方式完成替换
#define NO_NEW		//在原字符串的基础上进行替换
void replace(char *s, int capacity)
{
#ifdef NEW_STR
	int BlankCount = 0;
	if (s == nullptr || capacity <= 0)return;
	int i = 0;
	while (s[i] != '\0')
	if (s[i++] == ' ')BlankCount++;
	char *ns = new char[capacity + BlankCount * 2];
	int p1, p2;
	p1 = capacity;
	p2 = capacity + BlankCount * 2;
	while (p1 >= 0)
	{
		if (s[p1] != ' ')
		{
			ns[p2--] = s[p1--];
			continue;
		}
		else
		{
			ns[p2--] = '0';
			ns[p2--] = '2';
			ns[p2--] = '%';
			p1--;
			continue;
		}
	}
	strcpy(s, ns);
#endif
#ifdef NO_NEW
	if (s == nullptr || capacity <= 0)
		return;
	int length = 0;
	int numberOfBlank = 0;
	int i = 0;
	while (s[i] != '\0')
	{
		length++;
		if (s[i] == ' ')
			numberOfBlank++;
		i++;
	}
	int newLength = length + numberOfBlank * 2;
	if (newLength > capacity)
		return;
	int indexOfOriginal = length;
	int indexOfNew = newLength;
	while (indexOfOriginal >= 0 && indexOfNew > indexOfOriginal)
	{
		if (s[indexOfOriginal] == ' ')
		{
			s[indexOfNew--] = '0';
			s[indexOfNew--] = '2';
			s[indexOfNew--] = '%';
		}
		else
		{
			s[indexOfNew--] = s[indexOfOriginal];
		}
		--indexOfOriginal;
	}
#endif
}

void Test(char* testName, char string[], int length, char expected[])
{
	if (testName != NULL)
		printf("%s begins: ", testName);

	replace(string, length);

	if (expected == NULL && string == NULL)
		printf("passed.\n");
	else if (expected == NULL && string != NULL)
		printf("failed.\n");
	else if (strcmp(string, expected) == 0)
		printf("passed.\n");
	else
		printf("failed.\n");
}

// 空格在句子中间
void Test1()
{
	const int length = 100;

	char string[length] = "hello world";
	Test("Test1", string, length, "hello%20world");
}

// 空格在句子开头
void Test2()
{
	const int length = 100;

	char string[length] = " helloworld";
	Test("Test2", string, length, "%20helloworld");
}

// 空格在句子末尾
void Test3()
{
	const int length = 100;

	char string[length] = "helloworld ";
	Test("Test3", string, length, "helloworld%20");
}

// 连续有两个空格
void Test4()
{
	const int length = 100;

	char string[length] = "hello  world";
	Test("Test4", string, length, "hello%20%20world");
}

// 传入NULL
void Test5()
{
	Test("Test5", NULL, 0, NULL);
}

// 传入内容为空的字符串
void Test6()
{
	const int length = 100;

	char string[length] = "";
	Test("Test6", string, length, "");
}

//传入内容为一个空格的字符串
void Test7()
{
	const int length = 100;

	char string[length] = " ";
	Test("Test7", string, length, "%20");
}

// 传入的字符串没有空格
void Test8()
{
	const int length = 100;

	char string[length] = "helloworld";
	Test("Test8", string, length, "helloworld");
}

// 传入的字符串全是空格
void Test9()
{
	const int length = 100;

	char string[length] = "   ";
	Test("Test9", string, length, "%20%20%20");
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
	Test9();
	cin.get();
	return 0;
}

