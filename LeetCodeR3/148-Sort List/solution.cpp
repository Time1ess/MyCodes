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
    ListNode* merge(ListNode* h1, ListNode* h2) {
        if (h1 == nullptr) {
            return h2;
        } else if (h2 == nullptr) {
            return h1;
        }
        ListNode new_head(0);
        ListNode* tail = &new_head;
        while (h1 && h2) {
            if (h1->val < h2->val) {
                tail->next = h1;
                h1 = h1->next;
            } else {
                tail->next = h2;
                h2 = h2->next;
            }
            tail = tail->next;
            tail->next = nullptr;
        }
        if (h1 != nullptr) {
            tail->next = h1;
        } else if (h2 != nullptr) {
            tail->next = h2;
        }
        return new_head.next;
    }
    ListNode* sortList(ListNode* head, int n) {
        if (n <= 1) {
            return head;
        }
        int m = n / 2;
        ListNode* head2 = head;
        ListNode* prev = nullptr;
        for (int i = 0; i < m; i++) {
            prev = head2;
            head2 = head2->next;
        }
        prev->next = nullptr;
        
        head = sortList(head, m);
        head2 = sortList(head2, n - m);
        return merge(head, head2);
    }
    ListNode* sortList(ListNode* head) {
        if (head == nullptr || head->next == nullptr) {
            return head;
        }
        int n = 0;
        ListNode* node = head;
        while (node) {
            n++;
            node = node->next;
        }
        return sortList(head, n);
    }
};
