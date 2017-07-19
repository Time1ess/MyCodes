// Author: David
// Email: youchen.du@gmail.com
// Created: 2017-07-19 09:22
// Last modified: 2017-07-19 09:22
// Filename: solution.cpp
// Description:
struct MyTreeNode{
    MyTreeNode *left, *right;
    int value;
    int small_cnt;
    MyTreeNode(int val)
    {
        value = val;
        small_cnt = 0;
        left = right = NULL;
    }
};
class Solution {
public:
    int small_elems(MyTreeNode* root, int &target)
    {
        if(root == NULL)
            return 0;
        if(root->value > target)
            return small_elems(root->left, target);
        else
            return (root->value == target ? 0 : 1) + root->small_cnt + small_elems(root->right, target);
    }
    MyTreeNode* insert_node(MyTreeNode *root, int value)
    {
        if(root == NULL)
            root = new MyTreeNode(value);
        else
            if(value < root->value)
            {
                root->left = insert_node(root->left, value);
                root->small_cnt += 1;
            }
            else
                root->right = insert_node(root->right, value);
        return root;
    }
    vector<int> countSmaller(vector<int>& nums) {
        int size = nums.size();
        vector<int> ans(size, 0);
        MyTreeNode *root = NULL;
        for(int i = size - 1; i >= 0; i--)
        {
            root = insert_node(root, nums[i]);
            ans[i] = small_elems(root, nums[i]);
        }
        return ans;
    }
};
