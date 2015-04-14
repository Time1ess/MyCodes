// 包含min函数的栈.cpp : 定义控制台应用程序的入口点。
//
//题目:定义栈的数据结构，请在该类型中视线一个能够得到栈的最小元素的min函数
#include "stdafx.h"
#include <iostream>
#include <stack>
#include <cassert>
using namespace std;

template <typename T>class StackWithMin
{
public:
	void push(const T &);
	void pop();
	const T & min()const;
private:
	stack<T> m_data;
	stack<T> m_min;
};
template <typename T>
void StackWithMin<T>::push(const T &elem)
{
	if (m_min.size() == 0 || elem < m_min.top())
		m_min.push(elem);
	else
		m_min.push(m_min.top());
	m_data.push(elem);
}

template <typename T>
void StackWithMin<T>::pop()
{
	assert(m_data.size() > 0 && m_min.size() > 0);

	m_data.pop();
	m_min.pop();
}

template <typename T>
const T & StackWithMin<T>::min()const
{
	assert(m_data.size() >= 0 && m_min.size() >= 0);
	return m_min.top();
}

void Test(char* testName, const StackWithMin<int>& stack, int expected)
{
	if (testName != NULL)
		printf("%s begins: ", testName);

	if (stack.min() == expected)
		printf("Passed.\n");
	else
		printf("Failed.\n");
}

int _tmain(int argc, _TCHAR* argv[])
{
	StackWithMin<int> stack;

	stack.push(3);
	Test("Test1", stack, 3);

	stack.push(4);
	Test("Test2", stack, 3);

	stack.push(2);
	Test("Test3", stack, 2);

	stack.push(3);
	Test("Test4", stack, 2);

	stack.pop();
	Test("Test5", stack, 2);

	stack.pop();
	Test("Test6", stack, 3);

	stack.pop();
	Test("Test7", stack, 3);

	stack.push(0);
	Test("Test8", stack, 0);

	cin.get();
	return 0;
}

