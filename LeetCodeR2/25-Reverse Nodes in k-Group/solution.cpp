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
    ListNode* reverseKGroup(ListNode* head, int k) {
        if(!head || head->next == NULL)
            return head;
        ListNode *tmp = head;
        int cnt = 0;
        while(tmp)
        {
            cnt++;
            tmp = tmp->next;
        }
        ListNode new_head(0);
        ListNode *pre = &new_head;
        tmp = head;
        while(tmp)
        {
            if(cnt < k)
            {
                pre->next = tmp;
                break;
            }
            ListNode *next;
            for(int c = 0; c < k && tmp; c++)
            {
                next = tmp->next;
                tmp->next = pre->next;
                pre->next = tmp;
                tmp = next;
            }
            while(pre->next)
                pre = pre->next;
            tmp = next;
            cnt -= k;
        }
        return new_head.next;
    }
};
