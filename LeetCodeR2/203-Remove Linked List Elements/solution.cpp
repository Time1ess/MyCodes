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
    ListNode* removeElements(ListNode* head, int val) {
        if(!head)
            return head;
        ListNode *next;
        ListNode new_head(0);
        ListNode *pre;
        pre = NULL;
        next = head;
        while(next)
        {
            ListNode *tmp = next, *t;
            if(next->val == val)  // Need to delete
            {                         
                while(tmp && tmp->val == val)  // include nodes with val
                {
                    t = tmp;
                    tmp = tmp->next;
                    delete t;
                }
            }
            if(pre)
            {
                pre->next = tmp;
                pre = pre->next;
            }
            else  // init
            {
                new_head.next = tmp;
                pre = tmp;
            }
            next = tmp ? tmp->next : tmp;
        }
        return new_head.next;
    }
};
