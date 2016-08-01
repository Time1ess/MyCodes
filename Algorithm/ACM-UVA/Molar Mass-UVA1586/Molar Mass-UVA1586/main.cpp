#include <iostream>
#include <string>
#include <cctype>
using namespace std;

const double mass[4] = { 12.01, 1.008, 16.00, 14.01 };

int main()
{
	string s;
	cout.setf(ios_base::fixed);
	cout.precision(3);
	int n;
	int i;
	int k;
	double tmp;
	int num;
	cin >> n;
	cin.get();
	double *p = new double[n];
	for (i = 0; i < n; i++)
	{
		s = "";
		p[i] = 0;
		getline(cin,s);
		tmp = 0;
		num = 0;
		for (k = 0; k < s.length(); k++)
		{	
			switch (s[k])
			{
				case 'C':
					tmp += mass[0];
					break;
				case 'H':
					tmp += mass[1];
					break;
				case 'O':
					tmp += mass[2];
					break;
				case 'N':
					tmp += mass[3];
					break;
				default:
					break;
			}
			if (isalpha(s[k + 1])||k==s.length()-1)
			{
				p[i] += tmp;
				tmp = 0;
			}
			else
			{
				k++;
				if (isdigit(s[k]))
				{
					num = s[k] - 48;
					if (isdigit(s[k + 1]))
					{
						num = num*10 + s[k + 1] - 48;
						p[i] += tmp*num;
						tmp = 0;
						num = 0;
						k++;
						continue;
					}
					p[i] += num*tmp;
					tmp = 0;
					num = 0;
					continue;
				}
			}
		}
	}
	for (i = 0; i < n; i++)
		cout << p[i] << endl;
	return 0;
}