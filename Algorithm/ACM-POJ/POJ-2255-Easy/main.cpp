#include <iostream>
#include <cstring>
#pragma warning(disable:4996)
using namespace std;
char s1[33];
char s2[33];
char ans[33];
void build(int n, char* pre, char* in, char* post)
{
	if (n <= 0) return;
	int index = strchr(in, pre[0]) - in;	//查找先序序列中第一个字符在中序序列中出现的位置
	build(index, pre + 1, in, post);	//对结点的左子树进行使用后续遍历
	build(n - index - 1, pre + index + 1, in + index + 1, post + index);//对结点的右子树进行使用后续遍历
	post[n - 1] = pre[0];	//添加该结点进入后续遍历序列
}
int main()
{
	while (cin >> s1 >> s2)
	{
		int n = strlen(s1);
		build(n, s1, s2, ans);
		ans[n] = '\0';
		cout << ans << endl;
	}
	return 0;
}