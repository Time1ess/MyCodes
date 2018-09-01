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
    ListNode* rotateRight(ListNode* head, int k) {
        int n = 0;
        ListNode* node = head;
        while (node != nullptr) {
            n++;
            node = node->next;
        }
        if (n <= 1) {
            return head;
        } else if (k % n == 0) {
            return head;
        }
        k = n - (k % n);
        ListNode* prev = nullptr;
        ListNode* new_head = head;
        while (k--) {
            prev = new_head;
            new_head = new_head->next;
        }
        prev->next = nullptr;
        node = new_head;
        while (node->next != nullptr) {
            node = node->next;
        }
        node->next = head;
        return new_head;
    }
};
