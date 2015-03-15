#include <iostream>
using namespace std;


int main()
{
	int x = 0, y = 0;
	for (int i = 0; i < 3; i++)
	{
		int m;
		cin >> m;
		x = (m + x) / (x == 0 ? 1 : 2);
		cin >> m;
		y = (m + y) / (y == 0 ? 1 : 2);
		cout << x << "   " << y << endl;
	}
	
	cin.get();
	cin.get();
	return 0;
}