#include <iostream>
#include <cstdlib>
#include <algorithm>
#include <cmath>
using namespace std;
#define PI 3.14159

double theta[21];


double SUMCOS(int n, int p,int s)
{
	double ans = 0;
	for (int i = 1; i <= n; i++)
		ans += cos((6 * p + s)*theta[i]);
	return ans;
}

bool nexttheta(int n)
{
	theta[n] += 0.001;
	for (int k = n; k >= 2; k--)
	{
		if (theta[k] >= PI / 2)
		{
			theta[k - 1] += 0.001;
			theta[k] = 0;
		}
	}
	if (theta[1] >= PI / 2)return false;
	return true;
}

void printtheta(int n)
{
	for (int k = n; k >= 1; k--)
	{
		cout.precision(5);
		cout << theta[k] << " ";
	}
	cout << endl;
}

int main()
{
	int n;
	double m;
	int k;
	bool sol = false;
	cout << "Input N:";
	cin >> n;
	cout << "Input m:";
	cin >> m;
	cout << "Input k:";
	cin >> k;
	memset(theta, 0, sizeof(theta));
	do
	{
		
		double ans = SUMCOS(n, 0, 1);
		double c = fabs(ans - PI / 4 * m*n);
		cout.precision(5);
		cout << ans << "\t";
		cout.precision(5);
		cout<< c<< "\t";
		printtheta(n);
		if (c < 0.001)break;
	} while (nexttheta(n));
	cout << "OK" << endl;
	cin.get();
	//while (!sol)
	//{
	//	if (SUMCOS(n, 0, 1) != PI / 4 * n*m)
	//	{
	//	}
	//}
}