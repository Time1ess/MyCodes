#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <ctime>
#include <conio.h>
#pragma warning(disable:4996)

using namespace std;

int win = 0;
int lose = 0;
int key = 0;
int score = 0;
int map[4][4] = { 0 };
int blank = 16;

void showmap();
void movecolumn(int);
void moveline(int);
void gernerate();
bool find_eight();

int main(int argc, const char * argv)
{
	srand(time(0));
	showmap();
	while (1)
	{
		cin.get();

		gernerate();
		showmap();
	}
}

bool find_eight()
{
	for (int i = 0; i < 4;i++)
	for (int j = 0; j < 4;j++)
	if (map[i][j] >= 8)return true;
	return false;
}

void showmap()
{
	system("cls");
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
			cout << map[i][j] << " ";
		cout << endl;
	}
}

void gernerate()
{
	int pos = 0;
	if (find_eight())
	{
		if (rand()%100 > 30)
		{
			while (blank != 0)
			{
				pos = rand() % 16;
				if (map[pos / 4][pos % 4] == 0)
				{
					map[pos / 4][pos % 4] = 2;
					blank--;
					return;
				}
			}
		}
		else
		{
			while (blank != 0)
			{
				pos = rand() % 16;
				if (map[pos / 4][pos % 4] == 0)
				{
					map[pos / 4][pos % 4] = 4;
					blank--;
					return;
				}
			}
		}
	}
	else
	{
		while (blank != 0)
		{
			pos = rand() % 16;
			if (map[pos / 4][pos % 4] == 0)
			{
				map[pos / 4][pos % 4] = 2;
				blank--;
				return;
			}
		}
	}
}

void move()
{
	int direct = key;
	switch (direct)
	{
		case 2:
			movecolumn(0);
		case 4:
			moveline(0);
		case 6:
			moveline(1);
		case 8:
			movecolumn(1);
		default:return;
	}
	return;
}

void movecolumn(int direct)
{
	if (direct == 0)
	{
		int j, i, k;
		for (j = 0; j < 4; j++)
		{
			for (i = 3; i >= 0; i--)
			{
				if (map[i][j] == 0)
				{
					for (int m = i; m>0; m--)
					{
						map[m][j] = map[m - 1][j];
					}
					map[0][j] = 0;
				}
				for (k = i - 1; k >= 0; k--)
				{
					if (map[k][j] == map[i][j])
					{
						map[i][j] += map[k][j];
						map[k][j] = 0;
						break;
					}
					else if (map[k][j] != 0)break;
				}
			}
		}
	}
	else
	{

	}
}
