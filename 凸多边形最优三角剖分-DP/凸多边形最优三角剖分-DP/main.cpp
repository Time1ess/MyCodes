//凸多边形最优三角剖分
#include <iostream> 
#include <stack>
#include <map>
using namespace std;

const int N = 7;//凸多边形边数+1
int weight[][N] = { { 0, 2, 2, 3, 1, 4 }, { 2, 0, 1, 5, 2, 3 }, { 2, 1, 0, 2, 1, 4 }, { 3, 5, 2, 0, 6, 2 }, { 1, 2, 1, 6, 0, 1 }, { 4, 3, 4, 2, 1, 0 } };//凸多边形的权

int MinWeightTriangulation(int n, int **t, int **s);
void Traceback(int i, int j, int **s);//构造最优解
int Weight(int a, int b, int c);//权函数
void Traceback_norecursively(int i, int j, int **s);

int main()
{
	int **s = new int *[N];
	int **t = new int *[N];
	for (int i = 0; i < N; i++)
	{
		s[i] = new int[N];
		t[i] = new int[N];
	}

	cout << "此多边形的最优三角剖分值为：" << MinWeightTriangulation(N - 1, t, s) << endl;
	cout << "最优三角剖分结构为：" << endl;
	Traceback(1, 5, s); //s[i][j]记录了Vi-1和Vj构成三角形的第3个顶点的位置
	cout << "最优三角剖分结构为(非递归)：" << endl;
	Traceback_norecursively(1, 5, s);
	cin.get();
	return 0;
}

int MinWeightTriangulation(int n, int **t, int **s)
{
	for (int i = 1; i <= n; i++)
	{
		t[i][i] = 0;
	}
	for (int r = 2; r <= n; r++) //r为当前计算的链长（子问题规模）  
	{
		for (int i = 1; i <= n - r + 1; i++)//n-r+1为最后一个r链的前边界  
		{
			int j = i + r - 1;//计算前边界为r，链长为r的链的后边界  

			t[i][j] = t[i + 1][j] + Weight(i - 1, i, j);//将链ij划分为A(i) * ( A[i+1:j] )这里实际上就是k=i

			s[i][j] = i;

			for (int k = i + 1; k<j; k++)
			{
				//将链ij划分为( A[i:k] )* (A[k+1:j])   
				int u = t[i][k] + t[k + 1][j] + Weight(i - 1, k, j);
				if (u<t[i][j])
				{
					t[i][j] = u;
					s[i][j] = k;
				}
			}
		}
	}
	return t[1][N - 2];
}


void Traceback_norecursively(int i, int j, int **s)
{
	struct POS
	{
		int i, j;
		POS(int I,int J)
		{
			i = I;
			j = J;
		}
	}tmp(-1,-1);
	stack<POS> s1,s2;
	s1.push(POS(i,j));
	while (!s1.empty())  // 栈空时结束       
	{
		tmp = s1.top();
		s1.pop();
		s2.push(tmp);
		if (tmp.i!=s[tmp.i][tmp.j])
			s1.push(POS(tmp.i, s[tmp.i][tmp.j]));
		if (s[tmp.i][tmp.j] + 1!=tmp.j)
			s1.push(POS(s[tmp.i][tmp.j] + 1, tmp.j));
	}
	while (!s2.empty())
	{
		tmp = s2.top();
		cout << "三角剖分顶点：V" << tmp.i - 1 << ",V" << tmp.j << ",V" << s[tmp.i][tmp.j] << endl;
		s2.pop();
	}
}

void Traceback(int i, int j, int **s)
{
	if (i == j) return;
	Traceback(i, s[i][j], s);
	Traceback(s[i][j] + 1, j, s);
	cout << "三角剖分顶点：V" << i - 1 << ",V" << j << ",V" << s[i][j] << endl;
}

int Weight(int a, int b, int c)
{
	return weight[a][b] + weight[b][c] + weight[a][c];
}