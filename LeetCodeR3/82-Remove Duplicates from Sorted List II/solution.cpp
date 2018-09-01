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
    ListNode* deleteDuplicates(ListNode* head) {
        ListNode new_head(0);
        ListNode* new_tail = &new_head;
        while (head != nullptr) {
            if (head->next == nullptr || head->next->val != head->val) {
                ListNode* node = new ListNode(head->val);
                new_tail->next = node;
                new_tail = new_tail->next;
                head = head->next;
                continue;
            } else {
                int v = head->val;
                while (head != nullptr && head->val == v) {
                    head = head->next;
                }
            }
        }
        return new_head.next;
    }
};
