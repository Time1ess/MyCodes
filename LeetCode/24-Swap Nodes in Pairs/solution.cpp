// Author: David
// Email: youchen.du@gmail.com
// Created: 2017-04-07 11:36
// Last modified: 2017-04-07 11:36
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
    ListNode* swapPairs(ListNode* head) {
        if(head == NULL || head->next == NULL)
            return head;
        ListNode *p, *q;
        p = head;
        q = p->next;
        p->next = swapPairs(q->next);
        q->next = p;
        return q;
    }
};
