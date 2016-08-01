#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <cstdlib>
#pragma warning(disable:4996)
using namespace std;

double T, D, H;
double h, e;


void reversesolvee()
{
	e = (H - T) / 0.5555 + 10.0;
}


void solvee()
{
	e = 6.11*exp(5417.7530*((1 / 273.16) - (1 / (D + 273.16))));
}

void solveh()
{
	solvee();
	h = 0.5555*(e - 10.0);
}

void solveH()
{
	solveh();
	H = T + h;
}
void solveT()
{
	solveh();
	T = H - h;
}
void solveD()
{
	reversesolvee();
	D = 1 / (1 / 273.16 - log(e/6.11) / 5417.7530) - 273.16;
}


void solve(char le1, char le2)
{
	if ((le1 == 'T'&&le2 == 'D') || (le1 == 'D'&&le2 == 'T'))
		solveH();
	else
	if ((le1 == 'T'&&le2 == 'H') || (le1 == 'H'&&le2 == 'T'))
		solveD();
	else
	if ((le1 == 'D'&&le2 == 'H') || (le1 == 'H'&&le2 == 'D'))
		solveT();
}


int main()
{
//	freopen("D:\\MyCodes\\ACM-POJ\\Debug\\a.txt", "r", stdin);
//	freopen("D:\\MyCodes\\ACM-POJ\\Debug\\b.txt", "w", stdout);
	char cho1, cho2;
	double va1, va2;
	while (cin>>cho1>>va1>>cho2>>va2 && cho1 != 'E')
	{
		switch (cho1)
		{
		case 'T':
			T = va1;
			break;
		case 'D':
			D = va1;
			break;
		case 'H':
			H = va1;
			break;
		}
		switch (cho2)
		{
		case 'T':
			T = va2;
			break;
		case 'D':
			D = va2;
			break;
		case 'H':
			H = va2;
			break;
		}
		solve(cho1, cho2);
		printf("T %.1f D %.1f H %.1f\n", T, D, H);
	}
	return 0;
}