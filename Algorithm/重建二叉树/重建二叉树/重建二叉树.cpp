// 重建二叉树.cpp : 定义控制台应用程序的入口点。
//
//二叉树的建立，先序、中序、后序、宽度优先遍历
#include "stdafx.h"
#include <iostream>
#include <queue>
using namespace std;

struct BTreeNode
{
	int value;
	BTreeNode *leftC, *rightC;
};

BTreeNode* ConstructCore(int *startPreorder, int *endPreorder,
	int *startInorder, int *endInorder)
{
	//前序遍历的第一个数字是根结点的值
	int rootValue = startPreorder[0];
	BTreeNode *root = new BTreeNode();
	root->value = rootValue;
	root->leftC = root->rightC = NULL;

	//当前序列只含有一个值
	if (startPreorder == endPreorder)
	{
		if (startInorder == endInorder
			&&*startPreorder == *startInorder)
			return root;
		else
			throw exception("Invalid input.");
	}

	//在中序遍历中找到根结点的值
	int *rootInorder = startInorder;
	while (rootInorder <= endInorder&&*rootInorder != rootValue)
		++rootInorder;

	if (rootInorder == endInorder+1&&*rootInorder != rootValue)
		throw exception("Invalid input.");

	int leftLength = rootInorder - startInorder;
	int *leftPreorderEnd = startPreorder + leftLength;
	//左子树长度大于0，构建左子树
	if (leftLength > 0)
	{
		root->leftC = ConstructCore(startPreorder + 1,
			leftPreorderEnd, startInorder, rootInorder - 1);
	}
	//左子树长度不等于整个序列长度，构建右子树
	if (leftLength < endPreorder - startPreorder)
	{
		root->rightC = ConstructCore(leftPreorderEnd + 1,
			endPreorder, rootInorder + 1, endInorder);
	}
	return root;
}

BTreeNode* Construct(int *preorder, int *inorder, int length)
{
	if (preorder == NULL || inorder == NULL || length <= 0)
		return NULL;
	return ConstructCore(preorder, preorder + length - 1,
		inorder, inorder + length - 1);
}

void Test(char* testName, int* preorder, int* inorder, int length);

// 普通二叉树
//              1
//           /     \
//          2       3  
//         /       / \
//        4       5   6
//         \         /
//          7       8
void Test1()
{
	const int length = 8;
	int preorder[length] = { 1, 2, 4, 7, 3, 5, 6, 8 };
	int inorder[length] = { 4, 7, 2, 1, 5, 3, 8, 6 };

	Test("Test1", preorder, inorder, length);
}

// 所有结点都没有右子结点
//            1
//           / 
//          2   
//         / 
//        3 
//       /
//      4
//     /
//    5
void Test2()
{
	const int length = 5;
	int preorder[length] = { 1, 2, 3, 4, 5 };
	int inorder[length] = { 5, 4, 3, 2, 1 };

	Test("Test2", preorder, inorder, length);
}

// 所有结点都没有左子结点
//            1
//             \ 
//              2   
//               \ 
//                3 
//                 \
//                  4
//                   \
//                    5
void Test3()
{
	const int length = 5;
	int preorder[length] = { 1, 2, 3, 4, 5 };
	int inorder[length] = { 1, 2, 3, 4, 5 };

	Test("Test3", preorder, inorder, length);
}

// 树中只有一个结点
void Test4()
{
	const int length = 1;
	int preorder[length] = { 1 };
	int inorder[length] = { 1 };

	Test("Test4", preorder, inorder, length);
}

// 完全二叉树
//              1
//           /     \
//          2       3  
//         / \     / \
//        4   5   6   7
void Test5()
{
	const int length = 7;
	int preorder[length] = { 1, 2, 4, 5, 3, 6, 7 };
	int inorder[length] = { 4, 2, 5, 1, 6, 3, 7 };

	Test("Test5", preorder, inorder, length);
}

// 输入空指针
void Test6()
{
	Test("Test6", NULL, NULL, 0);
}

// 输入的两个序列不匹配
void Test7()
{
	const int length = 7;
	int preorder[length] = { 1, 2, 4, 5, 3, 6, 7 };
	int inorder[length] = { 4, 2, 8, 1, 6, 3, 7 };

	Test("Test7: for unmatched input", preorder, inorder, length);
}



void CreateCompleteBinaryTree(BTreeNode** head,int *values,int size)
{
	if (values == NULL || size <= 0)return;
	queue<BTreeNode **> qbt;
	int i = 0;

	qbt.push(&((*head)));

	while (i < size)
	{
		BTreeNode *node = new BTreeNode();
		BTreeNode **tmpNode=qbt.front();
		qbt.pop();
		node->value = values[i];
		node->leftC = NULL;
		node->rightC = NULL;
		*tmpNode = node;
		qbt.push(&((*tmpNode)->leftC));
		qbt.push(&((*tmpNode)->rightC));
		i++;
	}
	return;
}

void PreOrder(BTreeNode* root)
{
	if (root == NULL)return;
	cout << root->value << " ";
	PreOrder(root->leftC);
	PreOrder(root->rightC);
}

void InOrder(BTreeNode* root)
{
	if (root == NULL)return;
	InOrder(root->leftC);
	cout << root->value << " ";
	InOrder(root->rightC);
}

void PostOrder(BTreeNode* root)
{
	if (root == NULL)return;
	PostOrder(root->leftC);
	PostOrder(root->rightC);
	cout << root->value << " ";
}

void Breadth_First(BTreeNode* root)
{
	if (root == NULL)return;
	queue<BTreeNode*>qbt;
	qbt.push(root);
	while (!qbt.empty())
	{
		BTreeNode *node = qbt.front();
		qbt.pop();
		cout << node->value << " ";
		if (node->leftC != NULL)qbt.push(node->leftC);
		if (node->rightC != NULL)qbt.push(node->rightC);
	}
	return;
}



void Test(char* testName, int* preorder, int* inorder, int length)
{
	if (testName != NULL)
		printf("%s begins:\n", testName);

	printf("The preorder sequence is: ");
	for (int i = 0; i < length; ++i)
		printf("%d ", preorder[i]);
	printf("\n");

	printf("The inorder sequence is: ");
	for (int i = 0; i < length; ++i)
		printf("%d ", inorder[i]);
	printf("\n");

	try
	{
		BTreeNode* root = Construct(preorder, inorder, length);
		cout << "PreOrder:";
		PreOrder(root);
		cout << endl;
		cout << "InOrder:";
		InOrder(root);
		cout << endl;
		cout << "PostOrder:";
		PostOrder(root);
		cout << endl;
		cout << "Breadth_First";
		Breadth_First(root);
		cout << endl;

	}
	catch (std::exception& exception)
	{
		printf("Invalid Input.\n");
	}
	cout << endl << endl;
}

int _tmain(int argc, _TCHAR* argv[])
{
	Test1();
	Test2();
	Test3();
	Test4();
	Test5();
	Test6();
	Test7();

	cin.get();
	return 0;
}

