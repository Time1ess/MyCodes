// 从上往下打印二叉树.cpp : 定义控制台应用程序的入口点。
//
//题目:从上往下打印出二叉树的每个结点，同一层的结点按照从左到右的顺序打印
#include "stdafx.h"
#include <iostream>
#include <queue>
using namespace std;

struct BinaryTreeNode
{
	int m_nValue;
	BinaryTreeNode *m_pLeft;
	BinaryTreeNode *m_pRight;
};

BinaryTreeNode* CreateBinaryTreeNode(int value)
{
	BinaryTreeNode* pNode = new BinaryTreeNode();
	pNode->m_nValue = value;
	pNode->m_pLeft = NULL;
	pNode->m_pRight = NULL;

	return pNode;
}

void ConnectTreeNodes(BinaryTreeNode* pParent, BinaryTreeNode* pLeft, BinaryTreeNode* pRight)
{
	if (pParent != NULL)
	{
		pParent->m_pLeft = pLeft;
		pParent->m_pRight = pRight;
	}
}

void PrintTreeNode(BinaryTreeNode* pNode)
{
	if (pNode != NULL)
	{
		printf("value of this node is: %d\n", pNode->m_nValue);

		if (pNode->m_pLeft != NULL)
			printf("value of its left child is: %d.\n", pNode->m_pLeft->m_nValue);
		else
			printf("left child is null.\n");

		if (pNode->m_pRight != NULL)
			printf("value of its right child is: %d.\n", pNode->m_pRight->m_nValue);
		else
			printf("right child is null.\n");
	}
	else
	{
		printf("this node is null.\n");
	}

	printf("\n");
}

void PrintTree(BinaryTreeNode* pRoot)
{
	PrintTreeNode(pRoot);

	if (pRoot != NULL)
	{
		if (pRoot->m_pLeft != NULL)
			PrintTree(pRoot->m_pLeft);

		if (pRoot->m_pRight != NULL)
			PrintTree(pRoot->m_pRight);
	}
}

void DestroyTree(BinaryTreeNode* pRoot)
{
	if (pRoot != NULL)
	{
		BinaryTreeNode* pLeft = pRoot->m_pLeft;
		BinaryTreeNode* pRight = pRoot->m_pRight;

		delete pRoot;
		pRoot = NULL;

		DestroyTree(pLeft);
		DestroyTree(pRight);
	}
}

void PrintTreeInBreadthOrder(BinaryTreeNode *head)
{
	if (head == NULL)return;
	queue<BinaryTreeNode*> btnQueue;
	BinaryTreeNode *node = NULL;
	btnQueue.push(head);
	while (!btnQueue.empty())
	{
		node = btnQueue.front();
		btnQueue.pop();
		if (node->m_pLeft != NULL)btnQueue.push(node->m_pLeft);
		if (node->m_pRight != NULL)btnQueue.push(node->m_pRight);
		cout << node->m_nValue << " ";
	}
}

void Test1()
{
	printf("=====Test1 starts:=====\n");
	BinaryTreeNode* pNode8 = CreateBinaryTreeNode(8);
	BinaryTreeNode* pNode6 = CreateBinaryTreeNode(6);
	BinaryTreeNode* pNode10 = CreateBinaryTreeNode(10);
	BinaryTreeNode* pNode5 = CreateBinaryTreeNode(5);
	BinaryTreeNode* pNode7 = CreateBinaryTreeNode(7);
	BinaryTreeNode* pNode9 = CreateBinaryTreeNode(9);
	BinaryTreeNode* pNode11 = CreateBinaryTreeNode(11);

	ConnectTreeNodes(pNode8, pNode6, pNode10);
	ConnectTreeNodes(pNode6, pNode5, pNode7);
	ConnectTreeNodes(pNode10, pNode9, pNode11);

//	PrintTree(pNode8);

	printf("=====Test1: BreadthFirstSearch=====\n");
	PrintTreeInBreadthOrder(pNode8);
	cout << endl;
	DestroyTree(pNode8);
}

// 测试二叉树：出叶子结点之外，左右的结点都有且只有一个左子结点
//            8
//          7   
//        6 
//      5
//    4
void Test2()
{
	printf("=====Test2 starts:=====\n");
	BinaryTreeNode* pNode8 = CreateBinaryTreeNode(8);
	BinaryTreeNode* pNode7 = CreateBinaryTreeNode(7);
	BinaryTreeNode* pNode6 = CreateBinaryTreeNode(6);
	BinaryTreeNode* pNode5 = CreateBinaryTreeNode(5);
	BinaryTreeNode* pNode4 = CreateBinaryTreeNode(4);

	ConnectTreeNodes(pNode8, pNode7, NULL);
	ConnectTreeNodes(pNode7, pNode6, NULL);
	ConnectTreeNodes(pNode6, pNode5, NULL);
	ConnectTreeNodes(pNode5, pNode4, NULL);

//	PrintTree(pNode8);

	printf("=====Test2: BreadthFirstSearch=====\n");
	PrintTreeInBreadthOrder(pNode8);
	cout << endl;

	DestroyTree(pNode8);
}


// 测试空二叉树：根结点为空指针
void Test4()
{
	printf("=====Test4 starts:=====\n");
	BinaryTreeNode* pNode = NULL;

//	PrintTree(pNode);

	printf("=====Test4: BreadthFirstSearch=====\n");
	PrintTreeInBreadthOrder(pNode);
	cout << endl;
}


int _tmain(int argc, _TCHAR* argv[])
{
	Test1();
	Test2();
	Test4();
	cin.get();
	return 0;
}

