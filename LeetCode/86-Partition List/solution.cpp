// Author: David
// Email: youchen.du@gmail.com
// Created: 2017-09-15 14:23
// Last modified: 2017-09-15 14:23
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
    ListNode* partition(ListNode* head, int x) {
        ListNode l1(0), l2(0);
        ListNode *p1 = &l1, *p2 = &l2;
        while(head)
        {
            if(head->val < x)
                p1 = p1->next = head;
            else
                p2 = p2->next = head;
            head = head->next;
        }
        p2->next = NULL;
        p1->next = l2.next;
        return l1.next;
    }
};
