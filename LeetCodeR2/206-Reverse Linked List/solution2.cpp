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
    ListNode* reverseList(ListNode* head, ListNode **last)
    {
        if(!head)
            return NULL;
        if(head->next == NULL)
        {
            *last = head;
            return head;
        }
        ListNode* new_head = reverseList(head->next, last);
        head->next = NULL;
        (*last)->next = head;
        *last = head;
        return new_head;
    }
    ListNode* reverseList(ListNode* head) {
        ListNode *last = NULL;
        return reverseList(head, &last);
    }
};
