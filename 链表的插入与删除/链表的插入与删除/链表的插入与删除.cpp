// 链表的插入与删除.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <iostream>
using namespace std;
struct ListNode
{
	int m_nValue;
	ListNode* m_pNext;
};

void AddToTail(ListNode** pHead, int value)  //将值添加至链表
{
	ListNode* pNew = new ListNode();
	pNew->m_nValue = value;
	pNew->m_pNext = NULL;

	if (*pHead == NULL)
	{
		*pHead = pNew;
	}
	else
	{
		ListNode* pNode = *pHead;

		while (pNode->m_pNext != NULL)
			pNode = pNode->m_pNext;

		pNode->m_pNext = pNew;
	}
}

void RemoveNode(ListNode** pHead, int value)
{
	if (pHead == NULL || *pHead == NULL)
		return;
	ListNode* pToBeDeleted = NULL;
	//如果头指针为待删除结点
	if ((*pHead)->m_nValue == value)
	{
		pToBeDeleted = *pHead;
		*pHead = pToBeDeleted->m_pNext;
	}
	else
	{
		ListNode* pNode = *pHead;
		while (pNode->m_pNext != NULL&&
			pNode->m_pNext->m_nValue != value)
			pNode = pNode->m_pNext;
		if (pNode->m_pNext != NULL&&pNode->m_pNext->m_nValue == value)
		{
			pToBeDeleted = pNode->m_pNext;
			pNode->m_pNext = pToBeDeleted->m_pNext;
		}
	}
	if (pToBeDeleted != NULL)
	{
		delete pToBeDeleted;
		pToBeDeleted = NULL;
	}
}

int _tmain(int argc, _TCHAR* argv[])
{
	return 0;
}

