#include <iostream>
#include <initializer_list>
using namespace std;
template<class T>
T sum(initializer_list<T> il);

int main()
{
	int x = 5, y = 3, z = 6, k = 3, b = 88;
	cout << sum({ x, y, z, k, b }) << endl;
	cin.get();
	return 0;
}
template<class T>
T sum(initializer_list<T> il)
{
	T total=0;
	for (auto x = il.begin(); x != il.end(); x++)
		total += *x;
	return total;
}