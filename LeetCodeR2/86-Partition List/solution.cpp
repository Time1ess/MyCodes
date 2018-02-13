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
        if(!head || head->next == NULL)
            return head;
        ListNode less(0), larger(0);
        ListNode *less_tail, *larger_tail;
        while(head)
        {
            ListNode *next = head->next;
            head->next = NULL;
            if(head->val < x)
            {
                if(less.next)
                {
                    less_tail->next = head;
                    less_tail = less_tail->next;
                }
                else
                {
                    less.next = head;
                    less_tail = head;
                }
            }
            else
            {
                if(larger.next)
                {
                    larger_tail->next = head;
                    larger_tail = larger_tail->next;
                }
                else
                {
                    larger.next = head;
                    larger_tail = head;
                }
            }
            head = next;
        }
        if(less.next)
        {
            less_tail->next = larger.next;
            return less.next;
        }
        else
            return larger.next;
    }
};
