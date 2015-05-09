#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
using namespace std;
#define MAXSIZE 100
char flags[MAXSIZE];
char C[3] = { 'r','w','b' };

void randomCreate(int len)
{
	for (int i = 0; i < len; i++)
		flags[i] = C[rand() % 3];
}



void resort()
{
	int len = strlen(flags);
	char tmp;
	int r, k, b,i;
	for (i = 0; flags[i] == 'R'&&i<len; i++);
	r = i;
	for (i = len - 1; flags[i] == 'B'&&i >= 0; i--);
	b = i;
	k = r;
	while (k<=b)
	{
		if (flags[k] == 'R'&&r!=k)
		{
			tmp = flags[k];
			flags[k] = flags[r];
			flags[r] = tmp;

			r++;
		}
		else if (flags[k] == 'B'&&b!=k)
		{
			tmp = flags[k];
			flags[k] = flags[b];
			flags[b] = tmp;

			b--;
		}
		else
			k++;
	}
}

bool check(int num,int len)
{
	for (int j = 0; j < num; j++)
	{
		randomCreate(len);
		cout << "Before Sort:";
		for (int i = 0; i < len; i++)
			cout << (flags[i] = (char)toupper(flags[i]));
		cout << endl;
		resort();
		cout << "After Sort: ";
		for (int i = 0; i < len; i++)
			cout << flags[i];
		cout << endl;
		char s = flags[0];
		int i = 1;
		while(i<len)
		{
			if (s == flags[i])
			{
				i++;
				continue;
			}
			else if (s == 'R')
			{
				s = flags[i++];
				continue;
			}
			else if (s == 'W'&&flags[i] == 'B')
			{
				s = flags[i++];
				continue;
			}
			else
				break;
		}
		if (i == len)
		{
			cout << "Check Ok!" << endl;
			continue;
		}
		else
		{
			cout << "Check Fail!" << endl;
			return false;
		}
	}
	return true;
}


int main()
{
//	srand(time(0));
	while (cin.getline(flags, 100))
	{
		cout << "Before Sort:";
		for (int i = 0; i < strlen(flags); i++)
			cout << (flags[i] = (char)toupper(flags[i]));
		cout << endl;
		resort();
		cout << "After Sort: ";
		for (int i = 0; i < strlen(flags); i++)
			cout << flags[i];
		cout << endl;
	}
	//if (check(1000, 50))
	//	cout << endl << "Success!" << endl;
	//else
	//	cout << endl << "Failed!" << endl;
	cin.get();
	return 0;
}