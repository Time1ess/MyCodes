#include <iostream>
#include <string>
#include <vector>
#include <cstring>
#include <algorithm>
//#pragma warning(disable:4996)
using namespace std;

int Max(int cnt[4])
{
	int i = 0, j = 1;
	for (j = 1; j < 4;j++)
	if (cnt[j]>cnt[i])i = j;
	return i;
}

int main()
{
//	freopen("data.txt", "r", stdin);
//	freopen("out.txt", "w", stdout);
	int casenum;
	cin >> casenum;
	while (casenum--)
	{
		int tmpcnt[4] = { 0, 0, 0, 0 };
		int n, m;
		int i,j;
		int errorcnt=0;
		cin >> m;
		cin >> n;
		while (cin.get() != '\n')continue;
		if (m<4 || m>50 || n<4 || n>1000)continue;
		string s;
		vector<string> vs;
		for (i = 0; i < m; i++)
		{
			getline(cin, s);
			vs.push_back(s);
		}
		string ts="";
		for (j = 0; j < n; j++)
		{
			int ch;
			for (i = 0; i < m;i++)
				switch (vs[i][j])
				{
						case 'A':
							tmpcnt[0]++;
							break;
						case 'C':
							tmpcnt[1]++;
							break;
						case 'G':
							tmpcnt[2]++;
							break;
						case 'T':
							tmpcnt[3]++;
							break;
				}
			ch = Max(tmpcnt);
			switch (ch)
			{
				case 0:
					ts += 'A';
					errorcnt += m - tmpcnt[ch];
					break;
				case 1:
					ts += 'C';
					errorcnt += m - tmpcnt[ch];
					break;
				case 2:
					ts += 'G';
					errorcnt += m - tmpcnt[ch];
					break;
				case 3:
					ts += 'T';
					errorcnt += m - tmpcnt[ch];
					break;
			}
			memset(tmpcnt, 0, sizeof(tmpcnt));
		}
		cout << ts << endl << errorcnt << endl;
	}
//	fclose(stdin);
//	fclose(stdout);
	return 0;
}