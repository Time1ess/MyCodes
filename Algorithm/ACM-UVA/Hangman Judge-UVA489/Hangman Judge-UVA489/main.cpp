#define LOCAL
#include <iostream>
#include <set>
#include <map>
#include <cstring>
#include <cstdio>
#pragma warning(disable:4996)
using namespace std;

int main()
{
#ifdef LOCAL
	freopen("data.txt", "r", stdin);
	freopen("out.txt", "w", stdout);
#endif
	int cas;
	int total;
	int r_cnt;
	int e_cnt;
	char s[1024];
	char g[1024];
	map<char, int> m;
	set<char> error;
	set<char> right;
	while (cin >> cas)
	{
		cin.get();
		if (cas == -1) break;
		m.clear();
		error.clear();
		right.clear();
		memset(s, 0, sizeof(s));
		memset(g, 0, sizeof(g));
		gets(s);
		gets(g);
		total = strlen(s);
		char * p = s;
		while (*p)
		{
			if (m.find(*p) != m.end())
				m[*p]++;
			else
				m[*p] = 1;
			p++;
		}
		r_cnt = 0;
		e_cnt = 0;
		p = g;
		int flag = 0;
		while (*p)
		{
			if (m.find(*p) != m.end())
			{
				if (right.find(*p) == right.end())
				{
					r_cnt += m[*p];
					right.insert(*p);
				}
			}
			else
			{
				if (error.find(*p) == error.end())
				{
					e_cnt++;
					error.insert(*p);
				}
			}
			if (r_cnt == total)
			{
				flag = 1;
				break;
			}
			if (e_cnt >= 7)
			{
				flag = 2;
				break;
			}
			p++;
		}
		cout << "Round " << cas << endl;
		switch (flag)
		{
			case 0:
				cout << "You chickened out." << endl;
				break;
			case 1:
				cout << "You win." << endl;
				break;
			case 2:
				cout << "You lose." << endl;
				break;
		}
	}
	return 0;
}