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
    ListNode* insertionSortList(ListNode* head) {
        ListNode new_head(0);
        while(head)
        {
            ListNode* tmp = head->next;
            head->next = NULL;
            ListNode *p = &new_head;
            while(p->next && p->next->val < head->val)
                p = p->next;
            head->next = p->next;
            p->next = head;
            head = tmp;
        }
        return new_head.next;
    }
};
