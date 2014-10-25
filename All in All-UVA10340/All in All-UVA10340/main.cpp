#include <iostream>
#include <cstring>
//#pragma warning(disable:4996)
using namespace std;

int main()
{
//	freopen("data.txt", "r", stdin);
//	freopen("out.txt", "w", stdout);
	char fir[150000], sec[150000];
	int casenum = 0;
	while (cin>>fir)
	{

		cin >> sec;
		int i;
		int j = 0;
		for (i = 0,j=0;i<strlen(fir)&&j<strlen(sec);)
		{
			if (fir[i] == sec[j])j++,i++;
			else j++;
		}
		if (strlen(fir)==i)cout << "Yes";
		else cout << "No";
		cout << endl;
		memset(fir, 0, sizeof(fir));
		memset(sec, 0, sizeof(sec));
	}

//	fclose(stdin);
//	fclose(stdout);
	return 0;
}