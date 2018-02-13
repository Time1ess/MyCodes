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
    ListNode* reverseBetween(ListNode* head, int m, int n) {
        if(!head)
            return NULL;
        ListNode *last_node = NULL;
        ListNode *tmp, *next;
        ListNode new_head(0), *p;
        new_head.next = head;
        int cnt = n - m + 1;
        p = &new_head;
        for(int i = 0; i < m - 1; i++)
            p = p->next;
        last_node = p->next;
        tmp = p->next;
        while(cnt--)
        {
            next = tmp->next;
            tmp->next = p->next;
            p->next = tmp;
            tmp = next;
        }
        last_node->next = next;
        return new_head.next;
    }
};
