
/*
采用A*算法
*/
#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <vector>
#include <cstring>
#include <algorithm>
#include <string>
#pragma warning(disable:4996)
using namespace std;
#define N 3
#define MAXSIZE 200000
const int direction[4]{-N, N, -1, 1};

struct Puzzle
{
	string num;
	short zeropos;
	short dx;//当前结点在搜索树中深度
	short fx;//估价函数值
	int prev;//指向父节点
};

vector<pair<short, int>> openlist;
vector<pair<string,int>> closelist;
Puzzle puzzle[MAXSIZE];
int p;  //数组位置指针
string goal;
string head;


int process(string &start);
int posofzero(Puzzle &p);
int f(Puzzle &now, int index);
bool ablemove(int, int);
void Swap(int, Puzzle &);
bool findcloselist(string &);
bool sortmethod(pair<short, int>, pair<short, int>);

int main()
{
	freopen("data.txt", "r", stdin);
	freopen("out.txt", "w", stdout);
	for (int i = 0; i < N*N; i++)
	{
		head+= cin.get();
		cin.get();
	}
	for (int i = 0; i < N*N; i++)
	{
		goal+= cin.get();
		cin.get();
	}
	int target;
	memset(puzzle, 0, sizeof(puzzle));
	target=process(head);
	while (1)
	{
		cout << target << endl;
		for (int i = 0; i < N*N; i++)
		{
			cout << puzzle[target].num[i] << " ";
			if ((i + 1) % N == 0)cout << endl;
		}
		cout << endl;
		target = puzzle[target].prev;
		if (target == -1)break;


	}
	return 0;
}


int posofzero(Puzzle &p)
{
	for (int i = 0; i < N*N;i++)
	if (p.num[i] == '0')
		return i;
}

int f(Puzzle &now, int index)
{
	int cnt(puzzle[index].dx);
	for (int i = 0; i < N*N; i++)
	if (now.num[i] != goal[i])cnt++;
	return cnt;
}

bool ablemove(int direct, int index)
{
	switch (direct)
	{
		case 0:
			if (puzzle[index].zeropos/N == 0)return false;
			break;
		case 1:
			if (puzzle[index].zeropos/N == N-1)return false;
			break;
		case 2:
			if (puzzle[index].zeropos%N == 0)return false;
			break;
		case 3:
			if (puzzle[index].zeropos%N == N - 1)return false;
			break;
	}
	return true;
}


void Swap(int direct, string &p,int pos)
{
	int tmp;
	switch (direct)
	{
		case 0:
			tmp = p[pos];
			p[pos] = p[pos-N];
			p[pos-N] = tmp;
			break;
		case 1:
			tmp = p[pos];
			p[pos] = p[pos + N];
			p[pos + N] = tmp;
			break;
		case 2:
			tmp = p[pos];
			p[pos] = p[pos-1];
			p[pos-1] = tmp;
			break;
		case 3:
			tmp = p[pos];
			p[pos] = p[pos+1];
			p[pos+1] = tmp;
			break;
	}
}

bool findcloselist(string &s)
{
	for (auto x = closelist.begin(); x != closelist.end();x++)
	if (x->first == s)return true;
	return false;
}

bool sortmethod(pair<short, int> a, pair<short, int> b)
{
	if (a.first != b.first)
		return a.first > b.first;
	else
		return a.second > b.second;
}


int process(string &start)
{
	p = 0;
//	int cnt = 0;
	puzzle[p].num = start;
	puzzle[p].dx = 0;
	puzzle[p].zeropos = posofzero(puzzle[p]);
	puzzle[p].fx = f(puzzle[p], 0);
	puzzle[p].prev = -1;
	openlist.push_back(make_pair(puzzle[0].fx, p));
	while (!openlist.empty())
	{
		//cout << cnt++ << "T"<<endl;
		int index = openlist.back().second;
		openlist.pop_back();
		closelist.push_back(make_pair(puzzle[index].num,p));
		if (puzzle[index].num == goal)
			return index;
		for (int i = 0; i < 4; i++)
		{
			if (ablemove(i, index))
			{
				string s = puzzle[index].num;
				int pos(puzzle[index].zeropos);
				Swap(i, s, pos);

				if (!findcloselist(s))
				{
					p++;
					if (p == MAXSIZE)return -2;
					puzzle[p].num = s;
					puzzle[p].zeropos = pos + direction[i];
					puzzle[p].dx = puzzle[index].dx + 1;
					puzzle[p].prev = index;
					puzzle[p].fx = f(puzzle[p], p);
					openlist.push_back(make_pair(puzzle[p].fx, p));
				}
			}
		}
		//对openlist重新按照fx排序 从大到小，最后一个为最小的
		sort(openlist.begin(), openlist.end(), sortmethod);

	}
	return -1;
}

