// 反转链表.cpp : 定义控制台应用程序的入口点。
//
//题目:定义一个函数，输入一个链表的头结点，反转该链表并
//输出反转后链表的头结点。
#include "stdafx.h"
#include <iostream>
using namespace std;

struct ListNode
{
	int m_nKey;
	ListNode *m_pNext;
};

ListNode* CreateListNode(int value)
{
	ListNode* pNode = new ListNode();
	pNode->m_nKey = value;
	pNode->m_pNext = NULL;

	return pNode;
}


void ConnectListNodes(ListNode* pCurrent, ListNode* pNext)
{
	if (pCurrent == NULL)
	{
		printf("Error to connect two nodes.\n");
		exit(1);
	}

	pCurrent->m_pNext = pNext;
}

void PrintListNode(ListNode* pNode)
{
	if (pNode == NULL)
	{
		printf("The node is NULL\n");
	}
	else
	{
		printf("The key in node is %d.\n", pNode->m_nKey);
	}
}

void PrintList(ListNode* pHead)
{
	printf("PrintList starts.\n");

	ListNode* pNode = pHead;
	while (pNode != NULL)
	{
		printf("%d\t", pNode->m_nKey);
		pNode = pNode->m_pNext;
	}

	printf("\nPrintList ends.\n");
}

void DestroyList(ListNode* pHead)
{
	ListNode* pNode = pHead;
	while (pNode != NULL)
	{
		pHead = pHead->m_pNext;
		delete pNode;
		pNode = pHead;
	}
}


ListNode * ReverseList(ListNode *head)
{
	if (head == NULL)
		return NULL;
	if (head->m_pNext == NULL)
		return head;

	ListNode *pRest, *pNext,*newHead;
	newHead = head;
	pRest = head->m_pNext;
	head->m_pNext = NULL;
	while (pRest != NULL)
	{
		pNext = pRest;
		pRest = pRest->m_pNext;
		pNext->m_pNext = newHead;
		newHead = pNext;
	}
	return newHead;
}

ListNode* Test(ListNode* pHead)
{
	printf("The original list is: \n");
	PrintList(pHead);

	ListNode* pReversedHead = ReverseList(pHead);

	printf("The reversed list is: \n");
	PrintList(pReversedHead);

	return pReversedHead;
}

void Test1()
{
	ListNode* pNode1 = CreateListNode(1);
	ListNode* pNode2 = CreateListNode(2);
	ListNode* pNode3 = CreateListNode(3);
	ListNode* pNode4 = CreateListNode(4);
	ListNode* pNode5 = CreateListNode(5);

	ConnectListNodes(pNode1, pNode2);
	ConnectListNodes(pNode2, pNode3);
	ConnectListNodes(pNode3, pNode4);
	ConnectListNodes(pNode4, pNode5);

	ListNode* pReversedHead = Test(pNode1);

	DestroyList(pReversedHead);
}

// 输入的链表只有一个结点
void Test2()
{
	ListNode* pNode1 = CreateListNode(1);

	ListNode* pReversedHead = Test(pNode1);

	DestroyList(pReversedHead);
}

// 输入空链表
void Test3()
{
	Test(NULL);
}


int _tmain(int argc, _TCHAR* argv[])
{
	Test1();
	Test2();
	Test3();
	cin.get();
	return 0;
}

