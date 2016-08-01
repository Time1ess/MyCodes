#include <iostream>
#include <cstring>
#include <string>
#include <algorithm>
//#pragma warning(disable:4996)
using namespace std;


int main()
{
//	freopen("data.txt", "r", stdin);
//	freopen("out.txt", "w", stdout);
	int master[1000], driven[1000];
	string s1, s2;
	int i = 0;
	int j, k;
	while (getline(cin,s1))
	{
		getline(cin, s2);
		memset(master, 0, sizeof(master));
		memset(driven, 0, sizeof(driven));
		int len1 = s1.length();
		int len2 = s2.length();
		for (i = 0; i < len1; i++)
			master[i] = s1[i] - '0';
		for (i = 0; i < len2; i++)
			driven[i] = s2[i] - '0';
		int minlen = max(len1, len2);
		for (i = 0; i < len1; i++)
		{
			for (j = 0; j < len2; j++)
			if (master[i + j] + driven[j]>3)
				break;
			if (j == len2)
				break;
		}
		int length1 = len2 + i;
		for (i = 0; i < len2; i++)
		{
			for (j = 0; j < len1; j++)
			if (master[j] + driven[i + j]>3)
				break;
			if (j == len1)
				break;
		}
		int length2 = len1 + i;
		minlen = max(minlen, min(length1, length2));
		cout << minlen << endl;
	}
//	fclose(stdin);
//	fclose(stdout);
	return 0;
}
