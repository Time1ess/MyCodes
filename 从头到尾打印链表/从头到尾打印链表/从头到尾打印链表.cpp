// 从头到尾打印链表.cpp : 定义控制台应用程序的入口点。
//
//题目:输入一个链表的头结点，从尾到头反过来打印出每个结点的值
#include "stdafx.h"
#include <iostream>
#include <stack>
using namespace std;

struct ListNode
{
	int Key;
	ListNode* Next;
};

void AddToTail(ListNode** pHead, int value)  //将值添加至链表
{
	ListNode* pNew = new ListNode();
	pNew->Key = value;
	pNew->Next = NULL;

	if (*pHead == NULL)
	{
		*pHead = pNew;
	}
	else
	{
		ListNode* pNode = *pHead;

		while (pNode->Next != NULL)
			pNode = pNode->Next;

		pNode->Next = pNew;
	}
}

//使用栈的方法
void PrintListReversingly_stack(ListNode * pHead)
{
	stack<ListNode *> nodes;
	if (pHead == NULL)return;
	ListNode* pNode = pHead;
	while (pNode != NULL)
	{
		nodes.push(pNode);
		pNode = pNode->Next;
	}
	while (!nodes.empty())
	{
		pNode = nodes.top();
		cout << pNode->Key << " ";
		nodes.pop();
	}
}

//使用递归方法
void PrintListReversingly_Recursive(ListNode * pHead)
{
	if (pHead == NULL)return;
	else
	{
		PrintListReversingly_Recursive(pHead->Next);
		cout << pHead->Key << " ";
	}
}

// 1->2->3->4->5
void Test1()
{
	printf("\nTest1 begins.\n");

	ListNode* pHead=NULL;
	AddToTail(&pHead, 1);
	AddToTail(&pHead, 2);
	AddToTail(&pHead, 3);
	AddToTail(&pHead, 4);
	AddToTail(&pHead, 5);
	PrintListReversingly_stack(pHead);
	cout << endl;
	PrintListReversingly_Recursive(pHead);
}

// 只有一个结点的链表: 1
void Test2()
{
	printf("\nTest2 begins.\n");

	ListNode* pHead = NULL;
	AddToTail(&pHead, 1);

	PrintListReversingly_stack(pHead);
	cout << endl;
	PrintListReversingly_Recursive(pHead);
}

// 空链表
void Test3()
{
	printf("\nTest3 begins.\n");

	PrintListReversingly_stack(NULL);
	cout << endl;
	PrintListReversingly_Recursive(NULL);
}

int _tmain(int argc, _TCHAR* argv[])
{
	Test1();
	Test2();
	Test3();
	cin.get();
	return 0;
}

