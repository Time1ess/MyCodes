#include <iostream>
using namespace std;

int main()
{
	int n, total = 0;
	while (cin >> n)
	{
		total = n;
		while (n >= 5)
		{
			total += n / 5;
			n = n / 5 + n % 5;
		}
		cout << total << endl;
	}
	return 0;
}