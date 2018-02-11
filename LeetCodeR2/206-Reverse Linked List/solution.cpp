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
    ListNode* reverseList(ListNode* head) {
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
