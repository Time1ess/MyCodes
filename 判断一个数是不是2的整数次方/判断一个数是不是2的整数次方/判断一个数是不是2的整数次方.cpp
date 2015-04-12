// 判断一个数是不是2的整数次方.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <iostream>
using namespace std;

bool TwoPower(int n)
{
	return (n>0)&&!((n - 1)&n);
}

int _tmain(int argc, _TCHAR* argv[])
{
	cout << TwoPower(1) << endl;
	cout << TwoPower(2) << endl;
	cout << TwoPower(3) << endl;
	cout << TwoPower(4) << endl;
	cout << TwoPower(8) << endl;
	cout << TwoPower(-2) << endl;
	cin.get();
	return 0;
}

