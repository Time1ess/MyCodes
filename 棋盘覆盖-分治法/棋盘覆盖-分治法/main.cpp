/*
	问题描述:
	在一个2^k×2^k （k≥0）个方格组成的棋盘中，
	恰有一个方格与其他方格不同，称该方格为特殊
	方格。显然，特殊方格在棋盘中可能出现的位置
	有4^k种，因而有4^k种不同的棋盘，棋盘覆盖问
	题（chess cover problem）要求用4种不同形状
	的L型骨牌覆盖给定棋盘上除特殊方格以外的所
	有方格，且任何2个L型骨牌不得重叠覆盖。
	*/

#include <iostream>
using namespace std;

#define MAXSIZE 8
int chess[MAXSIZE][MAXSIZE];
int flag = 0;

void chessBoard(int tr, int tc, int dr, int dc, int size)
{
	if (size == 1)return;
	int s = size>>1;
	int f = ++flag;

	if (dr < tr + s&&dc < tc + s)
		chessBoard(tr, tc, dr, dc, s);
	else
	{
		chess[tr + s - 1][tc + s - 1] = f;
		chessBoard(tr, tc, tr + s - 1, tc + s - 1, s);
	}

	if (dr < tr + s&&dc >= tc + s)
		chessBoard(tr, tc + s, dr, dc, s);
	else
	{
		chess[tr + s - 1][tc + s] = f;
		chessBoard(tr, tc + s, tr + s - 1, tc + s, s);
	}

	if (dr >= tr + s&&dc < tc + s)
		chessBoard(tr + s, tc, dr, dc, s);
	else
	{
		chess[tr + s][tc + s - 1] = f;
		chessBoard(tr + s, tc, tr + s, tc + s - 1, s);
	}

	if (dr >= tr + s&&dc >= tc + s)
		chessBoard(tr + s, tc + s, dr, dc, s);
	else
	{
		chess[tr + s][tc + s] = f;
		chessBoard(tr + s, tc + s, tr + s, tc + s, s);
	}
}

void printChessBoard()
{
	for (int i = 0; i < MAXSIZE; i++)
	{
		for (int j = 0; j < MAXSIZE; j++)
		{
			cout.width(2);
			cout << chess[i][j] << " ";
		}
		cout << endl;
	}
}

int main()
{
	int keyr;
	int keyc;
	cin >> keyr >> keyc;
	memset(chess, 0, sizeof(chess));
	chess[keyr][keyc] = -1;
	printChessBoard();
	chessBoard(0, 0, keyr, keyc, MAXSIZE);
	cout << endl << endl;
	printChessBoard();
	cin.get();
	cin.get();
	return 0;
}