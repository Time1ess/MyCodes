// Author: David
// Email: youchen.du@gmail.com
// Created: 2017-08-23 09:41
// Last modified: 2017-08-23 09:41
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
    int remove_nth_node(ListNode* head, int n)
    {
        if(head == NULL)
            return 0;
        int len = remove_nth_node(head->next, n);
        if(len == n)
        {
            ListNode* tmp = head->next;
            head->next = tmp->next;
            delete tmp;
        }
        return len+1;
    }
    ListNode* removeNthFromEnd(ListNode* head, int n) {
        int len = remove_nth_node(head, n);
        if(len == n)
        {
            ListNode *tmp = head->next;
            delete head;
            return tmp;
        }
        return head;
    }
};
