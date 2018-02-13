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
    void reorderList(ListNode* head) {
        if(!head || head->next == NULL || head->next->next == NULL)
            return;
        int n = 0;
        ListNode* tmp = head, *head2;
        while(tmp)
        {
            n++;
            tmp = tmp->next;
        }
        head2 = head->next;
        tmp = head;
        for(int i = 1; i < (1 + n) / 2; i++)
        {
            head2 = head2->next;
            tmp = tmp->next;
        }
        tmp->next = NULL;
        ListNode *last = NULL;
        head2 = reverseList(head2, &last);
        while(head && head2)
        {
            tmp = head->next;
            head->next = head2;
            head = tmp;
            
            tmp = head2->next;
            head2->next = head;
            head2 = tmp;
        }
    }
};
