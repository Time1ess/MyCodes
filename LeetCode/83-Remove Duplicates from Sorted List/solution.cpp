// Author: David
// Email: youchen.du@gmail.com
// Created: 2017-03-24 09:48
// Last modified: 2017-03-24 09:48
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
    ListNode* deleteDuplicates(ListNode* head) {
        if(!head || !head->next)
            return head;
        ListNode *p, *t;
        p = head;
        while(p->next)
        {
            if(p->val != p->next->val)
                p = p->next;
            else
            {
                t = p->next;
                p->next = t->next;
            }
        }
        return head;
    }
};
