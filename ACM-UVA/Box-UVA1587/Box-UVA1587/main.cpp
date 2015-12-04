#include <iostream>
#include <cstring>
#include <algorithm>
//#pragma warning(disable:4996)
using namespace std;

bool right(int arr[6][2])
{
	if (arr[0][0] != arr[1][0] || arr[0][1] != arr[1][1])return false;
	if (arr[2][0] != arr[3][0] || arr[2][1] != arr[3][1])return false;
	if (arr[4][0] != arr[5][0] || arr[4][1] != arr[5][1])return false;
	if (arr[0][0] != arr[2][0])return false;
	if (arr[0][1] != arr[4][0])return false;
	if (arr[2][1] != arr[4][1])return false;
	return true;
}

int main()
{
//	freopen("data.txt", "r", stdin);
//	freopen("out.txt", "w", stdout);
	int w, h;
	int casenum = 0;
	int arr[6][2];
	int i, j;
	while (cin >> w)
	{
		cin >> h;
		arr[0][0] = w > h ? h : w;
		arr[0][1] = w > h ? w : h;
		for (i = 1; i < 6; i++)
		{
			cin >> w;
			cin >> h;
			arr[i][0] = w > h ? h : w;
			arr[i][1] = w > h ? w : h;
		}
		for (i = 0; i < 6;i++)
		for (j = i + 1; j < 6; j++)
		{
			if (arr[i][0] > arr[j][0])
				swap(arr[i], arr[j]);
		}
		for (i = 0; i < 6; i++)
		for (j = i + 1; j < 6; j++)
		{
			if (arr[i][1] > arr[j][1]&&arr[i][0]>=arr[j][0])
				swap(arr[i], arr[j]);
		}
		if (right(arr))cout << "POSSIBLE";
		else cout << "IMPOSSIBLE";
		cout << endl;
	}
//	fclose(stdin);
//	fclose(stdout);
	return 0;
}