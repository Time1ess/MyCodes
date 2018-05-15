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
     * @param l1: ListNode l1 is the head of the linked list
     * @param l2: ListNode l2 is the head of the linked list
     * @return: ListNode head of linked list
     */
    ListNode * mergeTwoLists(ListNode * l1, ListNode * l2) {
        // write your code here
        if(!l1 || !l2)
            return l1 ? l1 : l2;
        ListNode head(0);
        ListNode *write = &head, *h1 = l1, *h2 = l2, *tmp;
        while(h1 && h2)
        {
            if(h1->val < h2->val)
            {
                tmp = h1;
                h1 = h1->next;
            }
            else
            {
                tmp = h2;
                h2 = h2->next;
            }
            tmp->next = NULL;
            write->next = tmp;
            write = write->next;
        }
        if(h1)
            write->next = h1;
        else
            write->next = h2;
        return head.next;
    }
};
