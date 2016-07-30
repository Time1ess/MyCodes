//有一段楼梯有10级台阶，规定每一步只能跨一级或两级，要登上第10级台阶有几种不同的走法?
#include <iostream>
using namespace std;

int f[11];


//f[i]代表登上i级台阶的方法数
void dp(int i)
{
	if (i == 1)
	{
		f[i] = 1;
		return;
	}
	if (i == 2)
	{
		f[i] = 2;
		return;
	}
	if (f[i] != -1)return;
	f[i] = 0;
	dp(i - 1);
	dp(i - 2);
	f[i] += f[i - 1] + f[i - 2];
}

int main()
{
	int i;
	while (cin >> i&&i)
	{
		memset(f, -1, sizeof(f));
		dp(i);
		cout << f[i] << endl;
		cin.get();
	}
	return 0;
}