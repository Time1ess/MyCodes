// Author: David
// Email: youchen.du@gmail.com
// Created: 2017-02-14 09:55
// Last modified: 2017-02-14 09:55
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
    int sum_nodes(ListNode* l1, ListNode* l2, int l1_len, int l2_len, ListNode* ans)
    {
        int carry=0;
        if(l1_len <= 0 || l2_len <= 0)
            return carry;
        if(l1_len == l2_len)
        {
            ans->val = l1->val + l2->val;
            l1_len--;
            l2_len--;
            if(l1_len && l2_len)
            {
                ans->next = new ListNode(0);
                ans->val += sum_nodes(l1->next, l2->next, l1_len, l2_len, ans->next);
            }
        }
        else if(l1_len > l2_len)
        {
            ans->val = l1->val;
            l1_len--;
            if(l1_len && l2_len)
            {
                ans->next = new ListNode(0);
                ans->val += sum_nodes(l1->next, l2, l1_len, l2_len, ans->next);
            }
        }
        else
        {
            ans->val = l2->val;
            l2_len--;
            if(l1_len && l2_len)
            {
                ans->next = new ListNode(0);
                ans->val += sum_nodes(l1, l2->next, l1_len, l2_len, ans->next);
            }
        }

        if(ans->val >= 10)
        {
            ans->val %= 10;
            carry = 1;
        }
        return carry;
    }
    ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
        ListNode* result = new ListNode(0);
        ListNode* p;
        int l1_len = 0, l2_len = 0, carry;
        p = l1;
        while(p != NULL)
        {
            l1_len++;
            p = p->next;
        }
        p = l2;
        while(p != NULL)
        {
            l2_len++;
            p = p->next;
        }
        carry = sum_nodes(l1, l2, l1_len, l2_len, result);
        if(carry == 1)
        {
            p = new ListNode(0);
            p->val = 1;
            p->next = result;
            result = p;
        }
        return result;
    }
};
