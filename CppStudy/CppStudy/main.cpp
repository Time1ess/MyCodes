#include <iostream>
#include <cstdio>
using namespace std;
//#pragma warning(disable:4996)
//1
int algo(char *s, int len)
{
	int sum = 0;
	int c[4] = { 0 };
	for (int i = 0; i < len; i++)
	{
		switch (s[i])
		{
		case 'A':
			sum += c[1] + c[2] + c[3];
			c[0]++;
			break;
		case 'C':
			sum += c[2] + c[3];
			c[1]++;
			break;
		case 'G':
			sum += c[3];
			c[2]++;
			break;
		case 'T':
			c[3]++;
			break;
		default:
			break;
		}
	}
	return sum;
}


int main()
{
	char s[13]= "ACGGGCTACGTC";
	s[12] = '\0';
	cout << s << endl;
	int ans = algo(s, 12);
	cout << ans;
	cin.get();
	return 0;
}