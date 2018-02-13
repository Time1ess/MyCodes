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
        ListNode *tmp;
        tmp = head;
        while(tmp)
        {
            ListNode *next = tmp->next;
            bool deleted = false;
            if(next && next->val == tmp->val)
                deleted = true;
            if(deleted)
            {
                ListNode *p = next;
                while(p && p->val == tmp->val)
                {
                    next = p->next;
                    delete p;
                    p = next;
                }
                tmp->next = next;
            }
            tmp = tmp->next;
        }
        return head;
    }
};
