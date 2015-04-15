// 递归实现逆序字符串输出.cpp : 定义控制台应用程序的入口点。
//
//编写一个函数，输入int型，返回整数逆序后的字符串。如：输入123，
//返回"321"，要求必须使用递归，不能用全局变量，输入必须是一个参数,
//必须返回字符串
#include "stdafx.h"
#include <iostream>
#include <string>
using namespace std;


string ReversIntToString(int original)
{
	int unSignedOriginal = original >= 0 ? original : -original;
	string result = "";
	if (unSignedOriginal < 10)
		return result += unSignedOriginal + '0';
	result += unSignedOriginal % 10 + '0';
	result += ReversIntToString(unSignedOriginal / 10);
	if (original < 0)result += '-';
	return result;
}

int _tmain(int argc, _TCHAR* argv[])
{
	string s = "";
	s = ReversIntToString(-123);
	cout << s << endl;
	cin.get();
	return 0;
}

