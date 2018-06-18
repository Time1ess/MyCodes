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
    ListNode* addTwoNumbers(ListNode* l1, int n1, ListNode* l2, int n2) {
        if(n1 == 0 && n2 == 0) {
            return NULL;
        }
        ListNode *head, *next;
        if(n1 > n2) {
            head = new ListNode(l1->val);
            next = addTwoNumbers(l1->next, n1 - 1, l2, n2);
        } else if(n1 < n2) {
            head = new ListNode(l2->val);
            next = addTwoNumbers(l1, n1, l2->next, n2 - 1);
        } else {
            head = new ListNode(l1->val + l2->val);
            next = addTwoNumbers(l1->next, n1-1, l2->next, n2 - 1);
        }
        if(next && next->val >= 10) {
            next->val %= 10;
            head->val++;
        }
        head->next = next;
        return head;
    }
    ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
        int n1 = 0, n2 = 0;
        ListNode *node = l1;
        while(node) {
            n1++;
            node = node->next;
        }
        node = l2;
        while(node) {
            n2++;
            node = node->next;
        }
        ListNode* head = addTwoNumbers(l1, n1, l2, n2);
        if(head->val >= 10) {
            ListNode* newHead = new ListNode(1);
            head->val %= 10;
            newHead->next = head;
            return newHead;
        }
        return head;
    }
};
