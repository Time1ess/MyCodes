// Author: David
// Email: youchen.du@gmail.com
// Created: 2016-10-27 11:21
// Last modified: 2016-10-27 11:21
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
    ListNode* reverseList(ListNode* head) {
        if(head == NULL)
            return head;
        ListNode *tmp=head->next,*t;
        head->next = NULL;
        while(tmp != NULL)
        {
            t = tmp;
            tmp = tmp->next;
            t->next = head;
            head = t;
        }
        return head;
    }
};
