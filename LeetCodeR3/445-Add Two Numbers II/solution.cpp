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
    ListNode* duplicate(ListNode* head) {
        if (head == nullptr) {
            return nullptr;
        }
        ListNode* new_head = new ListNode(head->val);
        new_head->next = duplicate(head->next);
        return new_head;
    }
    ListNode* addTwoNumbers(ListNode* l1, int n, ListNode* l2, int m, int& carry) {
        if (n == 0 || m == 0) {
            return duplicate(n == 0 ? l2 : l1);
        }
        ListNode* ans = new ListNode(0);
        int child_carry = 0;
        if (n < m) {
            return addTwoNumbers(l2, m, l1, n, carry);
        } else if (n > m) {
            ans->next = addTwoNumbers(l1->next, n - 1, l2, m, child_carry);
            ans->val = l1->val + child_carry;
        } else {
            ans->next = addTwoNumbers(l1->next, n - 1, l2->next, m - 1, child_carry);
            ans->val = l1->val + l2->val + child_carry;
        }
        if (ans->val >= 10) {
            carry = 1;
            ans->val %= 10;
        }
        return ans;
        // n == m
    }
    ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
        if (l1 == nullptr || l2 == nullptr) {
            return duplicate(l1 == nullptr ? l2 : l1);
        }
        int n = 0, m = 0;
        ListNode* tmp = l1;
        while (tmp != nullptr) {
            n++;
            tmp = tmp->next;
        }
        tmp = l2;
        while (tmp != nullptr) {
            m++;
            tmp = tmp->next;
        }
        int carry = 0;
        ListNode* ans = addTwoNumbers(l1, n, l2, m, carry);
        if (carry == 0) {
            return ans;
        }
        ListNode* new_head = new ListNode(1);
        new_head->next = ans;
        return new_head;
    }
};
