#include <iostream>
using namespace std;


int main()
{
	int n;
	cin >> n;
	char ch;
	int *ans = new int[n];
	int tmp;
	int i;
	int index = 0;
	cin.get();
	for (i = 0; i < n; i++)
	{
		ans[i] = 0;
		tmp = 1;
		while ((ch=cin.get()) != '\n')
		{
			if (ch == '0')
			{
				ans[i] += tmp;
				tmp++;
			}
			else tmp = 1;
		}
	}
	for (i = 0; i < n; i++)
		cout << ans[i] << endl;
	return 0;
}