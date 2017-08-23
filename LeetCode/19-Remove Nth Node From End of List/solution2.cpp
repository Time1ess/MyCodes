// Author: David
// Email: youchen.du@gmail.com
// Created: 2017-08-23 09:49
// Last modified: 2017-08-23 09:49
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
    ListNode* removeNthFromEnd(ListNode* head, int n) {
        ListNode *fast, *slow;
        ListNode fake_head(-1);
        fake_head.next = head;
        slow = fast = &fake_head;
        for(int i = 1; i <= n; i++)
            fast = fast->next;
        while(fast->next != NULL)
        {
            slow = slow->next;
            fast = fast->next;
        }
        slow->next = slow->next->next;
        return fake_head.next;
    }
};
