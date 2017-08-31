// Author: David
// Email: youchen.du@gmail.com
// Created: 2017-08-31 14:50
// Last modified: 2017-08-31 14:50
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
class Solution {
public:
    ListNode* insertionSortList(ListNode* head) {
        if(!head || !head->next)
            return head;
        ListNode *root = new ListNode(-1);
        root->next = head;
        head = head->next;
        root->next->next = NULL;
        while(head)
        {
            ListNode *node = head;
            head = head->next;
            node->next = NULL;
            ListNode *tmp = root;
            while(tmp->next && tmp->next->val < node->val)
                tmp = tmp->next;
            if(tmp->next)
                node->next = tmp->next;
            tmp->next = node;
        }
        return root->next;
    }
};
