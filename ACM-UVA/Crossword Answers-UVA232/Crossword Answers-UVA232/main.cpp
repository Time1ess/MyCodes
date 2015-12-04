#include <iostream>
#include <cstdio>
#include <cstring>
#pragma warning(disable:4996)
using namespace std;

bool notyetout(int i,int j,int im[10][10],char pm[10][10])
{
	bool isnot = true;
	if (i>0)
	while (i--&&pm[i][j]!='*')
		isnot = isnot&&!im[i][j];
	return isnot;
}

int main()
{
//	freopen("input.txt", "r", stdin);
	cout.setf(ios_base::right, ios_base::adjustfield);
//	freopen("out.txt", "w", stdout);
	char maps[10][10];
	int indexmap[10][10];
	int r, c;
	int i = 0;
	int cnt = 0;
	int j = 0;
	memset(indexmap, 0, sizeof(indexmap));
	memset(maps, 0, sizeof(maps));
	while (cin>>r)
	{
		int index = 1;
		if (r == 0)return 0;
		cin >> c;
		cin.get();
		for (i = 0; i < r; i++)
		{
			for (j = 0; j < c; j++)
				cin.get(maps[i][j]);
			cin.get();
		}
		for (i = 0; i < r;i++)
		for (j = 0; j < c; j++)
		{
			int flag = 0;
			if ((i == 0 || j == 0)&&maps[i][j]!='*')flag = 1;
			if (i>0 && maps[i - 1][j] == '*'&&maps[i][j] != '*')flag = 1;
			if (j>0 && maps[i][j - 1] == '*'&&maps[i][j] != '*')flag = 1;
			if (flag == 1)indexmap[i][j] = index++;
		}
		if (cnt != 0)cout << endl;
		cout << "puzzle #" << ++cnt << ":" << endl;
		cout << "Across" << endl;
		for (i = 0; i < r; i++)
		for (j = 0; j < c; j++)
			{
				if (indexmap[i][j] != 0)
				{
					cout << " ";
					cout.width(2);
					cout<< indexmap[i][j] << ".";
					while (maps[i][j] != '*'&&j < c)
					{
						cout << maps[i][j];
						j++;
					}
					cout << endl;
				}
			}
		int tmpi;
		int tmpj;
		cout << "Down" << endl; 
		for (i = 0; i < r;i++)
		for (j = 0; j < c; j++)
		{
			tmpj = j;
			tmpi = i;
			if (indexmap[i][j] != 0&&notyetout(i,j,indexmap,maps))
			{
				cout << " ";
				cout.width(2);
				cout << indexmap[i][j] << ".";
				while (maps[i][j] != '*'&&i < r)
				{
					cout << maps[i][j];
					i++;
				}
				cout << endl;
			}
			i = tmpi;
			j = tmpj;
		}



		memset(indexmap, 0, sizeof(indexmap));
		memset(maps, 0, sizeof(maps));
	}
//	fclose(stdin);
//	fclose(stdout);
	return 0;
}