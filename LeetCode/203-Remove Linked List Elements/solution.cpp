// Author: David
// Email: youchen.du@gmail.com
// Created: 2017-09-18 08:38
// Last modified: 2017-09-18 08:38
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
    ListNode* removeElements(ListNode* head, int val) {
        if(head == NULL)
            return NULL;
        if(head->val == val)
            return removeElements(head->next, val);
        head->next = removeElements(head->next, val);
        return head;
    }
};
