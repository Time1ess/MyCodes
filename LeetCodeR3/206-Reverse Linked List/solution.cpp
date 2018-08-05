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
    ListNode* reverseList(ListNode* head, ListNode** last) {
        if(!head) {
            *last = NULL;
            return NULL;
        } else if(head->next == NULL) {
            *last = head;
            return head;
        }
        ListNode* new_head = reverseList(head->next, last);
        head->next = NULL;
        (*last)->next = head;
        *last = head;
        return new_head;
    }
    ListNode* reverseList(ListNode* head) {
        if(!head) {
            return NULL;
        }
        ListNode* last;
        return reverseList(head, &last);
    }
};
