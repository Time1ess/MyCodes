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
    ListNode* addTwoNumbers(ListNode* l1, ListNode* l2, int carry) {
        if (l1 == nullptr && l2 == nullptr) {
            if (carry == 1) {
                return new ListNode(1);
            }
            return nullptr;
        }
        ListNode* node = new ListNode((l1 ? l1->val : 0) + (l2 ? l2->val : 0) + carry);
        carry = 0;
        if (node->val >= 10) {
            node->val -= 10;
            carry = 1;
        }
        node->next = addTwoNumbers(l1 ? l1->next : nullptr, l2 ? l2->next : nullptr, carry);
        return node;
    }
    ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
        return addTwoNumbers(l1, l2, 0);
    }
};
