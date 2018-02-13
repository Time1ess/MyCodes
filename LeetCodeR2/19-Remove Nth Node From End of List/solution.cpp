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
    ListNode* removeNode(ListNode* head, int &current, int n)
    {
        if(!head)
        {
            current = 0;
            return head;
        }
        ListNode *rest = removeNode(head->next, current, n);
        current++;
        if(current == n)
            return rest;
        head->next = rest;
        return head;
    }
    ListNode* removeNthFromEnd(ListNode* head, int n) {
        int cnt = 0;
        return removeNode(head, cnt, n);
    }
};
