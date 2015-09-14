#include <iostream>
#include <cstdio>
#pragma warning(disable:4996)
using namespace std;



struct node
{
	int val;
	node *next;
};

node* create(int num)
{
	node *start, *p;
	start = new node;
	start->val = 1;
	start->next = NULL;
	p = start;
	for (int i = 2; i <= num; i++)
	{
		p->next = new node;
		p = p->next;
		p->val = i;
	}
	p->next = start;
	return start;
}

int main()
{
	int num;
	while (scanf("%d", &num) != EOF)
	{
		node *head = create(num);
		node *cur = head->next;
		node *pri = head;
		int k = 1;
		while (cur != pri)
		{
			for (; cur!= head;)
			{
				k++;
				if (k == 3)
				{
					pri->next = cur->next;
					delete cur;
					cur = pri->next;
					k = 0;
				}
				else
				{
					cur = cur->next;
					pri = pri->next;
				}
			}
			if (cur->next == pri&&k == 2)
			{
				delete cur;
				cur = pri;
				break;
			}
			head = cur;
			pri = head;
			cur = head->next;
			k = 1;

		}
		printf("%d\n", cur->val);
		delete cur;
	}
	return 0;
}
