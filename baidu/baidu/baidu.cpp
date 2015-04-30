// baidu.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <iostream>
#include <map>
#include <stack>
using namespace std;

int main()
{
	int T;
	cin >> T;
	while (T--)
	{
		map<int, int> digitsCount;
		stack<int> digits;
		int n;
		cin >> n;
		int tmp;
		for (int i = 0; i < n; i++)
		{
			cin >> tmp;
			digits.push(tmp);
			digitsCount[tmp]++;
		}
		int size = digits.size();
		while (!digits.empty())
		{
			if (size != digits.size())cout << "->";
			tmp = digits.top();
			cout << tmp;
			digitsCount[tmp]--;
			while (digitsCount[tmp] != 0)
			{
				int ttmp = digits.top();
				digits.pop();
				digitsCount[ttmp]--;
			}

			digits.pop();
		}
		digitsCount.clear();
	}
	return 0;
}