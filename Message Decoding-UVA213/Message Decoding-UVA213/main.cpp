//#define LOCAL
#include <iostream>
#include <cstring>
//#pragma warning(disable:4996)
using namespace std;
char code[11];
char tmp[20];

int readchar()
{
	for (;;)
	{
		int ch = getchar();
		if (ch != '\n'&&ch != '\r'&&ch!=' ')return ch;
	}
}

int readint(int c)
{
	int v = 0;
	while (c--)
		v = v * 2 + readchar() - '0';
	return v;
}

int segmentover(int data, int len)
{
	if (len == 3 && data == 7)return true;
	if (len == 2 && data == 3)return true;
	if (len == 1 && data == 1)return true;
	return false;
}

int main()
{
#ifdef LOCAL
	freopen("data.txt", "r", stdin);
	freopen("out.txt", "w", stdout);

#endif
	while (gets(tmp))
	{
		int i=0;
		while (tmp[i] != '\0')
			code[i] = tmp[i++];
		int len;
		while (len = readint(3))
		{
			if (len == 0)break;
			int data;
			while (1)
			{
				data = readint(len);
				if (segmentover(data, len))break;
				cout << code[data + (len - 1)*(len - 1)];
			}
		}
		cout << endl;
		cin.get();
	}
	return 0;
}