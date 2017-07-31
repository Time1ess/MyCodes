// Author: David
// Email: youchen.du@gmail.com
// Created: 2017-07-31 10:01
// Last modified: 2017-07-31 10:01
// Filename: solution.cpp
// Description:
/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
class Solution {
public:
    ListNode *head;
    TreeNode* build_tree(int length) // Inorder
    {
        if(length == 0)
            return NULL;
        TreeNode *node = new TreeNode(0);
        node->left = build_tree(length / 2);
        node->val = head->val;
        head = head->next;
        node->right = build_tree(length - length / 2 - 1);
        return node;
    }
    TreeNode* sortedListToBST(ListNode* head) {
        ListNode* p=head;
        int length = 0;
        while(p)
        {
            length++;
            p = p->next;
        }
        this->head = head;
        return build_tree(length);
    }
};
