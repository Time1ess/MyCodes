/**
 * Definition of ListNode
 * 
 * class ListNode {
 * public:
 *     int val;
 *     ListNode *next;
 * 
 *     ListNode(int val) {
 *         this->val = val;
 *         this->next = NULL;
 *     }
 * }
 */


class Solution {
public:
    /*
     * @param head: n
     * @return: The new head of reversed linked list.
     */
    ListNode * reverse(ListNode * head) {
        // write your code here
        if(!head || head->next == NULL)
            return head;
        ListNode new_head(0);
        while(head)
        {
            ListNode *tmp = head->next;
            head->next = new_head.next;
            new_head.next = head;
            head = tmp;
        }
        return new_head.next;
    }
};
