#include <iostream>
#include <vector>
#include <map>
#include <list>
#include <cstring>
#include <string>
#include <algorithm>
#include <ctime>
#pragma warning(disable:4996)

#define N 3
#define SIZE N*N
#define ARRAYSIZE 100000
using namespace std;

struct status
{
	string s;       //具体排列
	int zero;       //0所在位置
	int g;        //当前结点深度
	int father;      //父节点index
};

status goal;
status start;
status puzzle[ARRAYSIZE];

int direction[4] = { -N, N, -1, 1 };

vector<string> close;
map<int, int> open;   //将f和index放入容器中，按从小到大排列
int p = 0;

int f(status &);
int astar();
bool abletomove(string &, int);

int main()
{
	freopen("data.txt", "r", stdin);
	freopen("out.txt", "w", stdout);
	for (int i = 0; i < SIZE; i++)
	{
		start.s += cin.get();
		cin.get();
		if (start.s[i] == '0')start.zero = i;
	}
	for (int i = 0; i < SIZE; i++)
	{
		goal.s += cin.get();
		cin.get();
		if (goal.s[i] == '0')goal.zero = i;
	}
	int index;
	time_t start, end;

	start = clock();
	index= astar();
	end = clock();

	cout << index << endl;
	cout << double(end - start) / CLOCKS_PER_SEC << endl;
	return 0;
}

int f(status &p)
{
	int cnt = p.g;
	for (int i = 0; i < SIZE; i++)
	{
		if (p.s[i] != goal.s[i])
			cnt++;
	}
	return cnt;
}

bool abletomove(int zero, int direct)
{
	switch (direct)
	{
		case 0:
			if (zero < N)return false;
			break;
		case 1:
			if (zero > SIZE-N-1)return false;
			break;
		case 2:
			if (zero%N == 0)return false;
			break;
		case 3:
			if (zero%N == N - 1)return false;
			break;
	}
	return true;
}


int astar()
{
	start.g = 0;
	start.father = 0;
	puzzle[p] = start;
	open.insert(pair<int, int>(f(puzzle[p]), 0));
	while (!open.empty())
	{
		int index = open.begin()->second;
		open.erase(open.begin());
		close.push_back(puzzle[index].s);
		if (puzzle[index].s == goal.s)
			return index;
		for (int i = 0; i < 4; i++)
		{
			if (abletomove(puzzle[index].zero, i))
			{
				string s = puzzle[index].s;
				int j = puzzle[index].zero;
				s[j] = s[j + direction[i]];
				s[j + direction[i]] = '0';

				if (find(close.begin(), close.end(), s) != close.end())
					continue;
				p++;
				puzzle[p].s = s;
				puzzle[p].zero = j + direction[i];
				puzzle[p].father = index;
				puzzle[p].g = puzzle[index].g + 1;
				open.insert(pair<int, int>(f(puzzle[p]), p));
			}
		}
	}
	return -1;
}