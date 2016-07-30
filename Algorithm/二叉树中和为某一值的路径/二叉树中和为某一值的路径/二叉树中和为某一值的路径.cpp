// 二叉树中和为某一值的路径.cpp : 定义控制台应用程序的入口点。
//
//题目:输入一颗二叉树和一个整数，打印出二叉树中结点值得和为输入整数的所有路径
//从树的根结点开始往下一只到叶结点所经过的结点形成一条路径
#include "stdafx.h"
#include <iostream>
#include <vector>
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


void FindPath(BinaryTreeNode *root, int expectedSum, vector<int> &path, int currentSum)
{
	currentSum += root->m_nValue;
	path.push_back(root->m_nValue);

	bool isLeaf = root->m_pLeft == NULL&&root->m_pRight == NULL;
	if (currentSum == expectedSum&&isLeaf)
	{
		cout << "A path is found: ";
		vector<int>::iterator iter = path.begin();
		for (; iter != path.end(); ++iter)
			cout << *iter << "\t";
		cout << endl;
	}
	if (root->m_pLeft != NULL)
		FindPath(root->m_pLeft, expectedSum, path, currentSum);
	if (root->m_pRight != NULL)
		FindPath(root->m_pRight, expectedSum, path, currentSum);

	path.pop_back();
}

void FindPath(BinaryTreeNode *root, int expectedSum)
{
	if (root == NULL)
		return;
	vector<int> path;
	int currentSum = 0;
	FindPath(root, expectedSum, path, currentSum);
}

// ====================测试代码====================
void Test(char* testName, BinaryTreeNode* pRoot, int expectedSum)
{
	if (testName != NULL)
		printf("%s begins:\n", testName);

	FindPath(pRoot, expectedSum);

	printf("\n");
}

//            10
//         /      \
//        5        12
//       /\        
//      4  7     
// 有两条路径上的结点和为22
void Test1()
{
	BinaryTreeNode* pNode10 = CreateBinaryTreeNode(10);
	BinaryTreeNode* pNode5 = CreateBinaryTreeNode(5);
	BinaryTreeNode* pNode12 = CreateBinaryTreeNode(12);
	BinaryTreeNode* pNode4 = CreateBinaryTreeNode(4);
	BinaryTreeNode* pNode7 = CreateBinaryTreeNode(7);

	ConnectTreeNodes(pNode10, pNode5, pNode12);
	ConnectTreeNodes(pNode5, pNode4, pNode7);

	printf("Two paths should be found in Test1.\n");
	Test("Test1", pNode10, 22);

	DestroyTree(pNode10);
}

//            10
//         /      \
//        5        12
//       /\        
//      4  7     
// 没有路径上的结点和为15
void Test2()
{
	BinaryTreeNode* pNode10 = CreateBinaryTreeNode(10);
	BinaryTreeNode* pNode5 = CreateBinaryTreeNode(5);
	BinaryTreeNode* pNode12 = CreateBinaryTreeNode(12);
	BinaryTreeNode* pNode4 = CreateBinaryTreeNode(4);
	BinaryTreeNode* pNode7 = CreateBinaryTreeNode(7);

	ConnectTreeNodes(pNode10, pNode5, pNode12);
	ConnectTreeNodes(pNode5, pNode4, pNode7);

	printf("No paths should be found in Test2.\n");
	Test("Test2", pNode10, 15);

	DestroyTree(pNode10);
}

//               5
//              /
//             4
//            /
//           3
//          /
//         2
//        /
//       1
// 有一条路径上面的结点和为15
void Test3()
{
	BinaryTreeNode* pNode5 = CreateBinaryTreeNode(5);
	BinaryTreeNode* pNode4 = CreateBinaryTreeNode(4);
	BinaryTreeNode* pNode3 = CreateBinaryTreeNode(3);
	BinaryTreeNode* pNode2 = CreateBinaryTreeNode(2);
	BinaryTreeNode* pNode1 = CreateBinaryTreeNode(1);

	ConnectTreeNodes(pNode5, pNode4, NULL);
	ConnectTreeNodes(pNode4, pNode3, NULL);
	ConnectTreeNodes(pNode3, pNode2, NULL);
	ConnectTreeNodes(pNode2, pNode1, NULL);

	printf("One path should be found in Test3.\n");
	Test("Test3", pNode5, 15);

	DestroyTree(pNode5);
}

// 1
//  \
//   2
//    \
//     3
//      \
//       4
//        \
//         5
// 没有路径上面的结点和为16
void Test4()
{
	BinaryTreeNode* pNode1 = CreateBinaryTreeNode(1);
	BinaryTreeNode* pNode2 = CreateBinaryTreeNode(2);
	BinaryTreeNode* pNode3 = CreateBinaryTreeNode(3);
	BinaryTreeNode* pNode4 = CreateBinaryTreeNode(4);
	BinaryTreeNode* pNode5 = CreateBinaryTreeNode(5);

	ConnectTreeNodes(pNode1, NULL, pNode2);
	ConnectTreeNodes(pNode2, NULL, pNode3);
	ConnectTreeNodes(pNode3, NULL, pNode4);
	ConnectTreeNodes(pNode4, NULL, pNode5);

	printf("No paths should be found in Test4.\n");
	Test("Test4", pNode1, 16);

	DestroyTree(pNode1);
}

// 树中只有1个结点
void Test5()
{
	BinaryTreeNode* pNode1 = CreateBinaryTreeNode(1);

	printf("One path should be found in Test5.\n");
	Test("Test5", pNode1, 1);

	DestroyTree(pNode1);
}

// 树中没有结点
void Test6()
{
	printf("No paths should be found in Test6.\n");
	Test("Test6", NULL, 0);
}

int _tmain(int argc, _TCHAR* argv[])
{
	Test1();
	Test2();
	Test3();
	Test4();
	Test5();
	Test6();
	cin.get();
	return 0;
}
