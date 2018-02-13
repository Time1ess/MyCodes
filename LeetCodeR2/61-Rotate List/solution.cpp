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
    ListNode* rotateRight(ListNode* head, int k) {
        if(!head || head->next == NULL)
            return head;
        int cnt = 0;
        ListNode *tmp = head;
        while(tmp)
        {
            cnt++;
            tmp = tmp->next;
        }
        k %= cnt;
        if(k == 0)
            return head;
        ListNode *pre, *new_head;
        ListNode t(0);
        t.next = head;
        pre = &t;
        new_head = head;
        for(int i = 0; i < cnt - k; i++)
        {
            pre = pre->next;
            new_head = new_head->next;
        }
        pre->next = NULL;
        tmp = new_head;
        while(tmp->next)
            tmp = tmp->next;
        tmp->next = t.next;
        return new_head;
    }
};
