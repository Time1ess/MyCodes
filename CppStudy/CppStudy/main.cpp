#include <iostream>
#include <vector>
#include <fstream>
using namespace std;


double b(double n)
{
	if (n == 0)return 250000;
	if (n == 361)return 0;

}

int main()
{
	double p = 1310.01;
	ofstream fout("out.txt");
	double sum = 250000;
	do
	{
		sum = 250000;
		p += 0.0001;
		for (int i = 0; i < 361; i++)
		{
			sum = sum*1.004 - p;
			fout << sum << endl;
		}
		//cout << "now p=" << p << endl;
		cout << sum << endl;

	}while (fabs(sum - 0) > 0.1);
	cout.precision(14);
	cout << "Final p="<<p << endl;
	cout << pow(1.004, 12) << endl;
	cin.get();
	return 0;
}