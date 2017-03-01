// Author: David
// Email: youchen.du@gmail.com
// Created: 2017-03-01 19:52
// Last modified: 2017-03-01 19:52
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
    ListNode* oddEvenList(ListNode* head) {
        if(!head)
            return head;
        ListNode *odd, *even, *even_tail;
        odd = head;
        even = even_tail = head->next;
        while(even_tail && even_tail->next)
        {
            odd->next = odd->next->next;
            even_tail->next = even_tail->next->next;
            odd = odd->next;
            even_tail = even_tail->next;
        }
        odd->next = even;
        return head;
    }
};
