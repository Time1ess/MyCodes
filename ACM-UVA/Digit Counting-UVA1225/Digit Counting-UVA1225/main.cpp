#include <iostream>
#include <cstring>
#include <string>
#include <sstream>
using namespace std;

int main()
{
	int n;
	string max;
	cin >> n;
	int i = 0;
	int l;
	int cnt[10];
	while (n--)
	{
		cin >> l;
		memset(cnt, 0, sizeof(cnt));
		int k;
		for (k = 1; k < l + 1; k++)
		{
			stringstream ss;
			ss << k;
			ss >> max;
			for (i = 0; i < max.size(); i++)
				cnt[max[i] - '0'] ++;
		}
		for (i = 0; i < 10; i++)
		{
			if (i % 10 == 0)cout << cnt[i];
			else cout << " " << cnt[i];
		}
		cout << endl;
	}
	return 0;
}
