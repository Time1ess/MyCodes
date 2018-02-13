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
    ListNode* deleteDuplicates(ListNode* head) {
        if(!head || head->next == NULL)
            return head;
        ListNode new_head(0);
        new_head.next = head;
        ListNode *pre = &new_head, *tmp = head;
        while(tmp)
        {
            ListNode *next = tmp->next;
            bool deleted = false;
            if(next && next->val == tmp->val)
                deleted = true;
            if(!deleted)
            {
                pre = tmp;
                tmp = tmp->next;
                continue;
            }
            int val = tmp->val;
            while(tmp && tmp->val == val)
            {
                delete tmp;
                tmp = next;
                if(next)
                    next = next->next;
            }
            pre->next = tmp;
        }
        return new_head.next;
    }
};
