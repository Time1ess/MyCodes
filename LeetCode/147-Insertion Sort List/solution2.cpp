// Author: David
// Email: youchen.du@gmail.com
// Created: 2017-08-31 14:56
// Last modified: 2017-08-31 14:56
// Filename: solution2.cpp
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
        if(head == NULL)
            return NULL;
        ListNode* root = new ListNode(-1);
        root->next = insertionSortList(head->next);
        head->next = NULL;
        ListNode* tmp = root;
        while(tmp->next && tmp->next->val <= head->val)
            tmp = tmp->next;
        if(tmp->next)
            head->next = tmp->next;
        tmp->next = head;
        return root->next;
    }
};
