// Author: David
// Email: youchen.du@gmail.com
// Created: 2017-09-09 11:33
// Last modified: 2017-09-09 11:33
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
    bool isPalindrome(ListNode* head) {
        if(head == NULL || head->next == NULL)
            return true;
        ListNode *slow, *fast;
        slow = fast = head;
        while(fast->next && fast->next->next)
        {
            slow = slow->next;
            fast = fast->next->next;
        }
        slow->next = reverse_list(slow->next);
        slow = slow->next;
        while(slow)
        {
            if(head->val != slow->val)
                return false;
            head = head->next;
            slow = slow->next;
        }
        return true;
    }
    ListNode* reverse_list(ListNode* head)
    {
        ListNode* tmp = NULL;
        ListNode* new_head = NULL;
        while(head)
        {
            tmp = head->next;
            head->next = new_head;
            new_head = head;
            head = tmp;
        }
        return new_head;
    }
};
