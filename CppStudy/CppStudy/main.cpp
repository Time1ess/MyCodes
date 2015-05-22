#include <iostream>
using namespace std;

int main()
{
	char name[10];
	//cin >> name;
	name[0] = 0xb6;
	name[1] = 0xc5;
	name[2] = 0xd3;
	name[3] = 0xd3;
	name[4] = 0xe5;
	name[5] = 0xb7;
	for (int i = 0; i < 6; i++)
		cout << unsigned int(name[i]) << endl;
	cout << name << endl;
	cin.get();
	cin.get();
	return 0;
}