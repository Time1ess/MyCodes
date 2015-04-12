// 用两个栈实现队列.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <iostream>
#include <stack>
using namespace std;

template <typename T>class CQueue
{
public:
	CQueue(void);
	~CQueue(void);

	void appendTail(const T& node);
	T deleteHead();
private:
	stack<T> stack1;
	stack<T> stack2;
};

template <typename T> CQueue<T>::CQueue(void)
{
}

template <typename T> CQueue<T>::~CQueue(void)
{
}

template <typename T> 
void CQueue<T>::appendTail(const T& node)
{
	stack1.push(node);
}

template <typename T>
T CQueue<T>::deleteHead()
{
	if (!stack2.empty())
	{
		T& tmp = stack2.top();
		stack2.pop();
		return tmp;
	}
	else
	{
		while (!stack1.empty())
		{
			T& tmp = stack1.top();
			stack2.push(tmp);
			stack1.pop();
		}
		if (!stack2.empty())
		{
			T& tmp = stack2.top();
			stack2.pop();
			return tmp;
		}
	}
	throw exception("Queue is empty");
}

void Test(char actual, char expected)
{
	if (actual == expected)
		printf("Test passed.\n");
	else
		printf("Test failed.\n");
}


int _tmain(int argc, _TCHAR* argv[])
{
	CQueue<char> queue;

	try
	{
		queue.appendTail('a');
		queue.appendTail('b');
		queue.appendTail('c');

		char head = queue.deleteHead();
		Test(head, 'a');

		head = queue.deleteHead();
		Test(head, 'b');

		queue.appendTail('d');
		head = queue.deleteHead();
		Test(head, 'c');

		queue.appendTail('e');
		head = queue.deleteHead();
		Test(head, 'd');

		head = queue.deleteHead();
		Test(head, 'e');

		queue.deleteHead();
	}
	catch (exception e)
	{
		cout << "Catch exception!";
	}
	cin.get();
	return 0;
}

