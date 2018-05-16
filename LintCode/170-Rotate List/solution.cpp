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
     * @param head: the List
     * @param k: rotate to the right k places
     * @return: the list after rotation
     */
    int get_list_length(ListNode *head)
    {
        int n = 0;
        ListNode *node = head;
        while(node)
        {
            n++;
            node = node->next;
        }
        return n;
    }
    ListNode * rotateRight(ListNode * head, int k) {
        // write your code here
        if(!head)
            return head;
        int n = get_list_length(head);
        if(k % n == 0)
            return head;
        k = n - k % n;
        // k < n
        ListNode *pre, *cur = head;
        while(k--)
        {
            pre = cur;
            cur = cur->next;
        }
        pre->next = NULL;
        ListNode *new_head = cur;
        ListNode *new_tail = cur;
        while(new_tail->next)
            new_tail = new_tail->next;
        new_tail->next = head;
        return new_head;
    }
};
