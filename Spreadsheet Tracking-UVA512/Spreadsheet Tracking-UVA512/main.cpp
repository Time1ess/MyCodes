#include <iostream>
#include <string>
#include <cstdlib>
#include <cmath>
#pragma warning(disable:4996)
using namespace std;

int row, column;
int operations;

int ops[1000][20];
int ops_p=0;
int Total = 0;

void getresults(int,int *);

int main()
{
	freopen("data.txt", "r", stdin);
	freopen("out.txt", "w", stdout);
	cin >> row >> column;
	while (row!=0&&column!=0)
	{
		cin >> operations;
		ops_p = 0;
		memset(ops, 0, sizeof(ops));
		while (operations--)
		{
			cin.get();
			string cho = "";
			int op = -1;
			cho += cin.get();
			cho += cin.get();
			if (cho == "DR")op = 1;
			else if (cho == "DC")op = 2;
			else if (cho == "IC")op = 3;
			else if (cho == "IR")op = 4;
			else op = 5;

			ops[ops_p][0] = op;
			cin >> ops[ops_p++][1];
			int j = 2;
			if (ops[ops_p - 1][0] != 5)
			{
				for (int i = ops[ops_p - 1][1]; i > 0; i--)
					cin >> ops[ops_p - 1][j++];
			}
			else
			{
				for (int i = 0; i < 3; i++)
					cin >> ops[ops_p - 1][j++];
			}
		}
		int casenum;
		cin >> casenum;
		int *cases = new int[casenum * 2];
		int i = casenum;
		while (i--)
		{
			cin >> cases[(casenum - i - 1) * 2] >> cases[(casenum - i - 1) * 2 + 1];
		}
		//go operations and out results

		int *originaldata = new int[casenum * 2];
		memcpy(originaldata, cases,sizeof(int)*casenum*2);

		getresults(casenum,cases);

		Total++;
		cout << "Spreadsheet #" << Total << endl;
		for (int out = 0; out < casenum; out++)
		{
			cout << " Cell data in(" << originaldata[out * 2] << "," << originaldata[out * 2 + 1] << ") ";
			if (cases[out * 2] == -1 || cases[out * 2 + 1] == -1)cout << "GONE" << endl;
			else cout << "moved to(" << cases[out * 2]<<","<<cases[out*2+1]<< ")" << endl;
		}
		cin >> row >> column;
	}
	return 0;
}

void getresults(int cases,int *Case)
{
	int R=0;
	while (ops[R][0] != 0)
	{
		int choice = ops[R][0];
		switch (choice)
		{
			case 1:
			{
					  int j = 2;
					  int DR = ops[R][j++];
					  while (DR != 0)
					  {
						  for (int s = 0; s < cases; s += 2)
							 if (Case[s] == DR)
								  Case[s] = -1;
						  DR = ops[R][j++];
					  }
					  j = 2;
					  DR = ops[R][j++];
					  for (int s = 0; s < cases; s += 2)
					  {
						  int c = 0;
						  while (DR != 0)
						  {
							  if (Case[s] > DR)
								  c++;
							  DR = ops[R][j++];
						  }
						  Case[s] -= c;
					  } 
					  break;
			}
			case 2:
			{
					  int j = 2;
					  int DC = ops[R][j++];
					  while (DC != 0)
					  {
						  for (int s = 1; s < cases; s += 2)
							  if (Case[s] == DC)Case[s]=-1;
						  DC = ops[R][j++];
					  }
					  j = 2;
					  DC = ops[R][j++];
					  for (int s = 1; s < cases; s += 2)
					  {
						  int c = 0;
						  while (DC != 0)
						  {
							  if (Case[s] > DC)
								  c++;
							  DC = ops[R][j++];
						  }
						  Case[s] -= c;
					  }
					  break;
			}
			case 3:
			{
					  int j = 2;
					  int IC = ops[R][j++];
					  while (IC != 0)
					  {
						  for (int s = 1; s < cases; s += 2)
						  {
							  if (Case[s] >= IC)Case[s]++;
						  }
						  IC = ops[R][j++];
					  }
					  break;
			}
			case 4:
			{
					  int j = 2;
					  int IR = ops[R][j++];
					  while (IR != 0)
					  {
						  for (int s = 0; s < cases; s += 2)
						  {
							  if (Case[s] >= IR)Case[s]++;
						  }
						  IR = ops[R][j++];
					  }
					  break;
			}
			case 5:
			{
					  int change_x1 = ops[R][1], change_y1 = ops[R][2];
					  int change_x2 = ops[R][3], change_y2 = ops[R][4];
					  for (int s = 0; s < cases; s += 2)
					  {
						  if (Case[s] == change_x1&&Case[s + 1] == change_y1)
						  {
							  swap(Case[s], change_x2);
							  swap(Case[s + 1], change_y2);
							  break;
						  }
						  else if (Case[s] == change_x2&&Case[s + 1] == change_y2)
						  {
							  swap(Case[s], change_x1);
							  swap(Case[s + 1], change_y1);
							  break;
						  }
					  }
					  break;
			}
		}
		R++;
	}
}