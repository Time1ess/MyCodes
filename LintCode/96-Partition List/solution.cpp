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
     * @param head: The first node of linked list
     * @param x: An integer
     * @return: A ListNode
     */
    ListNode * partition(ListNode * head, int x) {
        // write your code here
        if(!head)
            return head;
        ListNode less(0), greater(0), *less_tail, *greater_tail;
        less_tail = &less;
        greater_tail = &greater;
        while(head)
        {
            ListNode *node = head;
            head = head->next;
            node->next = NULL;
            if(node->val < x)
            {
                less_tail->next = node;
                less_tail = less_tail->next;
            }
            else
            {
                greater_tail->next = node;
                greater_tail = greater_tail->next;
            }
        }
        less_tail->next = greater.next;
        return less.next;
    }
};
