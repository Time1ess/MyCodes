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
     * @param head: The first node of linked list.
     * @param n: An integer
     * @return: The head of linked list.
     */
    ListNode * removeNthFromEnd(ListNode * head, int n) {
        // write your code here
        ListNode *p1 = head;
        while(p1 && n--)
            p1 = p1->next;
        if(!p1)
        {
            ListNode *p2 = head->next;
            head->next = NULL;
            delete head;
            return p2;
        }
        ListNode *pre, *p2 = head;
        while(p1)
        {
            pre = p2;
            p2 = p2->next;
            p1 = p1->next;
        }
        pre->next = p2->next;
        p2->next = NULL;
        delete p2;
        return head;
    }
};
