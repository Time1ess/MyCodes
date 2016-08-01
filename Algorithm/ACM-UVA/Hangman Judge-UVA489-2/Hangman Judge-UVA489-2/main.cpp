//#define LOCAL
#include <iostream>
#include <cstring>
#include <cstdio>
#pragma warning(disable:4996)
using namespace std;
#define maxn 100
int chance;
char s[maxn], s2[maxn];
int win, lose;
int Left;

void guess(char ch)
{
	int bad = 1;
	for (int i = 0; i<strlen(s); i++)
	if (s[i] == ch)
	{
		Left--;
		s[i] = ' ';
		bad = 0;
	}
	if (bad) --chance;
	if (!chance) lose = 1;
	if (!Left) win = 1;
}

int main()
{
#ifdef LOCAL
	freopen("data.txt", "r", stdin);
	freopen("out.txt", "w", stdout);
#endif
	int rnd;
	while (cin >> rnd&&rnd != -1)
	{
		cin >> s;
		cin >> s2;
		cout << "Round " << rnd << endl;
		win = lose = 0;
		Left = strlen(s);
		chance = 7;
		for (int i = 0; i<strlen(s2); i++)
		{
			guess(s2[i]);
			if (win || lose)break;
		}
		if (win) cout << "You win.\n";
		else if (lose) cout << "You lose.\n";
		else cout << "You chickened out.\n";
	}
	return 0;
}