// Author: David
// Email: youchen.du@gmail.com
// Created: 2017-04-07 11:41
// Last modified: 2017-04-07 11:41
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
    ListNode* swapPairs(ListNode* head) {
        if(head == NULL || head->next == NULL)
            return head;
        ListNode **t, *p, *q;
        t = &head;
        while((p = *t) && (q = p->next))
        {
            p->next = q->next;
            q->next = p;
            *t = q;
            t = &(p->next);
        }
        return head;
    }
};
