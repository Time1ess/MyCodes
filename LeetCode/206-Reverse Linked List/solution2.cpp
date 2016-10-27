// Author: David
// Email: youchen.du@gmail.com
// Created: 2016-10-27 13:35
// Last modified: 2016-10-27 13:35
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
    ListNode* reverseList(ListNode* head) {
        if(head == NULL || head->next == NULL)
            return head;
        ListNode* tmp = reverseList(head->next);
        head->next->next = head;
        head->next = NULL;
        return tmp;
    }
};
