#include <iostream>
#include <cstring>
//#pragma warning(disable:4996)
using namespace std;

int main()
{
//	freopen("data.txt", "r", stdin);
//	freopen("out.txt", "w", stdout);
	int n, m;
	int flag = 0;
	int cnt = 0;
	int MOD[4000];
	int FRAC[4000];
	while (cin >> n)
	{
		cin >> m;
		memset(MOD, 0, sizeof(MOD));
		memset(FRAC, 0, sizeof(FRAC));
		int i, j;
		int len=-1;
		int flag = 0;
		MOD[0] = n;
		FRAC[0] = n / m;
		for (i = 1;; i++)
		{
			MOD[i] = (MOD[i - 1] - m*FRAC[i - 1]) * 10;
			FRAC[i] = MOD[i] / m;
			for (j = 1; j < i; j++)
			if (MOD[j] == MOD[i])
			{
				len = i - j;
				flag = 1;
				break;
			}
			if (flag == 1)break;
		}
		int c;
		cout << n << "/" << m << " = " << FRAC[0] << ".";
		for (c = 1; c < j; c++)
			cout << FRAC[c];
		cout << "(";
		for (c = j; c < i;c++)
		if (c>50)
		{
			cout << "...";
			break;
		}
		else
		{
			cout << FRAC[c];
		}
		cout << ")" << endl;
		cout << "   " << len << " = number of digits in repeating cycle" << endl << endl;
	}
//	fclose(stdin);
//	fclose(stdout);
	return 0;
}