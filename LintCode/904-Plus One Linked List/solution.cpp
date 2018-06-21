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
     * @param head: the first Node
     * @return: the answer after plus one
     */
    void plus(ListNode* head, int& adding) {
        if(!head)
            return;
        plus(head->next, adding);
        head->val += adding;
        adding = 0;
        if(head->val >= 10) {
            adding = 1;
            head->val %= 10;
        }
    }
    ListNode * plusOne(ListNode * head) {
        // Write your code here
        int adding = 1;
        plus(head, adding);
        if(adding != 0) {
            ListNode* newHead = new ListNode(1);
            newHead->next = head;
            return newHead;
        }
        return head;
    }
};
