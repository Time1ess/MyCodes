#include <iostream>
#include <string>
using namespace std;
int main()
{
	string s;
	int n;
	cin >> n;
	cin.get();
	while (n--)
	{
		cin.get();
		getline(cin, s);
		int i;
		for (i = 1; i < s.length(); i++)
		{
			string ps(s.begin(),s.begin()+i);
			for (int j = i; j < s.length(); j++)
			{

			}
		}
	}
	cin.get();
	return 0;
}