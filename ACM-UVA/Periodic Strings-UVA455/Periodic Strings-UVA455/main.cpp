#include <iostream>
#include <string>
using namespace std;
int main()
{
	string s;
	int n;
	int k;
	int j;
	cin >> n;
	cin.get();
	while (n--)
	{
		int len=0;
		cin.get();
		getline(cin, s);
		int i;
		for (i = 1; i <= s.length(); i++)
		{
			if (s.length() % i != 0)continue;
			string ps(s.begin(),s.begin()+i);
			len = ps.length();
			//finished substring set,now judge ps in s,if there is no compat,stop and continue next cycle
			//else break, finish looking.
			for (k = 0; k < s.length(); k += i)
			{
				for (j = 0; j < i; j++)
				{
					if (ps[j] == s[j+k])continue;
					else break;
				}
				if (j == i)continue;
				else break;
			}
			if (k == s.length())break;
			else continue;
		}
		if (n > 0)
			cout << len << endl << endl;
		else
			cout << len << endl;
	}
	return 0;
}