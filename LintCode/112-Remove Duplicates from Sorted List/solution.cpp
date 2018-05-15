/**
 * Definition of singly-linked-list:
 * class ListNode {
 * public:
 *     int val;
 *     ListNode *next;
 *     ListNode(int val) {
 *        this->val = val;
 *        this->next = NULL;
 *     }
 * }
 */

class Solution {
public:
    /**
     * @param head: head is the head of the linked list
     * @return: head of linked list
     */
    ListNode * deleteDuplicates(ListNode * head) {
        // write your code here
        if(!head)
            return head;
        ListNode *cur = head;
        while(cur)
        {
            if(cur->next == NULL || cur->next->val != cur->val)
            {
                cur = cur->next;
                continue;
            }
            ListNode *last_dup = cur->next;
            while(last_dup->next && last_dup->next->val == cur->val)
                last_dup = last_dup->next;
            cur->next = last_dup->next;
            cur = cur->next;
        }
        return head;
    }
};
