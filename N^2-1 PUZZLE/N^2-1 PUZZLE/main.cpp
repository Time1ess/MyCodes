#include <iostream>
#include <cstring>
#include <cstdio>
#pragma warning(disable:4996)
using namespace std;
#define N 3
#define SIZE N*N

struct node
{
	int data[N][N];
	int zero_i;
	int zero_j;
	node *next;
};

node *head;
node *goal;
node *last;
int flag = 0;

void process(node *);
bool ablemove(node *, int direct);
bool Swap(node *, int direct);
void reachgoal();

int main()
{
	cout.setf(ios_base::left, ios_base::adjustfield);
	freopen("data.txt", "r", stdin);
	freopen("out.txt", "w", stdout);
	head = new node;
	goal = new node;
	last = new node;
	memset(last, 0, sizeof(node));
	memset(head, 0, sizeof(node));
	memset(goal, 0, sizeof(node));
	int num;
	//   cout<<"Enter 0-15 to fill the start puzzle,0 to represent blank"<<endl;
	for (int i = 0; i<N; i++)
	for (int j = 0; j<N; j++)
	{
		cin >> num;
		if (num == 0)
		{
			head->zero_i = i;
			head->zero_j = j;
		}
		head->data[i][j] = num;
	}
	//   cout<<"Enter 0-15 to fill the start puzzle,0 to represent blank"<<endl;
	for (int i = 0; i<N; i++)
	for (int j = 0; j<N; j++)
	{
		cin >> num;
		if (num == 0)
		{
			goal->zero_i = i;
			goal->zero_j = j;
		}
		goal->data[i][j] = num;
	}
	process(head);
	cout << endl << "reach final" << endl;
	node *p = head;
	for (; p != nullptr; p = p->next)
	{
		for (int i = 0; i<N; i++)
		{
			for (int j = 0; j<N; j++)
			{
				cout.width(2);
				cout << p->data[i][j] << " ";
			}
			cout << endl;
		}
		cout << endl;
	}
	return 0;
}

void reachgoal(node *p)
{
	if (memcmp(p->data, goal->data, sizeof(int)*SIZE) == 0)flag = 1;
}


bool Swap(node *p, int direct)
{
	int m;
	switch (direct)
	{
		case 0:
			m = p->data[p->zero_i - 1][p->zero_j];
			p->data[p->zero_i - 1][p->zero_j] = p->data[p->zero_i][p->zero_j];
			p->data[p->zero_i][p->zero_j] = m;
			p->zero_i--;
			break;
		case 1:
			m = p->data[p->zero_i + 1][p->zero_j];
			p->data[p->zero_i + 1][p->zero_j] = p->data[p->zero_i][p->zero_j];
			p->data[p->zero_i][p->zero_j] = m;
			p->zero_i++;
			break;
		case 2:
			m = p->data[p->zero_i][p->zero_j - 1];
			p->data[p->zero_i][p->zero_j - 1] = p->data[p->zero_i][p->zero_j];
			p->data[p->zero_i][p->zero_j] = m;
			p->zero_j--;
			break;
		case 3:
			m = p->data[p->zero_i][p->zero_j + 1];
			p->data[p->zero_i][p->zero_j + 1] = p->data[p->zero_i][p->zero_j];
			p->data[p->zero_i][p->zero_j] = m;
			p->zero_j++;
			break;
	}
	node *tmp = head;
	for (; tmp->next != p; tmp = tmp->next)
	{
		if (memcmp(tmp->data, p->data, sizeof(int)*SIZE) == 0)return false;
	}
	return true;
}


bool ablemove(node *now, int direct)
{
	switch (direct)
	{
		case 0:
			if (now->zero_i == 0)return false;
			break;
		case 1:
			if (now->zero_i == N - 1)return false;
			break;
		case 2:
			if (now->zero_j == 0)return false;
			break;
		case 3:
			if (now->zero_j == N - 1)return false;
			break;
	}
	if (!Swap(now, direct))return false;
	if (memcmp(last->data, now->data, sizeof(int)*SIZE) == 0)return false;
	return true;
}

void process(node *now)
{
	reachgoal(now);
	if (flag == 1)return;
	memcpy(last->data, now->data, sizeof(int)*SIZE);
	for (int i = 0; i<4; i++)
	{
		node *next = new node;
		memcpy(next, now, sizeof(node));
		next->next = nullptr;
		now->next = next;
		if (ablemove(next, i))
			process(next);
		if (flag == 1)return;
		delete next;
		now->next = nullptr;
	}
}
