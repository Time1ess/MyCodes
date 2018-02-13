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
    ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
        if(!l1 && !l2)
            return NULL;
        ListNode* head = new ListNode((l1 ? l1->val: 0) + (l2 ? l2->val: 0));
        if(head->val >= 10)
        {
            head->val %= 10;
            if(l1 && l1->next)
                l1->next->val += 1;
            else if(l2 && l2->next)
                l2->next->val += 1;
            else
            {
                ListNode *next = new ListNode(1);
                head->next = next;
                return head;
            }
        }
        head->next = addTwoNumbers(l1 ? l1->next : NULL, l2 ? l2->next : NULL);
        return head;
    }
};
