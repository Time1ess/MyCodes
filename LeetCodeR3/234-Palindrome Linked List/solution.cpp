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
    bool Equal(ListNode* h1, ListNode* h2) {
        while (h1 != nullptr && h2 != nullptr) {
            if (h1->val != h2->val) {
                return false;
            }
            h1 = h1->next;
            h2 = h2->next;
        }
        return true;
    }
    bool isPalindrome(ListNode* head) {
        int n = 0;
        ListNode* node = head;
        while (node) {
            n++;
            node = node->next;
        }
        node = head;
        if (n % 2 == 1) {
            node = node->next;
        }
        for (int i = 0; i < n / 2; i++) {
            node = node->next;
        }
        ListNode h2(0);
        while (node) {
            ListNode* next = node->next;
            node->next = h2.next;
            h2.next = node;
            node = next;
        }
        return Equal(head, h2.next);
    }
};
