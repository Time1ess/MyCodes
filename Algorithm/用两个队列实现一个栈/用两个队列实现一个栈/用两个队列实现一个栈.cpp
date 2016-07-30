// 用两个队列实现一个栈.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <queue>
#include <iostream>
using namespace std;

template <typename T>class MyStack
{
public:
	MyStack(void);
	~MyStack(void);

	void MyPush(const T &elem);
	T & MyPop(void);
private:
	queue<T> q1;
	queue<T> q2;
};

template <typename T> MyStack<T>::MyStack(void)
{

}

template <typename T> MyStack<T>::~MyStack(void)
{

}

template <typename T> 
void MyStack<T>::MyPush(const T &elem)
{
	if (q1.size() == 0 && q2.size() == 0)
		q1.push(elem);
	else if (q1.size() != 0)
		q1.push(elem);
	else
		q2.push(elem);

}

template <typename T>
T & MyStack<T>::MyPop(void)
{
	if (q1.size() == 0 && q2.size() == 0)
		throw exception("Stack Empty!");
	else if (q1.size() > 0)
	{
		while (q1.size() > 1)
		{
			T &tmp = q1.front();
			q1.pop();
			q2.push(tmp);
		}
		T &tmp = q1.front();
		q1.pop();
		return tmp;
	}
	else if (q2.size() > 0)
	{
		while (q2.size() > 1)
		{
			T &tmp = q2.front();
			q2.pop();
			q1.push(tmp);
		}
		T &tmp = q2.front();
		q2.pop();
		return tmp;
	}
	else
		throw exception("Unknown Error");
}

void Test(char expect, char fact)
{
	if (expect == fact)
		cout << "Test passed."<<endl;
	else
		cout << "Test failed."<<endl;
}


int _tmain(int argc, _TCHAR* argv[])
{
	MyStack<char> s;
	try
	{
		s.MyPush('a');
		s.MyPush('b');
		s.MyPush('c');

		char tmp;

		tmp = s.MyPop();
		Test('c', tmp);

		tmp = s.MyPop();
		Test('b', tmp);

		s.MyPush('d');

		tmp = s.MyPop();
		Test('d', tmp);

		tmp = s.MyPop();
		Test('a', tmp);

		tmp = s.MyPop();
	}
	catch (exception e)
	{
		cout << e.what() << endl;
	}
	cin.get();
	return 0;
}

