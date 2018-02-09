#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>
#include <string>
#include "binary_tree.h"

using namespace std;


int main()
{
    TreeNode *root = build_tree();
    while(root)
    {
        if(root->left != NULL)
        {
            TreeNode *pre = root->left;
            while(pre->right && pre->right != root)
                pre = pre->right;
            if(pre->right == NULL)
            {
                pre->right = root;
                root = root->left;
            }
            else
            {
                pre->right = NULL;
                cout<<root->val<<endl;
                root = root->right;
            }
        }
        else
        {
            cout<<root->val<<endl;
            root = root->right;
        }
    }
    return 0;
}
